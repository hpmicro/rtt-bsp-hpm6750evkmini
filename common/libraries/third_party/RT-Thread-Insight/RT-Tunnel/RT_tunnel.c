#include "RT_tunnel.h"

/* Error check macro: return -1 if pointer is NULL */
#define ERROR_CHECK_PTR(ptr)      \
    if ((ptr) == NULL)            \
    {                             \
        LOG_ERROR("ptr is NULL"); \
        return PTR_ERROR_CODE;    \
    }

/* Error check macro: return 0 if tunnel operation state does not match */
#define ERROR_CHECK_OPERATION(tunnel, op)              \
    if ((tunnel->status & STATUS_OPERATION_Msk) != op) \
    {                                                  \
        LOG_ERROR("tunnel operation error");           \
        return OPERATION_ERROR_CODE;                   \
    }

/* Error check macro: return 0 if tunnel is already in use */
#define ERROR_CHECK_TUNNEL_USE(tunnel)                          \
    if ((tunnel->status & STATUS_USED_Msk) == STATUS_USED_BUSY) \
    {                                                           \
        return TUNNEL_BUSY_CODE;                                \
    }
#ifdef RT_TUNNEL_USE_NONCACHE_RAM
/* Set tunnel status to BUSY */
#define TUNNEL_SET_BUSY(tunnel) \
    (tunnel->status |= STATUS_USED_BUSY)

/* Set tunnel status to IDLE */
#define TUNNEL_SET_FREE(tunnel) \
    (tunnel->status &= ~STATUS_USED_BUSY)

/* Set tunnel buffer status to FULL */
#define TUNNEL_BUFFER_FULL(tunnel) \
    (tunnel->status |= STATUS_BUFFER_FULL)

/* Set tunnel buffer status to AVAILABLE */
#define TUNNEL_BUFFER_AVAILABLE(tunnel) \
    (tunnel->status &= ~STATUS_BUFFER_FULL)

/* Tunnel Control Block */
RT_tunnel_CB RT_T_CB __attribute__((section(".noncacheable"), aligned(8)));
/* Tunnel group instances */
RT_tunnel tunnel_group[TUNNEL_NUM] __attribute__((section(".noncacheable"), aligned(8)));
/* Buffer pool for tunnel ringbuffers */
uint8_t Buffer_pool[TUNNEL_NUM][TUNNEL_BUFFER_SIZE] __attribute__((section(".noncacheable"), aligned(8)));
#else
/* Atomic operation macro: set tunnel status to BUSY */
#define TUNNEL_SET_BUSY(tunnel) \
    __atomic_or_fetch(&(tunnel->status), STATUS_USED_BUSY, __ATOMIC_SEQ_CST)

/* Atomic operation macro: set tunnel status to IDLE */
#define TUNNEL_SET_FREE(tunnel) \
    __atomic_and_fetch(&(tunnel->status), ~STATUS_USED_BUSY, __ATOMIC_SEQ_CST)

/* Atomic operation macro: set tunnel buffer status to FULL */
#define TUNNEL_BUFFER_FULL(tunnel) \
    __atomic_or_fetch(&(tunnel->status), STATUS_BUFFER_FULL, __ATOMIC_SEQ_CST)

/* Atomic operation macro: set tunnel buffer status to AVAILABLE */
#define TUNNEL_BUFFER_AVAILABLE(tunnel) \
    __atomic_and_fetch(&(tunnel->status), ~STATUS_BUFFER_FULL, __ATOMIC_SEQ_CST)

/* Tunnel Control Block */
RT_tunnel_CB RT_T_CB;
/* Tunnel group instances */
RT_tunnel tunnel_group[TUNNEL_NUM];
/* Buffer pool for tunnel ringbuffers */
uint8_t Buffer_pool[TUNNEL_NUM][TUNNEL_BUFFER_SIZE];
#endif

/*****************************************************************************
 * @brief        read data from tunnel buffer
 *
 * @param[in]    tunnel      tunnel instance
 * @param[out]   buffer      destination buffer pointer
 * @param[in]    bytes       number of bytes to read
 *
 * @retval int               actual number of bytes read,
 *                           negative value on error
 *
 * @note         lock will be taken and released internally
 *****************************************************************************/
static int Read_Buffer(RT_tunnel_t tunnel, void *buffer, uint32_t bytes)
{
    /* Error check */
    ERROR_CHECK_PTR(tunnel);
    ERROR_CHECK_PTR(buffer);
    ERROR_CHECK_OPERATION(tunnel, STATUS_OPERATION_READ);
    ERROR_CHECK_TUNNEL_USE(tunnel);

    TUNNEL_SET_BUSY(tunnel);

    uint32_t buffer_used = 0;
    uint32_t read_size   = 0;

    /* check buffer usage */
    buffer_used = chry_ringbuffer_get_used(&tunnel->RB);
    if (buffer_used < bytes)
    {
        // LOG_WARN("Buffer usage is smaller than read size.");
        bytes = buffer_used;
    }

    /* read from ringbuffer */
    read_size = chry_ringbuffer_read(&tunnel->RB, buffer, bytes);
    if (read_size != bytes)
    {
        LOG_WARN("Fewer bytes were read than expected.");
    }

    TUNNEL_SET_FREE(tunnel);

    return read_size;
}

/*****************************************************************************
 * @brief        write data into tunnel buffer
 *
 * @param[in]    tunnel      tunnel instance
 * @param[in]    buffer      source buffer pointer
 * @param[in]    bytes       number of bytes to write
 *
 * @retval int               actual number of bytes written,
 *                           0 if buffer not enough,
 *                           negative value on error
 *
 * @note         lock will be taken and released internally
 *****************************************************************************/

static int Write_Buffer(RT_tunnel_t tunnel, void *buffer, uint32_t bytes)
{
    /* Error check */
    ERROR_CHECK_PTR(tunnel);
    ERROR_CHECK_PTR(buffer);
    ERROR_CHECK_OPERATION(tunnel, STATUS_OPERATION_WRITE);
    ERROR_CHECK_TUNNEL_USE(tunnel);

    /* Set tunnel busy flag */
    TUNNEL_SET_BUSY(tunnel);

    uint32_t buffer_free = 0;
    uint32_t write_size  = 0;

    /* check free space */
    buffer_free = chry_ringbuffer_get_free(&tunnel->RB);
    if (buffer_free < bytes)
    {
        if ((tunnel->status & STATUS_BUFFER_Msk) == STATUS_BUFFER_AVAILABLE)
        {
            TUNNEL_BUFFER_FULL(tunnel);
            // LOG_ERROR("Write size exceeds buffer capacity.");
        }
        TUNNEL_SET_FREE(tunnel);
        return TUNNEL_FULL_CODE;
    }

    TUNNEL_BUFFER_AVAILABLE(tunnel);

    /* write into ringbuffer */
    write_size = chry_ringbuffer_write(&tunnel->RB, buffer, bytes);
    if (write_size != bytes)
    {
        LOG_ERROR("Write Buffer Error.");
    }

    TUNNEL_SET_FREE(tunnel);

    return write_size;
}

/*****************************************************************************
 * @brief        get free byte count of tunnel buffer
 *
 * @param[in]    tunnel      tunnel instance
 *
 * @retval int          number of free bytes in the tunnel buffer
 *****************************************************************************/
int Get_Tunnel_Buffer_Free(RT_tunnel_t tunnel)
{
    /* Error check */
    ERROR_CHECK_PTR(tunnel);
    return chry_ringbuffer_get_free(&tunnel->RB);
}

/*****************************************************************************
 * @brief        get used byte count of tunnel buffer
 *
 * @param[in]    tunnel      tunnel instance
 *
 * @retval int          number of used bytes in the tunnel buffer
 *****************************************************************************/
int Get_Tunnel_Buffer_Used(RT_tunnel_t tunnel)
{
    /* Error check */
    ERROR_CHECK_PTR(tunnel);
    return chry_ringbuffer_get_used(&tunnel->RB);
}

/*****************************************************************************
 * @brief        get a free tunnel instance
 *
 * @retval RT_tunnel_t       a free tunnel instance, or NULL if none available
 *****************************************************************************/
RT_tunnel_t Get_Free_Tunnel(void)
{
    for (uint32_t i = 0; i < TUNNEL_NUM; i++)
    {
        if ((RT_T_CB.tunnel_ptr[i]->status & STATUS_ACTIVE_Msk) == STATUS_UNACTIVE)
        {
            RT_T_CB.tunnel_ptr[i]->status |= STATUS_ACTIVE;
            return RT_T_CB.tunnel_ptr[i];
        }
    }

    return RT_NULL;
}

/*****************************************************************************
 * @brief        set operation type for a tunnel
 *
 * @param[in]    tunnel      tunnel instance
 * @param[in]    operation   operation type to set
 *
 * @retval int               0 if success, negative value on error
 *****************************************************************************/
int Set_Tunnel_Operation(RT_tunnel_t tunnel, tunnel_operation operation)
{
    /* Error check */
    ERROR_CHECK_PTR(tunnel);

    if (operation == tunnel_read)
    {
        tunnel->status |= STATUS_OPERATION_READ;
    }
    else if (operation == tunnel_write)
    {
        tunnel->status |= STATUS_OPERATION_WRITE;
    }

    return 0;
}

/*****************************************************************************
 * @brief        Set ID for a tunnel
 *
 * @param[in]    tunnel      Pointer to tunnel instance
 * @param[in]    ID          ID to assign to the tunnel
 *
 * @retval       int         0 if success, negative value on error
 *****************************************************************************/
int Set_Tunnel_ID(RT_tunnel_t tunnel, uint32_t ID)
{
    /* Check if tunnel pointer is valid */
    ERROR_CHECK_PTR(tunnel);

    /* Assign ID to tunnel */
    tunnel->ID = ID;

    return 0;
}

/*****************************************************************************
 * @brief        initialize tunnel system
 *
 * @note         should be called before using any tunnel functions
 *****************************************************************************/
int RT_Tunnel_Init(void)
{
    /* init tunnel instances */
    for (uint32_t i = 0; i < TUNNEL_NUM; i++)
    {
        /* 1. init ID */
        tunnel_group[i].ID = TUNNEL_RESET_ID;

        /* 2. init status */
        tunnel_group[i].status = STATUS_UNACTIVE | STATUS_USED_FREE;

        /* 3. init ringbuffer */
        chry_ringbuffer_init(&tunnel_group[i].RB, Buffer_pool[i], TUNNEL_BUFFER_SIZE);

        /* 4. init operations */
        tunnel_group[i].read  = Read_Buffer;
        tunnel_group[i].write = Write_Buffer;

        LOG_DEBUG("[Info][%d] Tunnel_group[i].ID:0x%08X", i, tunnel_group[i].ID);
        LOG_DEBUG("[Info][%d] Tunnel_group[i].status:0x%08X", i, tunnel_group[i].status);
        LOG_DEBUG("[Info][%d] Tunnel_group[i].status_address:0x%08X", i, &tunnel_group[i].status);
        LOG_DEBUG("[Info][%d] Tunnel_group[i].RB.in:0x%08X", i, tunnel_group[i].RB.in);
        LOG_DEBUG("[Info][%d] Tunnel_group[i].RB.in_address:0x%08X", i, &tunnel_group[i].RB.in);
        LOG_DEBUG("[Info][%d] Tunnel_group[i].RB.out:0x%08X", i, tunnel_group[i].RB.out);
        LOG_DEBUG("[Info][%d] Tunnel_group[i].RB.out_address:0x%08X", i, &tunnel_group[i].RB.out);
        LOG_DEBUG("[Info][%d] Tunnel_group[i].RB.mask:0x%08X", i, tunnel_group[i].RB.mask);
        LOG_DEBUG("[Info][%d] Tunnel_group[i].RB.pool:0x%08X\n", i, tunnel_group[i].RB.pool);
    }

    LOG_DEBUG("RT_T_CB Address:0x%08X", &RT_T_CB);
    /* init tunnel control block */
    RT_T_CB.tunnel_num = TUNNEL_NUM;
    LOG_DEBUG("RT_T_CB.tunnel_num Addr:0x%08X", &RT_T_CB.tunnel_num);
    rt_memcpy(RT_T_CB.ID, "RT_T_CB", sizeof("RT_T_CB"));
    for (uint32_t i = 0; i < TUNNEL_NUM; i++)
    {
        RT_T_CB.tunnel_ptr[i] = &tunnel_group[i];
        LOG_DEBUG("RT_T_CB.tunnel_ptr[%d]:0x%08X", i, RT_T_CB.tunnel_ptr[i]);
    }

    return 0;
}
INIT_COMPONENT_EXPORT(RT_Tunnel_Init);

/*****************************************************************************
 * @brief        print tunnel buffer content in hex format
 *
 * @param[in]    argc    argument count
 * @param[in]    argv    argument vector
 *                       argv[1] : tunnel index (0 ~ TUNNEL_NUM-1)
 *
 * @note         This function is used as an RT-Thread shell command.
 *               It reads all used bytes from the specified tunnel buffer
 *               and prints them in hex format, 4 bytes per line.
 *
 * @retval int   0 on success, negative value on error
 *****************************************************************************/
static int Tunnel_buffer_Print(int argc, char **argv)
{
    if (argc < 2)
    {
        LOG_ERROR("too few argv");
        return -1;
    }

    /* Parse tunnel index from argv */
    uint32_t tunnel_num = (uint32_t)(*argv[1] - '0');
    if (tunnel_num >= TUNNEL_NUM)
    {
        LOG_ERROR("tunnel_num out of bounds");
        return -1;
    }
    RT_tunnel_t test_tunnel = &tunnel_group[tunnel_num];

    /* Get used size and allocate temporary buffer */
    uint32_t used   = chry_ringbuffer_get_used(&test_tunnel->RB);
    uint8_t *buffer = rt_malloc(used);

    /* Check for allocation failure */
    if (buffer == NULL)
    {
        LOG_ERROR("rt_malloc failed: buffer is NULL");
        return -1;
    }

    /* Read buffer content */
    chry_ringbuffer_peek(&test_tunnel->RB, buffer, used);

    /* Print hex data, 4 bytes per line */
    for (uint32_t i = 0; i < used; i++)
    {
        if (((i % 4) == 0) && (i != 0))
        {
            rt_kprintf("\n");
        }
        rt_kprintf("[%04d]0x%02x\t", i, buffer[i]);
    }

    /* Free allocated buffer */
    rt_free(buffer);

    return 0;
}
MSH_CMD_EXPORT(Tunnel_buffer_Print, Tunnel_buffer_Print);

void Tunnel_Info_Print(void)
{
    for (uint32_t i = 0; i < TUNNEL_NUM; i++)
    {
        LOG_DEBUG("[Info][%d] Tunnel_group[i].ID:0x%08X", i, tunnel_group[i].ID);
        LOG_DEBUG("[Info][%d] Tunnel_group[i].status:0x%08X", i, tunnel_group[i].status);
        LOG_DEBUG("[Info][%d] Tunnel_group[i].status_address:0x%08X", i, &tunnel_group[i].status);
        LOG_DEBUG("[Info][%d] Tunnel_group[i].RB.in:0x%08X", i, tunnel_group[i].RB.in);
        LOG_DEBUG("[Info][%d] Tunnel_group[i].RB.in_address:0x%08X", i, &tunnel_group[i].RB.in);
        LOG_DEBUG("[Info][%d] Tunnel_group[i].RB.out:0x%08X", i, tunnel_group[i].RB.out);
        LOG_DEBUG("[Info][%d] Tunnel_group[i].RB.out_address:0x%08X", i, &tunnel_group[i].RB.out);
        LOG_DEBUG("[Info][%d] Tunnel_group[i].RB.mask:0x%08X", i, tunnel_group[i].RB.mask);
        LOG_DEBUG("[Info][%d] Tunnel_group[i].RB.pool:0x%08X\n", i, tunnel_group[i].RB.pool);
    }
}
MSH_CMD_EXPORT(Tunnel_Info_Print, Tunnel_Info_Print);
