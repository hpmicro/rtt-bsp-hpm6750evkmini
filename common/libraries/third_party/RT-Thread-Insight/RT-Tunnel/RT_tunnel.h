#ifndef __RT_TUNNEL_H__
#define __RT_TUNNEL_H__

#include "RT_Log_Print.h"
#include "chry_ringbuffer.h"
#include "rtthread.h"

/* ---------------- Tunnel Configuration ---------------- */
// #define TUNNEL_NUM         (3UL)          /**< Number of tunnels */
// #define TUNNEL_BUFFER_SIZE (8 * 1024UL)   /**< Buffer size per tunnel */
#define TUNNEL_RESET_ID (0xBAADF00DUL) /**< Default reset ID */

/* ---------------- Tunnel Status Flags ---------------- */
#define STATUS_ACTIVE_Pos (0UL)
#define STATUS_ACTIVE_Msk (1UL << STATUS_ACTIVE_Pos)
#define STATUS_ACTIVE     (1UL << STATUS_ACTIVE_Pos)
#define STATUS_UNACTIVE   (0UL << STATUS_ACTIVE_Pos)

#define STATUS_OPERATION_Pos   (1UL)
#define STATUS_OPERATION_Msk   (1UL << STATUS_OPERATION_Pos)
#define STATUS_OPERATION_READ  (1UL << STATUS_OPERATION_Pos)
#define STATUS_OPERATION_WRITE (0UL << STATUS_OPERATION_Pos)

#define STATUS_USED_Pos  (2UL)
#define STATUS_USED_Msk  (1UL << STATUS_USED_Pos)
#define STATUS_USED_BUSY (1UL << STATUS_USED_Pos)
#define STATUS_USED_FREE (0UL << STATUS_USED_Pos)

#define STATUS_BUFFER_Pos       (3UL)
#define STATUS_BUFFER_Msk       (1UL << STATUS_BUFFER_Pos)
#define STATUS_BUFFER_FULL      (1UL << STATUS_BUFFER_Pos)
#define STATUS_BUFFER_AVAILABLE (0UL << STATUS_BUFFER_Pos)

/* ---------------- Tunnel Return Codes ---------------- */
#define PTR_ERROR_CODE       (-1) /**< Error code indicating that a pointer is NULL or invalid */
#define TUNNEL_BUSY_CODE     (-2) /**< Error code indicating that the tunnel is currently busy */
#define OPERATION_ERROR_CODE (-3) /**< Error code indicating an invalid or failed operation */
#define TUNNEL_FULL_CODE     (-4) /**< Error code indicating that the tunnel buffer is full */

/* ---------------- Tunnel Operation Enum ---------------- */
/**
 * @enum tunnel_operation
 * @brief Tunnel operation type.
 */
typedef enum _tunnel_operation
{
    tunnel_write = 0, /**< Write operation */
    tunnel_read  = 1  /**< Read operation  */
} tunnel_operation;

/* ---------------- Tunnel Structure ---------------- */
/**
 * @struct RT_tunnel
 * @brief Tunnel structure containing buffer, lock, and operations.
 */
typedef struct _RT_tunnel
{
    uint32_t          ID;     /**< Tunnel ID */
    uint32_t          status; /**< Tunnel status flags */
    chry_ringbuffer_t RB;     /**< Ring buffer for data storage */

    int (*read)(struct _RT_tunnel *tunnel, void *buffer, uint32_t bytes);  /**< Read callback */
    int (*write)(struct _RT_tunnel *tunnel, void *buffer, uint32_t bytes); /**< Write callback */
} RT_tunnel;
typedef RT_tunnel *RT_tunnel_t;

/* ---------------- Tunnel Control Block ---------------- */
/**
 * @struct RT_tunnel_CB
 * @brief Global control block for tunnel management.
 */
typedef struct _RT_tunnel_CB
{
    char       ID[8];                  /**< Control block identifier */
    uint32_t   tunnel_num;             /**< Number of tunnels */
    RT_tunnel *tunnel_ptr[TUNNEL_NUM]; /**< Array of tunnel pointers */
} RT_tunnel_CB;
typedef RT_tunnel_CB *RT_tunnel_CB_t;

/* ---------------- API Functions ---------------- */
/**
 * @brief  Get free byte count of tunnel buffer.
 * @param[in] tunnel Tunnel instance
 * @retval int  Number of free bytes in the buffer
 */
int Get_Tunnel_Buffer_Free(RT_tunnel_t tunnel);

/**
 * @brief  Get used byte count of tunnel buffer.
 * @param[in] tunnel Tunnel instance
 * @retval int  Number of used bytes in the buffer
 */
int Get_Tunnel_Buffer_Used(RT_tunnel_t tunnel);

/**
 * @brief  Get a free tunnel instance.
 * @retval RT_tunnel_t A free tunnel instance, or NULL if none available
 */
RT_tunnel_t Get_Free_Tunnel(void);

/**
 * @brief     Set operation type for a tunnel.
 * @param[in] tunnel       Tunnel instance
 * @param[in] operation    Operation type (read/write)
 * @retval    int          0 on success, negative value on error
 */
int Set_Tunnel_Operation(RT_tunnel_t tunnel, tunnel_operation operation);

/*****************************************************************************
 * @brief        Set ID for a tunnel
 * @param[in]    tunnel      Pointer to tunnel instance
 * @param[in]    ID          ID to assign to the tunnel
 * @retval       int         0 if success, negative value on error
 *****************************************************************************/
int Set_Tunnel_ID(RT_tunnel_t tunnel, uint32_t ID);

/**
 * @brief Initialize tunnel system.
 * @note  Should be called before using any tunnel functions.
 */
int RT_Tunnel_Init(void);

#endif /* __RT_TUNNEL_H__ */
