
const char wifi_nvram_ap6611s[] = {
    "NVRAMRev=$Rev: 874188 $"					"\x00"
    "sromrev=11"								"\x00"
    "boardrev=0x1200"							"\x00"
    "boardtype=0x0a74"							"\x00"
    "boardflags=0x00408001"						"\x00"
    "boardflags2=0xc0800000"					"\x00"
    "boardflags3=0x40002180"					"\x00"
    //"boardnum=57410"							"\x00"
    "macaddr=00:90:4c:12:d0:01"					"\x00"
    "jtag_irw=38"								"\x00"

    //Regulatory specific
    "ccode=0"									"\x00"
    "regrev=0"									"\x00"

    //Ant related
    "aa2g=1"									"\x00"
    "aa5g=1"									"\x00"
    "agbg0=0"									"\x00"
    "aga0=0"									"\x00"
    "ag6ga0=0"									"\x00"

    //Feature flags
    "subband5gver=0x4"							"\x00"
    "subband6gver=0x1"							"\x00"

    //Board specific
    "vendid=0x14e4"								"\x00"
    "devid=0x44b0"								"\x00"
    "manfid=0x2d0"								"\x00"
    "antswitch=0"								"\x00"
    "pdgain5g=0"								"\x00"
    "pdgain2g=0"								"\x00"

    //RX gain related
    "rxgains2gelnagaina0=0"						"\x00"
    "rxgains2gtrisoa0=0"						"\x00"
    "rxgains2gtrelnabypa0=0"					"\x00"
    "rxgains5gelnagaina0=0"						"\x00"
    "rxgains5gtrisoa0=0"						"\x00"
    "rxgains5gtrelnabypa0=0"					"\x00"
    "rxgains5gmelnagaina0=0"					"\x00"
    "rxgains5gmtrisoa0=0"						"\x00"
    "rxgains5gmtrelnabypa0=0"					"\x00"
    "rxgains5ghelnagaina0=0"					"\x00"
    "rxgains5ghtrisoa0=0"						"\x00"
    "rxgains5ghtrelnabypa0=0"					"\x00"

    //RSSI related
    //"rssicorrnorm_c0=7,7"						"\x00"
    //"rssicorrnorm5g_c0=8,8,8,8,7,8,8,6,6,7,5,6"								"\x00"
    //"rssicorrnorm6g_c0=9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9"					"\x00"


    //HWRSSI related
    "rssi_cal_rev=1"							"\x00"
    "rxgaincal_rssical=1"						"\x00"
    "gain_cal_temp=31"							"\x00"
    "rssi_cal_freq_grp_2g=0x08,0x01,0x91,0x2a,0x23,0xb3,0xc4"					"\x00"
    "rssi_delta_2gb0=8,8,8,8,4,4,4,4"											"\x00"
    "rssi_delta_2gb1=8,8,8,8,4,4,4,4"											"\x00"
    "rssi_delta_2gb2=8,8,8,8,4,4,4,4"											"\x00"
    "rssi_delta_2gb3=8,8,8,8,4,4,4,4"											"\x00"
    "rssi_delta_2gb4=8,8,8,8,4,4,4,4"											"\x00"
    "rssi_delta_5gl=18,18,18,18,16,16,16,16,18,18,18,18"						"\x00"
    "rssi_delta_5gml=12,12,12,12,12,12,12,12,10,10,10,10"						"\x00"
    "rssi_delta_5gmu=12,12,12,12,8,8,8,8,10,10,10,10"							"\x00"
    "rssi_delta_5gh=8,8,8,8,8,8,8,8,10,10,10,10"								"\x00"
    "rssi_delta_6gb0=12,12,12,12,8,8,8,8,8,8,8,8"								"\x00"
    "rssi_delta_6gb1=12,12,12,12,8,8,8,8,8,8,8,8"								"\x00"
    "rssi_delta_6gb2=12,12,12,12,8,8,8,8,8,8,8,8"								"\x00"
    "rssi_delta_6gb3=8,8,8,8,8,8,8,8,6,6,6,6"									"\x00"
    "rssi_delta_6gb4=8,8,8,8,4,4,4,4,6,6,6,6"									"\x00"
    "rssi_delta_6gb5=8,8,8,8,4,4,4,4,6,6,6,6"									"\x00"

    //TSSI related
    "extpagain2g=2"								"\x00"
    "extpagain5g=2"								"\x00"
    "tssipos2g=1"								"\x00"
    "tssipos5g=1"								"\x00"
    "tworangetssi2g=0"							"\x00"
    "tworangetssi5g=0"							"\x00"
    "lowpowerrange2g=0"							"\x00"
    "lowpowerrange5g=0"							"\x00"
    "low_adc_rate_en=1"							"\x00"
    "paparambwver=3"							"\x00"
    "AvVmid_c0=3,122,5,96,5,95,5,96,4,107"										"\x00"
    "AvVmid_6g_c0=5,102,5,93,5,96,5,94,5,104,5,105"								"\x00"

    //PA parameters
    "pa2gccka0=16,10091,-1054"					"\x00"

    "pa2ga0=-9,8185,-834"						"\x00"
    //"pa5ga0=131,7758,-723,131,7788,-727,56,7538,-739,272,9973,-888"												"\x00"
    //"pa6ga0=319,8199,-594,182,7194,-656,20,6583,-706,-41,6607,-726,-32,6827,-734,59,7183,-708"					"\x00"
    "pa5ga0=22,7109,-707,34,7082,-694,50,7134,-694,-10,7646,-793"													"\x00"
    "pa6ga0=-46,6742,-712,-20,6801,-698,52,7040,-667,76,6985,-644,84,6887,-649,53,6815,-655"						"\x00"

    //MISC Core related
    "bandcap=7"									"\x00"
    "txchain=1"									"\x00"
    "rxchain=1"									"\x00"
    "nocrc=1"									"\x00"
    "otpimagesize=502"							"\x00"
    "xtalfreq=37400"							"\x00"
    "cckdigfilttype=2"							"\x00"

    //rpcal coef for imptxbf
    "rpcal5gb0=238"								"\x00"
    "rpcal5gb1=228"								"\x00"
    "rpcal5gb2=222"								"\x00"
    "rpcal5gb3=229"								"\x00"
    "rpcal2g=15"								"\x00"

    //Tempsense Related
    "tempthresh=255"							"\x00"
    "tempoffset=40"								"\x00"
    "rawtempsense=0x1ff"						"\x00"
    "phycal_tempdelta=15"						"\x00"
    "temps_period=15"							"\x00"
    "temps_hysteresis=15"						"\x00"

    //Max power and offsets
    "maxp2ga0=85"								"\x00"
    "maxp5ga0=70,70,70,70"						"\x00"
    "cckpwroffset0=2"							"\x00"
    "powoffs2gtna0=1,0,0,0,0,0,0,0,0,0,0,0,0,0"					"\x00"
    "pdoffset40ma0=0x4442"						"\x00"
    "pdoffset80ma0=0x6442"						"\x00"
    "pdoffset6g40ma0=0x000000"					"\x00"
    "pdoffset6g80ma0=0x222222"					"\x00"

    //HWOLPC
    "disable_olpc=0"							"\x00"
    "olpc_thresh2g=40"							"\x00"
    "olpc_anchor2g=52"							"\x00"
    "olpc_thresh5g=40"							"\x00"
    "olpc_anchor5g=52"							"\x00"
    "olpc_thresh6g=40"							"\x00"
    "olpc_anchor6g=52"							"\x00"
    "hwolpc_offset_c0=1,-1,-1,-1,-1"							"\x00"
    "hwolpc_offset6g_c0=4,4,4,4,4,4"							"\x00"


    //5G power offset per channel for band edge channel
    "powoffs5g20mtna0=0,0,0,0,0,0,0"							"\x00"
    "powoffs5g40mtna0=0,0,0,0,0"								"\x00"
    "powoffs5g80mtna0=0,0,0,0,0"								"\x00"
    "mcs11poexp=0"								"\x00"

    //2G/5G SU Power Per Rate
    "cckbw202gpo=0x1111"						"\x00"
    "cckbw20ul2gpo=0x1111"						"\x00"
    "mcsbw202gpo=0xba964222"					"\x00"
    "mcsbw402gpo=0xba964222"					"\x00"
    "dot11agofdmhrbw202gpo=0x5533"				"\x00"
    "ofdmlrbw202gpo=0x0011"						"\x00"
    "mcsbw205glpo=0x97422222"					"\x00"
    "mcsbw405glpo=0xB8533333"					"\x00"
    "mcsbw805glpo=0xB8533333"					"\x00"
    "mcsbw205gmpo=0x97422222"					"\x00"
    "mcsbw405gmpo=0xB8533333"					"\x00"
    "mcsbw805gmpo=0xB8533333"					"\x00"
    "mcsbw205ghpo=0x97422222"					"\x00"
    "mcsbw405ghpo=0xA8522222"					"\x00"
    "mcsbw805ghpo=0xB8522222"					"\x00"
    "mcs1024qam2gpo=0x7777"						"\x00"
    "mcs1024qam5glpo=0xFFdddd"					"\x00"
    "mcs1024qam5gmpo=0xFFDDDD"					"\x00"
    "mcs1024qam5ghpo=0xFFEECC"					"\x00"
    "mcs1024qam5gx1po=0xFFFFFF"					"\x00"
    "mcs1024qam5gx2po=0xFFFFFF"					"\x00"
    "mcs8poexp=0"								"\x00"
    "mcs9poexp=0"								"\x00"
    "mcs10poexp=0"								"\x00"

    //6G SU Power Per Rate
    "maxp6ga0=67,67,67,67,66,66"				"\x00"
    "mcsbw206gb1po=0xC8755555"					"\x00"
    "mcsbw406gb1po=0xCB966666"					"\x00"
    "mcsbw806gb1po=0xDCA55555"					"\x00"
    "mcsbw206gb2po=0xCB966666"					"\x00"
    "mcsbw406gb2po=0xCB977777"					"\x00"
    "mcsbw806gb2po=0xDCA55555"					"\x00"
    "mcsbw206gb3po=0xA9755555"					"\x00"
    "mcsbw406gb3po=0xDCA66666"					"\x00"
    "mcsbw806gb3po=0xDCA55555"					"\x00"
    "mcsbw206gb4po=0xA9744444"					"\x00"
    "mcsbw406gb4po=0xDBA66666"					"\x00"
    "mcsbw806gb4po=0xDCA55555"					"\x00"
    "mcsbw206gb5po=0xA9755555"					"\x00"
    "mcsbw406gb5po=0xDB966666"					"\x00"
    "mcsbw806gb5po=0xDCA55555"					"\x00"
    "mcsbw206gb6po=0xA9755555"					"\x00"
    "mcsbw406gb6po=0xDB666666"					"\x00"
    "mcsbw806gb6po=0xDCA55555"					"\x00"
    "mcs1024qam6gb1po=0xFFFFEE"					"\x00"
    "mcs1024qam6gb2po=0xFFFFEE"					"\x00"
    "mcs1024qam6gb3po=0xFFFFEE"					"\x00"
    "mcs1024qam6gb4po=0xFFFFEE"					"\x00"
    "mcs1024qam6gb5po=0xFFFFDD"					"\x00"
    "mcs1024qam6gb6po=0xFFFFDD"					"\x00"

    //OOB params
    //"device_wake_opt=1"						"\x00"
    "host_wake_opt=0"							"\x00"
    "muxenab=0x10"								"\x00"

    //SWCTRL Related
    "swctrlmap_2g=0x00000010,0x00000004,0x00000010,0x000000,0x3FF"						"\x00"
    "swctrlmapext_2g=0x00000000,0x00000000,0x00000000,0x000000,0x000"					"\x00"
    "swctrlmap_5g=0x00000002,0x00000008,0x00000002,0x000000,0x3FF"						"\x00"
    "swctrlmapext_5g=0x00000000,0x00000000,0x00000000,0x000000,0x000"					"\x00"
    "swctrlmap_6g=0x00000002,0x00000008,0x00000002,0x000000,0x3FF"						"\x00"
    "swctrlmapext_6g=0x00000000,0x00000000,0x00000000,0x000000,0x000"					"\x00"
    "clb2gslice0core0=0x016"					"\x00"
    "clb2gslice1core0=0x000"					"\x00"
    "clb5gslice0core0=0xA"						"\x00"
    "clb5gslice1core0=0x000"					"\x00"

    //BT Coex
    "btc_mode=1"								"\x00"
    "btc_prisel_ant_mask=0x2"					"\x00"
    "clb_swctrl_smask_ant0=0x39e"				"\x00"
    //"clb_swctrl_dmask_bt_ant0=0x2"			"\x00"
    "bt_coex_chdep_div=1"						"\x00"

    //--- PAPD Cal related params ----
    //0:NBPAPD 1:WBPAPD
    "txwbpapden=0"								"\x00"
    //NB PAPD Cal params
    "nb_eps_offset=470,470"						"\x00"
    "nb_bbmult=66,66"							"\x00"
    "nb_papdcalidx=30,30,21,14,26,26"			"\x00"
    "nb_txattn=2,2"								"\x00"
    "nb_rxattn=1,1"								"\x00"
    "nb_eps_stopidx=63"							"\x00"
    "epsilonoff_5g20_c0=-3,-3,-3,-3"			"\x00"
    "epsilonoff_5g40_c0=-3,-3,-2,-2"			"\x00"
    "epsilonoff_5g80_c0=-2,-3,-2,-2"			"\x00"
    "epsilonoff_6g20_c0=-3,-3,-3,-3,-3,-3"		"\x00"
    "epsilonoff_6g40_c0=-2,-3,-3,-3,-2,-2"		"\x00"
    "epsilonoff_6g80_c0=-1,-1,-3,-2,-1,-1"		"\x00"
    "epsilonoff_2g20_c0=-2"						"\x00"
    "epsilonoff_2g40_c0=0"						"\x00"

    //PAPR related
    "paprdis=0"									"\x00"
    "paprrmcsgamma2g=500,550,550,-1,-1,-1,-1,-1,-1,-1,-1,-1"					"\x00"
    "paprrmcsgain2g=128,128,128,0,0,0,0,0,0,0,0,0"								"\x00"
    "paprrmcsgamma2g_ch13=500,550,550,-1,-1,-1,-1,-1,-1,-1,-1,-1"				"\x00"
    "paprrmcsgain2g_ch13=128,128,128,0,0,0,0,0,0,0,0,0"							"\x00"
    "paprrmcsgamma2g_ch1=500,550,550,-1,-1,-1,-1,-1,-1,-1,-1,-1"				"\x00"
    "paprrmcsgain2g_ch1=128,128,128,0,0,0,0,0,0,0,0,0"							"\x00"
    "paprrmcsgamma5g20=500,500,500,-1,-1,-1,-1,-1,-1,-1,-1,-1"					"\x00"
    "paprrmcsgain5g20=0,0,0,0,0,0,0,0,0,0,0,0"									"\x00"
    "paprrmcsgamma5g40=600,600,600,-1,-1,-1,-1,-1,-1,-1,-1,-1"					"\x00"
    "paprrmcsgain5g40=0,0,0,0,0,0,0,0,0,0,0,0"									"\x00"
    "paprrmcsgamma5g80=550,550,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1"					"\x00"
    "paprrmcsgain5g80=128,128,0,0,0,0,0,0,0,0,0,0"								"\x00"

    //Enable papd for cck when target pwr ge 16dBm
    "cckpapd_pwrthresh=64"						"\x00"

    //energy detect threshold
    "ed_thresh2g=-67"							"\x00"
    "ed_thresh5g=-67"							"\x00"
    "ed_thresh6g=-67"							"\x00"

    //energy detect threshold for EU
    "eu_edthresh2g=-67"							"\x00"
    "eu_edthresh5g=-67"							"\x00"
    "eu_edthresh6g=-67"							"\x00"

    //# ULOFDMA Board limit PPRs for 2G20 ##
    "ruppr2g20bpska0=0x0"						"\x00"
    "ruppr2g20qpska0=0x0"						"\x00"
    "ruppr2g20qam16a0=0x0"						"\x00"
    "ruppr2g20qam64a0=0x1"						"\x00"
    "ruppr2g20qam256a0=0x21084"					"\x00"
    "ruppr2g20qam1024a0=0x50000"				"\x00"
    //# ULOFDMA Board limit PPRs for 2G40 ##
    "ruppr2g40bpska0=0x200000"					"\x00"
    "ruppr2g40qpska0=0x200000"					"\x00"
    "ruppr2g40qam16a0=0x200000"					"\x00"
    "ruppr2g40qam64a0=0x200001"					"\x00"
    "ruppr2g40qam256a0=0x421084"				"\x00"
    "ruppr2g40qam1024a0=0xA50000"				"\x00"
    //# ULOFDMA Board limit PPRs for 5G20 ##
    "ruppr5g20bpska0=0x20000"					"\x00"
    "ruppr5g20qpska0=0x18000"					"\x00"
    "ruppr5g20qam16a0=0x28000"					"\x00"
    "ruppr5g20qam64a0=0x29086"					"\x00"
    "ruppr5g20qam256a0=0x62908"					"\x00"
    "ruppr5g20qam1024a0=0x70000"				"\x00"
    //# ULOFDMA Board limit PPRs for 5G40 ##
    "ruppr5g40bpska0=0x638000"					"\x00"
    "ruppr5g40qpska0=0x840020"					"\x00"
    "ruppr5g40qam16a0=0x638001"					"\x00"
    "ruppr5g40qam64a0=0x739085"					"\x00"
    "ruppr5g40qam256a0=0x106a108"				"\x00"
    "ruppr5g40qam1024a0=0x1078000"				"\x00"
    //# ULOFDMA Board limit PPRs for 5G80 ##
    "ruppr5g80bpska0=0x0"						"\x00"
    "ruppr5g80qpska0=0x0"						"\x00"
    "ruppr5g80qam16a0=0x0"						"\x00"
    "ruppr5g80qam64a0=0x187218e7"				"\x00"
    "ruppr5g80qam256a0=0x3904254a"				"\x00"
    "ruppr5g80qam1024a0=0x49068000"				"\x00"

    //# ULOFDMA Board limit PPRs for 6G20 ##
    "ruppr6g20bpska0=0x0"						"\x00"
    "ruppr6g20qpska0=0x0"						"\x00"
    "ruppr6g20qam16a0=0x21084"					"\x00"
    "ruppr6g20qam64a0=0x5294A"					"\x00"
    "ruppr6g20qam256a0=0x6318C"					"\x00"
    "ruppr6g20qam1024a0=0x94A52"				"\x00"
    //# ULOFDMA Board limit PPRs for 6G40 ##
    "ruppr6g40bpska0=0x0"						"\x00"
    "ruppr6g40qpska0=0x0"						"\x00"
    "ruppr6g40qam16a0=0x421084"					"\x00"
    "ruppr6g40qam64a0=0xA5294A"					"\x00"
    "ruppr6g40qam256a0=0xC6318C"				"\x00"
    "ruppr6g40qam1024a0=0x1294A52"				"\x00"
    //# ULOFDMA Board limit PPRs for 6G80 ##
    "ruppr6g80bpska0=0x0"						"\x00"
    "ruppr6g80qpska0=0x0"						"\x00"
    "ruppr6g80qam16a0=0x10421084"				"\x00"
    "ruppr6g80qam64a0=0x28A5294A"				"\x00"
    "ruppr6g80qam256a0=0x30C6318C"				"\x00"
    "ruppr6g80qam1024a0=0x49294A52"				"\x00"

    //Base K Values (For the VHT case 5G 80/40/20/2G20)
    "proxd_basekival=35296,34652,36022,36142"											"\x00"
    "proxd_basektval=35299,34646,36022,36142"											"\x00"
    //Offsets across channels (Upper nibble for target, lower nibble for initiator - saved in hex)
    "proxd_80mkval=0x1717,0,0,0,0,0x0000,0x0000"										"\x00"
    "proxd_40mkval=0x3636,0x3535,0,0,0,0,0,0,0,0,0x0000,0x2727,0x2727"					"\x00"
    "proxd_20mkval=0x4444,0x6363,0x1111,0x0000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x3737,0x8888,0x6666,0x5050,0x4444"	"\x00"
    "proxd_2gkval=0x1a1a,0x1c1c,0x4242,0x3434,0x3434,0x3333,0x0000,0x0101,0x0505,0x0909,0x3c3c,0,0,0"					"\x00"
    //Offsets across frame formats @ Initiator
    //Only for non-VHT frame (Leg6, Leg non-6, mcs0, non-mcs0)
    //Delta between the base values are adjusted here
    "proxdi_rate80m=70598,70598,0,0"					"\x00"
    "proxdi_rate40m=69298,69298,0,0"					"\x00"
    "proxdi_rate20m=72044,72044,0,0"					"\x00"
    "proxdi_rate2g=72284,72284,0,0"						"\x00"
    "proxdi_ack=0,0,0,0"								"\x00"
    //Offsets across frame formats @ Responder
    "proxdt_rate80m=70598,70598,0,0"					"\x00"
    "proxdt_rate40m=69298,69298,0,0"					"\x00"
    "proxdt_rate20m=72044,72044,0,0"					"\x00"
    "proxdt_rate2g=72284,72284,0,0"						"\x00"
    "proxdt_ack=0,0,0,0"								"\x00"
    //Offsets for sub-bands (VHT, Leg6, Leg non-6, mcs0, non-mcs0)
    "proxd_sub80m20m=1627,-1627,-1627,0,0"				"\x00"
    "proxd_sub80m40m=976,-976,-976,0,0"					"\x00"
    "proxd_sub40m20m=586,-586,-586,586,586"				"\x00"
    "\x00\x00"
};
