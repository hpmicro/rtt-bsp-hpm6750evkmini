#include "rtconfig.h"

#ifdef RT_MHD_MFG_TEST
#include "wifi_firmware_bcm43436b0_mfgtest.h"
#else
#include "wifi_firmware_bcm43436b0_normal.h"
#endif

#include "nvram_ap6236.h"

extern char* wifi_firmware_ptr;
extern int   wifi_firmware_size;
extern char* wifi_clm_blob_ptr;
extern int   wifi_clm_blob_size;
extern char* wifi_nvram_ptr;
extern int   wifi_nvram_size;

void wifi_chip_resource_init(void)
{
#ifdef RT_MHD_MFG_TEST
	wifi_firmware_ptr  = (char*)fw_dlarray_43436b0_mfg;
	wifi_firmware_size = sizeof(fw_dlarray_43436b0_mfg);
#else
	wifi_firmware_ptr  = (char*)fw_dlarray_43436b0;
	wifi_firmware_size = sizeof(fw_dlarray_43436b0);
#endif
	wifi_clm_blob_ptr  = 0;
	wifi_clm_blob_size = 0;
	wifi_nvram_ptr     = (char*)wifi_nvram_ap6236;
	wifi_nvram_size    = sizeof(wifi_nvram_ap6236);
}