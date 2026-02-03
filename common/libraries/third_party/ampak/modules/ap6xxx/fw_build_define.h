#ifndef INCLUDED_FW_BUILD_DEFINE_H_
#define INCLUDED_FW_BUILD_DEFINE_H_

#define BCM_NAME				bcm43xxx
#define FW_ARRAY				fw

#define MFG_FW_ARRAY			mfg_fw

//#define FW_SIZE				fw_size
#define CLM_ARRAY				clm
//#define CLM_SIZE				clm_size
//#define FW_TABLE				fw_table

#define MFG_CLM_ARRAY			mfg_clm

#define NML_FW					wlan_nml
#define MFG_FW					wlan_mfg

#define ARRAY_TOKEN				[]
#define FILE_TOKEN				h

#define NML_FW_TYPE				0
#define MFG_FW_TYPE				1

#define CONNECT_TOKEN1(a, b)	a##b
#define CONNECT_TOKEN(a, b)		CONNECT_TOKEN1(a, b)

#define FILE_NAME(n, m)			n.m
#define ARRAY_NAME(n)			n[]

#define RESOURCE_NAME1(n, m)	n##_##m
#define RESOURCE_NAME(n, m)		RESOURCE_NAME1(n, m)

#define STRING_NAME1(n)			#n
#define STRING_NAME(n)			STRING_NAME1(n)

typedef struct
{
	int		chip;			//CHIP: 43438
	int		chiprev;		//REV:	0: A0, 1: A1
	int		type;			//FW type: 0: normal, 1: mfg
	int 	fw_size;		//FW size
	char 	*fw_array;		//FW array address
	int		clm_size;		//CLM size
	char	*clm_array;		//CLM array address
} wifi_fw_info_table_t;

#endif //INCLUDED_FW_BUILD_DEFINE_H_