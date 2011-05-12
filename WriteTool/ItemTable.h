#define NUM_COLUMNS 3
#define NUM_ITEMS   53

#define FIELD_NUM_COLUMNS 5
#define FIELD_NUM_ITEMS   42

#define A_KEY_INDEX                     0       // 0
#define ESN_INDEX                       1       // 1

#define MDN_INDEX_COUNTS                2
#define MDN_INDEX_MIN                   2       // 2, 3;

#define MCC_INDEX_COUNTS                2
#define MCC_INDEX_MIN                   4       // 4, 5;

#define ONE_ONE_TWO_TWO_INDEX_COUNTS    2
#define ONE_ONE_TWO_TWO_INDEX_MIN       6       // 6, 7;

#define MIN1_INDEX_COUNTS               2
#define MIN1_INDEX_MIN                  8       // 8, 9;

#define MIN2_INDEX_COUNTS               2
#define MIN2_INDEX_MIN                  10       // 10, 11;

#define IMSI_LENGHT_INDEX_COUNTS        2
#define IMSI_LENGHT_INDEX               12      // 12, 13;

#define UM_USER_INDEX                   14      // 14
#define UM_PASSWORD_INDEX               15      // 15
#define AN_USER_INDEX                   16      // 16
#define AN_PASSWORD_INDEX               17      // 17

#define M_IP_NUM_INDEX                  18      // 18

#define NAI_INDEX_COUNTS                6
#define NAI_INDEX_MIN                   19      // 19

#define QC_MOBILE_IP_INDEX              25      // 25
#define REGISTRATION_INDEX              26      // 26        
#define INITIAL_RETRY_INTERVAL          27      // 27
#define EXPIRY_RE_REGISTRATION_INDEX    28      // 28
#define ACTIVE_NAI                      29      // 29     
#define RFC2002_AUTH_INDEX              30      // 30
#define RRQ_IF_TRAFFIC_INDEX            31      // 31
#define ENABLE_PROFILE                  32      // 32

#define DMU_PKOID_INDEX_COUNTS          6
#define DMU_PKOID_INDEX_MIN             33      // 33

#define DMU_MN_AUTH_INDEX_COUNTS        6
#define DMU_MN_AUTH_INDEX_MIN           39      // 39

#define SHARED_SECRET_INDEX_COUNTS      6
#define SHARED_SECRET_INDEX_MIN         45      // 45

#define IMEI_INDEX                      51      // 51

static _TCHAR *_gszItem[NUM_ITEMS][NUM_COLUMNS] =
{
    // NV_ITEM_ID   FIELD_COUNTS INDEX
    _T("00025"),    _T("2"),    _T("0"),     //0 A-Key   (write only)
    _T("00000"),    _T("1"),    _T("0"),     //1 ESN

    _T("00178"),    _T("2"),    _T("0"),     //2 MDN     (Directory)
    _T("00178"),    _T("2"),    _T("1"),     //3 MDN     (Directory)

    _T("00176"),    _T("2"),    _T("0"),     //4 MCC     (CMMA)
    _T("00176"),    _T("2"),    _T("1"),     //5 MCC     (CMMA)

    _T("00177"),    _T("2"),    _T("0"),     //6 11_22   (CMMA)
    _T("00177"),    _T("2"),    _T("1"),     //7 11_22   (CMMA)

    _T("00032"),    _T("3"),    _T("0"),     //8 MIN1    (CMMA)
    _T("00032"),    _T("3"),    _T("1"),     //9 MIN1    (CMMA)

    _T("00033"),    _T("3"),    _T("0"),     //10 MIN2    (CMMA)
    _T("00033"),    _T("3"),    _T("1"),     //11 MIN2   (CMMA)

    _T("00209"),    _T("2"),    _T("0"),     //12 IMSI_LENGHT
    _T("00209"),    _T("2"),    _T("1"),     //13 IMSI_LENGHT

    _T("00318"),    _T("2"),    _T("0"),     //14 Password Authentication Protocol User ID
    _T("00319"),    _T("2"),    _T("0"),     //15 Password Authentication Protocol Password
    
    _T("00579"),    _T("2"),    _T("0"),     //16 1xEV(HDR) Access Netword CHAP Authentication NAI
    _T("00580"),    _T("2"),    _T("0"),     //17 1xEV(HDR) Access Netword CHAP Authentication Password

    _T("00463"),    _T("1"),    _T("0"),     //18 Data Services Mobile IP Number Profiles
    
    _T("00465"),    _T("11"),   _T("0"),     //19 Data Services Mobile IP General User Profile
    _T("00465"),    _T("11"),   _T("1"),     //20 Data Services Mobile IP General User Profile
    _T("00465"),    _T("11"),   _T("2"),     //21 Data Services Mobile IP General User Profile
    _T("00465"),    _T("11"),   _T("3"),     //22 Data Services Mobile IP General User Profile
    _T("00465"),    _T("11"),   _T("4"),     //23 Data Services Mobile IP General User Profile
    _T("00465"),    _T("11"),   _T("5"),     //24 Data Services Mobile IP General User Profile

    _T("00459"),    _T("1"),    _T("0"),     //25 Data Services QC Mobile IP
    _T("00460"),    _T("1"),    _T("0"),     //26 Data Services Mobile IP Registration Retries
    _T("00461"),    _T("1"),    _T("0"),     //27 Data Services Mobile IP Registration Retries Initial Interval
    _T("00462"),    _T("1"),    _T("0"),     //28 Data Services Mobile IP Registration Expiration Attempt Reregistration
    _T("00464"),    _T("1"),    _T("0"),     //29 Data Services Mobile IP Currently Active Profiles

    _T("00546"),    _T("1"),    _T("0"),     //30 Data Services Mobile IP RFC2002bis MN Home Agent Authenticator Calculation
    _T("00707"),    _T("1"),    _T("0"),     //31 Data Services Mobile IP RRQ IF Traffic

    _T("00714"),    _T("6"),    _T("0"),     //32 Data Services Mobile IP Enable Profile

    _T("00854"),    _T("2"),    _T("0"),     //33 Data Services Mobile IP DMU PKO ID
    _T("00854"),    _T("2"),    _T("1"),     //34 Data Services Mobile IP DMU PKO ID
    _T("00854"),    _T("2"),    _T("2"),     //35 Data Services Mobile IP DMU PKO ID
    _T("00854"),    _T("2"),    _T("3"),     //36 Data Services Mobile IP DMU PKO ID
    _T("00854"),    _T("2"),    _T("4"),     //37 Data Services Mobile IP DMU PKO ID
    _T("00854"),    _T("2"),    _T("5"),     //38 Data Services Mobile IP DMU PKO ID

    _T("00889"),    _T("2"),    _T("0"),     //39 Data Services Mobile IP DMU MN Authentication
    _T("00889"),    _T("2"),    _T("1"),     //40 Data Services Mobile IP DMU MN Authentication
    _T("00889"),    _T("2"),    _T("2"),     //41 Data Services Mobile IP DMU MN Authentication
    _T("00889"),    _T("2"),    _T("3"),     //42 Data Services Mobile IP DMU MN Authentication
    _T("00889"),    _T("2"),    _T("4"),     //43 Data Services Mobile IP DMU MN Authentication
    _T("00889"),    _T("2"),    _T("5"),     //44 Data Services Mobile IP DMU MN Authentication

    _T("00466"),    _T("35"),   _T("0"),     //45 Data Services Mobile IP Shared Secret User Profile
    _T("00466"),    _T("35"),   _T("1"),     //46 Data Services Mobile IP Shared Secret User Profile
    _T("00466"),    _T("35"),   _T("2"),     //47 Data Services Mobile IP Shared Secret User Profile
    _T("00466"),    _T("35"),   _T("3"),     //48 Data Services Mobile IP Shared Secret User Profile
    _T("00466"),    _T("35"),   _T("4"),     //49 Data Services Mobile IP Shared Secret User Profile
    _T("00466"),    _T("35"),   _T("5"),     //50 Data Services Mobile IP Shared Secret User Profile

    _T("00550"),    _T("9"),    _T("0"),     //51 UE_IMEI

    _T("00447"),    _T("6"),    _T("0")      //52 Blue Tooth Address
};

// 0. NV_A_KEY_I(25)
static char *_gszField_A_KEY_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("00"),                 _T("00"), _T("nam"), _T("8"), _T("UINT8"),
    _T("0x0000000000000000"), _T("0x0000000000000000"), _T("key"), _T("64"), _T("UINT64")
};

// 1. NV_ELECTRONIC_SERIAL_NUMBER(0)
static char *_gszField_ELECTRONIC_SERIAL_NUMBER[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("0x00000000"),   _T("0x00000000"),   _T("esn"),  _T("32"),   _T("UINT32")
};

// 2. NV_DIR_NUMBER_I(178)      // size of dir_number is 80 in QXDM, but limit 15 charact later on form, one bug?
static char *_gszField_DIR_NUMBER_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("00"),     _T("00"),   _T("nam"),    _T("8"), _T("UINT8"),
    _T("0b0000"), _T("0b0000"), _T("dir_number"), _T("80"), _T("ANSI Fixed String")
};
/*
 *	2, 3;
 */

// 4. NV_IMSI_MCC_I(176)
static char *_gszField_IMSI_MCC[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("00"),    _T("00"), _T("nam"), _T("8"), _T("UINT8"),
    _T("0x0000"),    _T("0x0000"), _T("imsi_mcc"), _T("16"), _T("UINT16")
};
/*
 *	4, 5;
 */

// 6. NV_IMSI_11_12_I(177)
static char *_gszField_IMSI_11_12[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("00"),    _T("00"), _T("nam"), _T("8"), _T("UINT8"),
    _T("0x00"),    _T("0x00"), _T("imsi_11_12"), _T("8"), _T("UINT8")
};
/*
 *	6, 7;
 */

//    IMSI_M: Five components of IMSI_M
// 8. NV_MIN1_I(32)
static char *_gszField_MIN1_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
	_T("00"),    _T("00"), _T("nam"), _T("8"), _T("UINT8"),
	_T("0x00000000"),    _T("0x00000000"), _T("min1[0]"), _T("32"), _T("UINT32"),
	_T("0x00000000"),    _T("0x00000000"), _T("min1[1]"), _T("32"), _T("UINT32")
};
/*
 *	8, 9;
 */

// 10. NV_MIN2_I(33)
static char *_gszField_MIN2_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
	_T("00"),       _T("00"), _T("nam"), _T("8"), _T("UINT8"),
	_T("0x0000"),   _T("0x0000"), _T("min2[0]"), _T("16"), _T("UINT16"),
	_T("0x0000"),   _T("0x0000"), _T("min2[1]"), _T("16"), _T("UINT16")
};
/*
 *	10, 11;
 */

// 12. NV_IMSI_ADDR_NUM_I(209)
static char *_gszField_IMSI_ADDR_NUM[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("00"),    _T("00"),  _T("nam"), _T("8"), _T("UINT8"),
    _T("00"),    _T("00"),  _T("num"),  _T("8"), _T("UINT8")
};
/*
 *	12, 13;
 */

// Um
// 14. NV_PAP_USER_ID_I(318)             // 合并了64(64*8bits)个UINT8成ANSI Fixed String
static char *_gszField_PAP_USER_ID_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("0x00"),     _T("0x00"), _T("user_id_len"), _T("8"), _T("UINT8"),
    _T("0b0000"),   _T("0b0000"), _T("userid_id[i]"), _T("512"), _T("ANSI Fixed String")
};

// 15. NV_PAP_PASSWORD_I(319)            // 合并了14(14*8bits)个UINT8成ANSI Fixed String
static char *_gszField_PAP_PASSWORD_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("0x00"),     _T("0x00"), _T("password_len"), _T("8"), _T("UINT8"),
    _T("0b0000"),   _T("0b0000"), _T("password[i]"), _T("112"), _T("ANSI Fixed String")
};

// AN
// 16. NV_HDR_AN_AUTH_NAI_I(579)         // 合并了64(64*8bits)个UINT8成ANSI Fixed String
static char *_gszField_HDR_AN_AUTH_NAI_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("00"),       _T("00"), _T("length"), _T("8"), _T("UINT8"),
    _T("0b0000"),   _T("0b0000"), _T("nai[i]"), _T("512"), _T("ANSI Fixed String")
};

// 17. NV_HDR_AN_AUTH_PASSWORD_I(580)   // 合并了14(14*8bits)个UINT8成ANSI Fixed String
static char *_gszField_HDR_AN_AUTH_PASSWORD_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("00"),     _T("00"), _T("password_len"), _T("8"), _T("UINT8"),
    _T("0b0000"),   _T("0b0000"), _T("password[i]"), _T("112"), _T("ANSI Fixed String")
};

// 18. NV_DS_MIP_NUM_PROF_I(463)
static char *_gszField_DS_MIP_NUM_PROF_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("0x00"),   _T("0x00"),   _T("ds_mip_num_prof"),  _T("8"),   _T("UINT8")
};

// 19. NV_DS_MIP_GEN_USER_PROF_I(465)   // 合并了72(72*8bits)个UINT8成ANSI Fixed String
static char *_gszField_DS_MIP_GEN_USER_PROF_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("00"),           _T("00"),           _T("index"),            _T("8"),    _T("UINT8"),
    _T("0x00"),         _T("0x00"),         _T("nai_length"),       _T("8"),    _T("UINT8"),
    _T("0b0000"),       _T("0b0000"),       _T("nai[i]"),           _T("576"),  _T("ANSI Fixed String"),
    _T("0x00"),         _T("0x00"),         _T("mn_ha_spi_set"),    _T("8"),    _T("UINT8"), 
    _T("0x00000000"),   _T("0x00000000"),   _T("mn_ha_spi"),        _T("32"),   _T("UINT32"), 
    _T("0x00"),         _T("0x00"),         _T("mn_aaa_spi_set"),   _T("8"),    _T("UINT8"), 
    _T("0x00000000"),   _T("0x00000000"),   _T("mn_aaa_spi"),       _T("32"),   _T("UINT32"), 
    _T("0x00"),         _T("0x00"),         _T("rev_tun_pref"),     _T("8"),    _T("UINT8"), 
    _T("0x00000000"),   _T("0x00000000"),   _T("home_addr"),        _T("32"),   _T("UINT32"), 
    _T("0x00000000"),   _T("0x00000000"),   _T("primary_ha_addr"),  _T("32"),   _T("UINT32"), 
    _T("0x00000000"),   _T("0x00000000"),   _T("secondary_ha_addr"),_T("32"),   _T("UINT32")
};

/*
 *	19, 20, 21, 22, 23, 24;
 */

// 25. NV_DS_QCMIP_I(459)
static char *_gszField_DS_QCMIP_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("0x00"),   _T("0x00"),   _T("ds_qcmip"),  _T("8"),   _T("UINT8")
};

// 26. NV_DS_MIP_RETRIES_I(460)
static char *_gszField_DS_MIP_RETRIES_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("00"),   _T("00"),   _T("ds_mip_retries"),  _T("8"),   _T("UINT8")
};

// 27. NV_DS_MIP_RETRY_INT_I(461)
static char *_gszField_DS_MIP_RETRY_INT_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("0x00"),   _T("0x00"),   _T("ds_mip_retry_int"),  _T("8"),   _T("UINT8")
};

// 28. NV_DS_MIP_PRE_RE_RRQ_TIME_I(462)
static char *_gszField_DS_MIP_PRE_RE_RRQ_TIME_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("00"),   _T("00"),   _T("ds_mip_pre_re_rrq_time"),  _T("8"),   _T("UINT8")
};

// 29. NV_DS_MIP_ACTIVE_PROF_I(464)
static char *_gszField_DS_MIP_ACTIVE_PROF_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("0x00"),   _T("0x00"),   _T("ds_mip_active_prof"),  _T("8"),   _T("UINT8")
};

// 30. NV_DS_MIP_2002BIS_MN_HA_AUTH_I(546)
static char *_gszField_DS_MIP_2002BIS_MN_HA_AUTH_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("0x00"),   _T("0x00"),   _T("ds_mip_2002bis_mn_ha_auth"),  _T("8"),   _T("UINT8")
};

// 31. NV_DS_MIP_RRQ_IF_TFRK_I(707)
static char *_gszField_DS_MIP_RRQ_IF_TFRK_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("0x00"),   _T("0x00"),   _T("ds_mip_rrq_if_tfrk"),  _T("8"),   _T("UINT8")
};

// 32. NV_DS_MIP_ENABLE_PROF_I(714)
static char *_gszField_DS_MIP_ENABLE_PROF_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("0x00"),   _T("0x00"),   _T("ds_mip_enable_prof[0]"),  _T("8"),   _T("UINT8"), 
    _T("0x00"),   _T("0x00"),   _T("ds_mip_enable_prof[1]"),  _T("8"),   _T("UINT8"), 
    _T("0x00"),   _T("0x00"),   _T("ds_mip_enable_prof[2]"),  _T("8"),   _T("UINT8"), 
    _T("0x00"),   _T("0x00"),   _T("ds_mip_enable_prof[3]"),  _T("8"),   _T("UINT8"), 
    _T("0x00"),   _T("0x00"),   _T("ds_mip_enable_prof[4]"),  _T("8"),   _T("UINT8"), 
    _T("0x00"),   _T("0x00"),   _T("ds_mip_enable_prof[5]"),  _T("8"),   _T("UINT8")
};

// 33. NV_DS_MIP_DMU_PKOID_I(854)
static char *_gszField_DS_MIP_DMU_PKOID_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("00"),   _T("00"),   _T("index"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("pkoid"), _T("8"), _T("UINT8")
};
/*
 *	33, 34, 35, 36, 37, 38
 */

// 39. NV_DS_MIP_DMU_MN_AUTH_I(889)     // 3(3*8bits)个UINT8成ANSI Fixed String
static char *_gszField_DS_MIP_DMU_MN_AUTH_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("00"),       _T("00"),   _T("index"),           _T("8"),  _T("UINT8"),
    _T("0x000000"), _T("0x000000"), _T("mn_auth[i]"),  _T("24"), _T("UINT8"),
    //_T("0x00"),     _T("0x00"), _T("mn_auth[1]"),   _T("8"),    _T("UINT8"),
    //_T("0x00"),     _T("0x00"), _T("mn_auth[2]"),   _T("8"),    _T("UINT8")
};
/*
 *	39, 40, 41, 42, 43, 44
 */

// 45. NV_DS_MIP_SS_USER_PROF_I(466)    // 合并了16(16*8bits)个UINT8成ANSI Fixed String
static char *_gszField_DS_MIP_SS_USER_PROF_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("00"),   _T("00"),   _T("index"),                        _T("8"),    _T("UINT8"),

    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret_length"),   _T("8"),    _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_ha_shared_secret[i]"), _T("8"), _T("UINT8"),

    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret_length"),  _T("8"),    _T("UINT8"), 
    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret[i]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("mn_aaa_shared_secret[i]"), _T("8"), _T("UINT8")
};
/*
 *	45, 46, 47, 48, 49, 50
 */

// 51. NV_UE_IMEI_I(550)
static char *_gszField_UE_IMEI_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("0x00"), _T("0x00"), _T("ue_imei[0]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("ue_imei[1]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("ue_imei[2]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("ue_imei[3]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("ue_imei[4]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("ue_imei[5]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("ue_imei[6]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("ue_imei[7]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("ue_imei[8]"), _T("8"), _T("UINT8")
};

// 52. NV_BD_ADDR_I(447)
static char *_gszField_BD_ADDR_I[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS] =
{
    _T("0x00"), _T("0x00"), _T("bd_addr[0]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("bd_addr[1]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("bd_addr[2]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("bd_addr[3]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("bd_addr[4]"), _T("8"), _T("UINT8"),
    _T("0x00"), _T("0x00"), _T("bd_addr[5]"), _T("8"), _T("UINT8")
};

static char *_gszFieldItem[NUM_ITEMS] = 
{
    (char *)_gszField_A_KEY_I,

    (char *)_gszField_ELECTRONIC_SERIAL_NUMBER, 

    (char *)_gszField_DIR_NUMBER_I, (char *)_gszField_DIR_NUMBER_I,

	(char *)_gszField_IMSI_MCC, (char *)_gszField_IMSI_MCC,
    (char *)_gszField_IMSI_11_12, (char *)_gszField_IMSI_11_12, 
	(char *)_gszField_MIN1_I, (char *)_gszField_MIN1_I,
    (char *)_gszField_MIN2_I, (char *)_gszField_MIN2_I,
    (char *)_gszField_IMSI_ADDR_NUM, (char *)_gszField_IMSI_ADDR_NUM,

    (char *)_gszField_PAP_USER_ID_I, (char *)_gszField_PAP_PASSWORD_I, 

    (char *)_gszField_HDR_AN_AUTH_NAI_I, (char *)_gszField_HDR_AN_AUTH_PASSWORD_I,

    (char *)_gszField_DS_MIP_NUM_PROF_I, 
    (char *)_gszField_DS_MIP_GEN_USER_PROF_I, (char *)_gszField_DS_MIP_GEN_USER_PROF_I, 
    (char *)_gszField_DS_MIP_GEN_USER_PROF_I, (char *)_gszField_DS_MIP_GEN_USER_PROF_I,
    (char *)_gszField_DS_MIP_GEN_USER_PROF_I, (char *)_gszField_DS_MIP_GEN_USER_PROF_I, 
    
    (char *)_gszField_DS_QCMIP_I, 
    (char *)_gszField_DS_MIP_RETRIES_I, 
    (char *)_gszField_DS_MIP_RETRY_INT_I,
    (char *)_gszField_DS_MIP_PRE_RE_RRQ_TIME_I, 
    (char *)_gszField_DS_MIP_ACTIVE_PROF_I,

    (char *)_gszField_DS_MIP_2002BIS_MN_HA_AUTH_I, 
    (char *)_gszField_DS_MIP_RRQ_IF_TFRK_I, 

    (char *)_gszField_DS_MIP_ENABLE_PROF_I,

    (char *)_gszField_DS_MIP_DMU_PKOID_I, (char *)_gszField_DS_MIP_DMU_PKOID_I,
    (char *)_gszField_DS_MIP_DMU_PKOID_I, (char *)_gszField_DS_MIP_DMU_PKOID_I,
    (char *)_gszField_DS_MIP_DMU_PKOID_I, (char *)_gszField_DS_MIP_DMU_PKOID_I,

    (char *)_gszField_DS_MIP_DMU_MN_AUTH_I, (char *)_gszField_DS_MIP_DMU_MN_AUTH_I, 
    (char *)_gszField_DS_MIP_DMU_MN_AUTH_I, (char *)_gszField_DS_MIP_DMU_MN_AUTH_I, 
    (char *)_gszField_DS_MIP_DMU_MN_AUTH_I, (char *)_gszField_DS_MIP_DMU_MN_AUTH_I,

    (char *)_gszField_DS_MIP_SS_USER_PROF_I, (char *)_gszField_DS_MIP_SS_USER_PROF_I, 
    (char *)_gszField_DS_MIP_SS_USER_PROF_I, (char *)_gszField_DS_MIP_SS_USER_PROF_I, 
    (char *)_gszField_DS_MIP_SS_USER_PROF_I, (char *)_gszField_DS_MIP_SS_USER_PROF_I,

    (char *)_gszField_UE_IMEI_I,

    (char *)_gszField_BD_ADDR_I
};

