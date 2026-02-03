
#include "rtthread.h"
#include "wmhd_api.h"
#include "hwconfig.h"

#if !defined(RT_USING_WIFI)
static void wmhd_init(int argc, char **argv)
{
    wmhd_gpio_config(WL_REG_ON, WL_REGON_PORT, WL_REGON_PIN); //WL_REGON
    wmhd_gpio_config(WL_HW_OOB, WL_HWOOB_PORT, WL_HWOOB_PIN); //WL_HWOOB
    wmhd_module_init();
}
MSH_CMD_EXPORT(wmhd_init, wmhd wifi driver init);
#endif

#if defined(RT_USING_WIFI) && ( (RTTHREAD_VERSION >= RT_VERSION_CHECK(5, 0, 0)) && defined(RT_WLAN_MANAGE_ENABLE) && defined(RT_WLAN_MSH_CMD_ENABLE) || \
        (RTTHREAD_VERSION < RT_VERSION_CHECK(5, 0, 0) ) )
#define wmhd            wmhd
#else
#define wmhd            wifi
#endif

static void wmhd(int argc, char **argv)
{
    if (argc > 1)
    {
        ++argv;
        --argc;
    }
    wmhd_wifi_commands(argc, argv);
}
MSH_CMD_EXPORT(wmhd, wmhd wifi command);

static void wl(int argc, char **argv)
{
    if (argc > 1)
    {
        ++argv;
        --argc;
    }
        wmhd_wl_cmds(argc, argv);
}
MSH_CMD_EXPORT(wl, wifi test tool command);
