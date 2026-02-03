
#include "rtconfig.h"
#include "fw_build_define.h"
#include "nv_build_define.h"
#include "wmhd_api.h"

#ifdef RT_WIFI_AP6212A_SEL
#include "wifi_firmware_bcm43438a1_normal.h"
static wifi_fw_info_table_t wlan_nml_fw_bcm43438a1 =
{
	.chip 		= 43430,
	.chiprev 	= 1,
	.type 		= NML_FW_TYPE,
	.fw_size 	= sizeof(fw_dlarray_43438a1),
	.fw_array 	= (char*)fw_dlarray_43438a1,
	.clm_size	= 0,
	.clm_array 	= 0,
};

#ifdef RT_MHD_MFG_TEST
#include "wifi_firmware_bcm43438a1_mfgtest.h"
static wifi_fw_info_table_t wlan_mfg_fw_bcm43438a1 =
{
	.chip 		= 43430,
	.chiprev 	= 1,
	.type 		= MFG_FW_TYPE,
	.fw_size 	= sizeof(fw_dlarray_43438a1_mfg),
	.fw_array 	= (char*)fw_dlarray_43438a1_mfg,
	.clm_size	= 0,
	.clm_array 	= 0,
};
#endif

#include "nvram_ap6212a.h"
static wifi_nv_info_table_t wlan_nv_ap6212a =
{
	.chip	 = 43430,
	.chiprev = 1,
	.size 	 = sizeof(wifi_nvram_ap6212a),
	.array 	 = (char*)wifi_nvram_ap6212a,
};
#endif

#ifdef RT_WIFI_AP6236_SEL
#include "wifi_firmware_bcm43436b0_normal.h"
static wifi_fw_info_table_t wlan_nml_fw_bcm43436b0 =
{
	.chip 		= 43430,
	.chiprev 	= 2,
	.type 		= NML_FW_TYPE,
	.fw_size 	= sizeof(fw_dlarray_43436b0),
	.fw_array 	= (char*)fw_dlarray_43436b0,
	.clm_size	= 0,
	.clm_array 	= 0,
};

#include "nvram_ap6236.h"
static wifi_nv_info_table_t wlan_nv_ap6236 =
{
	.chip	 = 43430,
	.chiprev = 2,
	.size 	 = sizeof(wifi_nvram_ap6236),
	.array 	 = (char*)wifi_nvram_ap6236,
};
#endif

#ifdef RT_WIFI_AP6256_SEL
#include "wifi_firmware_bcm43456c5_normal.h"
#include "wifi_clm_bcm43456c5.h"
static wifi_fw_info_table_t wlan_nml_fw_bcm43456c5 =
{
	.chip 		= 0x4345,
	.chiprev 	= 9,
	.type 		= NML_FW_TYPE,
	.fw_size 	= sizeof(fw_dlarray_43456c5),
	.fw_array 	= (char*)fw_dlarray_43456c5,
	.clm_size	= sizeof(clm_dlarray_43456c5),
	.clm_array 	= (char*)clm_dlarray_43456c5,
};

#include "nvram_ap6256.h"
static wifi_nv_info_table_t wlan_nv_ap6256 =
{
	.chip	 = 0x4345,
	.chiprev = 9,
	.size 	 = sizeof(wifi_nvram_ap6256),
	.array 	 = (char*)wifi_nvram_ap6256,
};
#endif

#if defined(RT_WIFI_AP6201BM_SEL) || defined(RT_WIFI_AP6203BM_SEL) || defined(RT_WIFI_AP6303BH_SEL)
#include "wifi_firmware_bcm43013c1_normal.h"
#include "wifi_clm_bcm43013c1.h"
static wifi_fw_info_table_t wlan_nml_fw_bcm43013c1 =
{
	.chip 		= 0xA804,
	.chiprev 	= 2,
	.type 		= NML_FW_TYPE,
	.fw_size 	= sizeof(fw_dlarray_43013c1),
	.fw_array 	= (char*)fw_dlarray_43013c1,
	.clm_size	= sizeof(clm_dlarray_43013c1),
	.clm_array 	= (char*)clm_dlarray_43013c1,
};

#if defined(RT_WIFI_AP6201BM_SEL)
#include "nvram_ap6201bm.h"
static wifi_nv_info_table_t wlan_nv_ap6201bm =
{
	.chip	 = 0xA804,
	.chiprev = 2,
	.size 	 = sizeof(wifi_nvram_ap6201bm),
	.array 	 = (char*)wifi_nvram_ap6201bm,
};
#endif

#if defined(RT_WIFI_AP6203BM_SEL)
#include "nvram_ap6203bm.h"
static wifi_nv_info_table_t wlan_nv_ap6203bm =
{
	.chip	 = 0xA804,
	.chiprev = 2,
	.size 	 = sizeof(wifi_nvram_ap6203bm),
	.array 	 = (char*)wifi_nvram_ap6203bm,
};
#endif

#if defined(RT_WIFI_AP6303BH_SEL)
#include "nvram_ap6303bh.h"
static wifi_nv_info_table_t wlan_nv_ap6303bh =
{
	.chip	 = 0xA804,
	.chiprev = 2,
	.size 	 = sizeof(wifi_nvram_ap6303bh),
	.array 	 = (char*)wifi_nvram_ap6303bh,
};
#endif
#endif

#ifdef RT_WIFI_AP6275S_SEL
#include "wifi_firmware_bcm43752a2_normal.h"
#include "wifi_clm_bcm43752a2.h"
static wifi_fw_info_table_t wlan_nml_fw_bcm43752a2 =
{
	.chip 		= 43752,
	.chiprev 	= 2,
	.type 		= NML_FW_TYPE,
	.fw_size 	= sizeof(fw_dlarray_43752a2),
	.fw_array 	= (char*)fw_dlarray_43752a2,
	.clm_size	= sizeof(clm_dlarray_43752a2),
	.clm_array 	= (char*)clm_dlarray_43752a2,
};

#include "nvram_ap6275s.h"
static wifi_nv_info_table_t wlan_nv_ap6275s =
{
	.chip	 = 43752,
	.chiprev = 2,
	.size 	 = sizeof(wifi_nvram_ap6275s),
	.array 	 = (char*)wifi_nvram_ap6275s,
};
#endif

#ifdef RT_WIFI_AP6281_SEL
#include "wifi_firmware_syn4381a0_normal.h"
#include "wifi_clm_syn4381a0.h"
static wifi_fw_info_table_t wlan_nml_fw_syn4381a0 =
{
	.chip 		= 0x4381,
	.chiprev 	= 1,
	.type 		= NML_FW_TYPE,
	.fw_size 	= sizeof(fw_dlarray_4381a0),
	.fw_array 	= (char*)fw_dlarray_4381a0,
	.clm_size	= sizeof(clm_dlarray_4381a0),
	.clm_array 	= (char*)clm_dlarray_4381a0,
};

#include "nvram_ap6281.h"
static wifi_nv_info_table_t wlan_nv_ap6281 =
{
	.chip	 = 0x4381,
	.chiprev = 1,
	.size 	 = sizeof(wifi_nvram_ap6281),
	.array 	 = (char*)wifi_nvram_ap6281,
};
#endif

#ifdef RT_WIFI_AP6611S_SEL
#include "wifi_firmware_syn43711a0_normal.h"
#include "wifi_clm_syn43711a0.h"
static wifi_fw_info_table_t wlan_nml_fw_syn43711a0 =
{
	.chip 		= 43711,
	.chiprev 	= 0,
	.type 		= NML_FW_TYPE,
	.fw_size 	= sizeof(fw_dlarray_43711a0),
	.fw_array 	= (char*)fw_dlarray_43711a0,
	.clm_size	= sizeof(clm_dlarray_43711a0),
	.clm_array 	= (char*)clm_dlarray_43711a0,
};

#include "nvram_ap6611s.h"
static wifi_nv_info_table_t wlan_nv_ap6611s =
{
	.chip	 = 43711,
	.chiprev = 0,
	.size 	 = sizeof(wifi_nvram_ap6611s),
	.array 	 = (char*)wifi_nvram_ap6611s,
};
#endif

void wifi_chip_resource_init(void)
{
    void *ptr_fw_list[10];
    void *ptr_nv_list[10];
	int fw_num = 0, nv_num = 0;
#ifdef RT_WIFI_AP6212A_SEL
    ptr_fw_list[fw_num++] = (void *)&wlan_nml_fw_bcm43438a1;
#ifdef RT_MHD_MFG_TEST
    ptr_fw_list[fw_num++] = (void *)&wlan_mfg_fw_bcm43438a1;
#endif
	ptr_nv_list[nv_num++] = (void *)&wlan_nv_ap6212a;
#endif
#ifdef RT_WIFI_AP6236_SEL
    ptr_fw_list[fw_num++] = (void *)&wlan_nml_fw_bcm43436b0;
	ptr_nv_list[nv_num++] = (void *)&wlan_nv_ap6236;
#endif
#ifdef RT_WIFI_AP6256_SEL
    ptr_fw_list[fw_num++] = (void *)&wlan_nml_fw_bcm43456c5;
	ptr_nv_list[nv_num++] = (void *)&wlan_nv_ap6256;
#endif
#if defined(RT_WIFI_AP6201BM_SEL) || defined(RT_WIFI_AP6203BM_SEL) || defined(RT_WIFI_AP6303BH_SEL)
    ptr_fw_list[fw_num++] = (void *)&wlan_nml_fw_bcm43013c1;
#if defined(RT_WIFI_AP6201BM_SEL)
	ptr_nv_list[nv_num++] = (void *)&wlan_nv_ap6201bm; //Note: Because chip id is the same if using multi 43013 chip, so it can't select correct nvram.
#endif
#if defined(RT_WIFI_AP6203BM_SEL)
	ptr_nv_list[nv_num++] = (void *)&wlan_nv_ap6203bm;
#endif
#if defined(RT_WIFI_AP6303BH_SEL)
	ptr_nv_list[nv_num++] = (void *)&wlan_nv_ap6303bh;
#endif
#endif
#ifdef RT_WIFI_AP6275S_SEL
    ptr_fw_list[fw_num++] = (void *)&wlan_nml_fw_bcm43752a2;
	ptr_nv_list[nv_num++] = (void *)&wlan_nv_ap6275s;
#endif
#ifdef RT_WIFI_AP6281_SEL
    ptr_fw_list[fw_num++] = (void *)&wlan_nml_fw_syn4381a0;
	ptr_nv_list[nv_num++] = (void *)&wlan_nv_ap6281;
#endif
#ifdef RT_WIFI_AP6611S_SEL
    ptr_fw_list[fw_num++] = (void *)&wlan_nml_fw_syn43711a0;
	ptr_nv_list[nv_num++] = (void *)&wlan_nv_ap6611s;
#endif

	if (fw_num > 10 || nv_num > 10)
	{
		//rt_kprintf("%s: firmware or nvram support no more than 10\r\n", __FUNCTION__);
		return;
	}

	wmhd_wlan_fw_load(ptr_fw_list, fw_num);
	wmhd_wlan_nv_load(ptr_nv_list, nv_num);
	//wmhd_wlan_fw_type(1); //0: normal(default)   1: mfgtest
}