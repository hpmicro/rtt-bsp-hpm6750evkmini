#ifndef __RT_INSIGHT_H__
#define __RT_INSIGHT_H__

#include "RT_Log_Print.h"
#include "RT_insight_config.h"
#include "RT_tunnel.h"
#include "rtthread.h"
#include <rthw.h>

/* ---------------- Insight Data Structure ---------------- */
/**
 * @struct RT_insight_info
 * @brief Structure representing an insight event or trace information.
 */
typedef struct _RT_insight_info
{
    uint32_t Frame_Header;     /**< Frame header, 4 bytes */
    uint32_t ID;               /**< Event ID, 4 bytes */
    uint32_t Track_Type;       /**< Track type, 4 bytes */
    uint32_t Time_Stamp_ns_lo; /**< Lower 32 bits of timestamp in nanoseconds */
    uint32_t Time_Stamp_ns_hi; /**< Higher 32 bits of timestamp in nanoseconds */
} RT_insight_info;

/* ---------------- Insight Initialization ---------------- */
/**
 * @brief Initialize the RT Insight module.
 *
 * @retval int  0 on success, negative value on error
 */
int RT_Insight_Init(void);

#endif // __RT_INSIGHT_H__
