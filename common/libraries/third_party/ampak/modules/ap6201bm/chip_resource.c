#include "rtconfig.h"

#ifdef RT_MHD_MFG_TEST
#include "wifi_firmware_bcm43013c1_mfgtest.h"
#else
#include "wifi_firmware_bcm43013c1_normal.h"
#endif

#include "wifi_clm_bcm43013c1.h"
#include "nvram_ap6201bm.h"

extern char* wifi_firmware_ptr;
extern int   wifi_firmware_size;
extern char* wifi_clm_blob_ptr;
extern int   wifi_clm_blob_size;
extern char* wifi_nvram_ptr;
extern int   wifi_nvram_size;

void wifi_chip_resource_init(void)
{
#ifdef RT_MHD_MFG_TEST
	wifi_firmware_ptr  = (char*)fw_dlarray_43013c1_mfg;
	wifi_firmware_size = sizeof(fw_dlarray_43013c1_mfg);
#else
	wifi_firmware_ptr  = (char*)fw_dlarray_43013c1;
	wifi_firmware_size = sizeof(fw_dlarray_43013c1);
#endif
	wifi_clm_blob_ptr  = (char*)clm_dlarray_43013c1;
	wifi_clm_blob_size = sizeof(clm_dlarray_43013c1);
	wifi_nvram_ptr     = (char*)wifi_nvram_ap6201bm;
	wifi_nvram_size    = sizeof(wifi_nvram_ap6201bm);
}