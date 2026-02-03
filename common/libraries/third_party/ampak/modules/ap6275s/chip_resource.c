#include "rtconfig.h"

#ifdef RT_MHD_MFG_TEST
#include "wifi_firmware_bcm43752a2_mfgtest.h"
#else
#include "wifi_firmware_bcm43752a2_normal.h"
#endif

#include "wifi_clm_bcm43752a2.h"
#include "nvram_ap6275s.h"

extern char* wifi_firmware_ptr;
extern int   wifi_firmware_size;
extern char* wifi_clm_blob_ptr;
extern int   wifi_clm_blob_size;
extern char* wifi_nvram_ptr;
extern int   wifi_nvram_size;

void wifi_chip_resource_init(void)
{
#ifdef RT_MHD_MFG_TEST
	wifi_firmware_ptr  = (char*)fw_dlarray_43752a2_mfg;
	wifi_firmware_size = sizeof(fw_dlarray_43752a2_mfg);
#else
	wifi_firmware_ptr  = (char*)fw_dlarray_43752a2;
	wifi_firmware_size = sizeof(fw_dlarray_43752a2);
#endif
	wifi_clm_blob_ptr  = (char*)clm_dlarray_43752a2;
	wifi_clm_blob_size = sizeof(clm_dlarray_43752a2);
	wifi_nvram_ptr     = (char*)wifi_nvram_ap6275s;
	wifi_nvram_size    = sizeof(wifi_nvram_ap6275s);
}