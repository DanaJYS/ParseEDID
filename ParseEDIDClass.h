#pragma once
#include <string.h>

#define		CBIOS_ESTABLISHMODECOUNT		17
#define		CBIOS_STDMODECOUNT				8
#define		CBIOS_DTLMODECOUNT				4
#define		CBIOS_DTDTIMINGCOUNT			6

#define		MAX_HDMI_VIC_LEN				7
#define		MAX_HDMI_3D_LEN					31

#define		MAX_SVD_COUNT					31

#define		CBIOS_EDIDMAXBLOCKCOUNT			4

#define CBIOS_HDMI_EXTENED_VIC_COUNTS		4 
#define CBIOS_HDMI_NORMAL_VIC_COUNTS		107
#define CBIOS_HDMIFORMATCOUNT				CBIOS_HDMI_NORMAL_VIC_COUNTS + CBIOS_HDMI_EXTENED_VIC_COUNTS

#define		CBIOS_HDMI_AUDIO_FORMAT_COUNT	16

typedef struct _CBIOS_S3GMODE_INFO
{
	union
	{
		struct  
		{
			unsigned short	YResolution;
			unsigned short	XResolution;
		};
		unsigned int	XYResolution;
	};

	unsigned short	Refreshrate;
	bool			Valid;
}CBIOS_S3GMODE_INFO, *PCBIOS_S3GMODE_INFO;

typedef struct _CBIOS_MODE_INFO_EXT
{
	union
	{
		struct  
		{
			union
			{
				unsigned short	YResolution;
				unsigned short	VActive;
			};
			union
			{
				unsigned short	XResolution;
				unsigned short	HActive;
			};
		};
		unsigned int	XYResolution;
	};

	unsigned short	HBlank;
	unsigned short	HSyncOffset;
	unsigned short	HSyncPulseWidth;
	unsigned short	VBlank;
	unsigned short	VSyncOffset;
	unsigned short	VSyncPulseWidth;
	unsigned short	HImageSize;
	unsigned short	VImageSize;
	unsigned short	PixelClock;
	unsigned short	Refreshrate;
	bool			Valid;
	unsigned char	InterLaced;
	unsigned char	VSync;
	unsigned char	HSync;
	unsigned char	AspectRatio;
	unsigned char	IsNativeMode;
}CBIOS_MODE_INFO_EXT, *PCBIOS_MODE_INFO_EXT;

typedef struct _HDMI_3D_STRUCTURE_ALL
{
	unsigned short		FrameRacking		:1;
	unsigned short		FieldAlternative	:1;
	unsigned short		LineAlternative		:1;
	unsigned short		SideBySideFull		:1;
	unsigned short		LDepth				:1;
	unsigned short		LDepthGraphics		:1;
	unsigned short		TopAndBottom		:1;
	unsigned short		RsvdBits0			:1;
	unsigned short		SideBySideHalf		:1;
	unsigned short		RsvdBits1			:6;
	unsigned short		NotInUse			:1;
}HDMI_3D_STRUCTURE_ALL, *PHDMI_3D_STRUCTURE_ALL;

typedef struct _CBIOS_HDMI_FORMAT_DESCRIPTOR
{
	unsigned char	IsNative;
	unsigned char	IsSupported;
	unsigned char	BlockIndex;
	unsigned char	RefreshIndex;
	union
	{
		HDMI_3D_STRUCTURE_ALL	Video3DSupportStruct;
		unsigned short			Video3DSupportCaps;
	};

	struct 
	{
		unsigned char			IsSupportYCbCr420	:1;
		unsigned char			IsSupportOtherFormat	:1;
		unsigned char			RsvdBits	:6;
	};

	unsigned char		SVDIndexInVideoBlock;
}CBIOS_HDMI_FORMAT_DESCRIPTOR, *PCBIOS_HDMI_FORMAT_DESCRIPTOR;

typedef struct _CBIOS_HDMI_3D_FORMAT
{
	struct  
	{
		unsigned char    HDMI3DStructure             :4;
		unsigned char    HDMI2DVICOrder              :4;
	};
	struct
	{
		unsigned char    RsvdBits                    :4;
		unsigned char    HDMI3DDetail                :4;
	};
}CBIOS_HDMI_3D_FORMAT, *PCBIOS_HDMI_3D_FORMAT;

typedef struct _CBIOS_HDMI_VSDB_EXTENTION
{
	struct
	{
		unsigned char        VSDBLength              :5;
		unsigned char        VSDBTag                 :3;
	}Tag;
	struct  
	{
		unsigned char        RegistrationIDByte0;
		unsigned char        RegistrationIDByte1;
		unsigned char        RegistrationIDByte2;
		unsigned short       SourcePhyAddr;

	}VSDBHeader;
	union
	{
		struct
		{
			unsigned char    IsSupportDualLink       :1;
			unsigned char    RsvdBits0               :2;
			unsigned char    IsSupportY444           :1;
			unsigned char    IsSupport30Bit          :1;
			unsigned char    IsSupport36Bit          :1;
			unsigned char    IsSupport48Bit          :1;
			unsigned char    IsSupportAI             :1;
		};
		unsigned char        SupportCaps;
	};
	unsigned short           MaxTMDSClock;
	union
	{
		struct
		{
			unsigned char    CNC0_Graphics           :1;
			unsigned char    CNC1_Photo              :1;
			unsigned char    CNC2_Cinema             :1;
			unsigned char    CNC3_Game               :1;
			unsigned char    RsvdBits1               :1;
			unsigned char    HDMIVideoPresent        :1;
			unsigned char    ILatencyFieldsPresent   :1;
			unsigned char    LatencyFieldsPresent    :1;
		};
		unsigned char        PresentFlags;
	};
	unsigned char            VideoLatency;
	unsigned char            AudioLatency;
	unsigned char            InterlacedVideoLatency;
	unsigned char            InterlacedAudioLatency;
	union
	{
		struct  
		{
			unsigned char    RsvdBits2               :3;
			unsigned char    ImageSize               :2;
			unsigned char    HDMI3DMultiPresent      :2;
			unsigned char    HDMI3DPresent           :1;
		};
		unsigned char        HDMI3DPresentFlags;
	};
	struct  
	{
		unsigned char        HDMI3DLen               :5;
		unsigned char        HDMIVICLen              :3;
	};
	unsigned char            HDMIVIC[MAX_HDMI_VIC_LEN];
	unsigned short           HDMI3DStructAll;
	unsigned short           HDMI3DMask;
	CBIOS_HDMI_3D_FORMAT     HDMI3DForamt[MAX_HDMI_3D_LEN];
	unsigned int             HDMI3DFormatCount;
}CBIOS_HDMI_VSDB_EXTENTION, *PCBIOS_HDMI_VSDB_EXTENTION;

typedef struct _CBIOS_CEA_SVD_DATA
{
	unsigned char        SVDCount;
	unsigned char        SVD[MAX_SVD_COUNT];
}CBIOS_CEA_SVD_DATA, *PCBIOS_CEA_SVD_DATA;

typedef enum _CBIOS_STEREO_VIEW
{
	FIELD_SEQ_RIGHT = 0x1,  // Field sequential stereo, right image when stereo sync signal = 1
	FIELD_SEQ_LEFT,         // Field sequential stereo, left image when stereo sync signal = 1
	TWO_WAY_RIGHT,          // 2-way interleaved stereo, right image on even lines
	TWO_WAY_LEFT,           // 2-way interleaved stereo, left image on even lines
	FOUR_WAY,               // 4-way interleaved stereo
	SIDE_BY_SIDE_INTERLEAVE // Side-by-Side interleaved stereo
}CBIOS_STEREO_VIEW;

typedef struct _CBIOS_MONITOR_MISC_ATTRIB
{
	union
	{
		struct
		{
			unsigned int IsCEA861Monitor    :1;
			unsigned int IsCEA861RGB        :1;
			unsigned int IsCEA861YCbCr422   :1;
			unsigned int IsCEA861YCbCr444   :1;
			unsigned int IsCEA861Audio      :1;
			unsigned int IsCEA861UnderScan  :1;
			unsigned int IsCEA861HDMI       :1;
			unsigned int RsvdBits           :25;
		};
		unsigned int     CEA861MonitorCaps;
	};  
	unsigned int                  TotalNumberOfNativeFormat;
	unsigned char                 Tag;
	unsigned char                 RevisionNumber;
	unsigned char                 OffsetOfDetailedTimingBlock;
	CBIOS_HDMI_VSDB_EXTENTION  VSDBData;
	CBIOS_CEA_SVD_DATA         SVDData[CBIOS_EDIDMAXBLOCKCOUNT - 1];
	// CBIOS_CEA_EXTENED_BLOCK    ExtDataBlock[MAX_CEA_EXT_DATA_BLOCK_NUM];
	bool                       bStereoViewSupport;    // stereo Viewing Support for row-interlace
	CBIOS_STEREO_VIEW          StereoViewType;        // stereo view type
	unsigned char              ManufactureName[2];
	unsigned char              ProductCode[2];
	unsigned char              MonitorName[16];
	unsigned char              SAD_Count;             // at most 15 SADs
	unsigned char              CEA_SADs[15][3];
	unsigned char              SpeakerAllocationData;
	unsigned short             MonitorHorSize;        // monitor screen image horizontal size in millimeter(mm)
	unsigned short             MonitorVerSize;        // monitor screen image vertical size in millimeter(mm)
}CBIOS_MONITOR_MISC_ATTRIB, *PCBIOS_MONITOR_MISC_ATTRIB;

typedef enum _CBIOS_HDMI_AUDIO_FORMAT_TYPE   {
	CBIOS_AUDIO_FORMAT_REFER_TO_STREAM_HEADER,
	CBIOS_AUDIO_FORMAT_LPCM,
	CBIOS_AUDIO_FORMAT_AC_3,
	CBIOS_AUDIO_FORMAT_MPEG_1,
	CBIOS_AUDIO_FORMAT_MP3,
	CBIOS_AUDIO_FORMAT_MPEG_2,
	CBIOS_AUDIO_FORMAT_AAC_LC,
	CBIOS_AUDIO_FORMAT_DTS,
	CBIOS_AUDIO_FORMAT_ATRAC,
	CBIOS_AUDIO_FORMAT_DSD,
	CBIOS_AUDIO_FORMAT_E_AC_3,
	CBIOS_AUDIO_FORMAT_DTS_HD,
	CBIOS_AUDIO_FORMAT_MLP,
	CBIOS_AUDIO_FORMAT_DST,
	CBIOS_AUDIO_FORMAT_WMA_PRO,
	CBIOS_AUDIO_FORMAT_HE_AAC,
	CBIOS_AUDIO_FORMAT_HE_AAC_V2,
	CBIOS_AUDIO_FORMAT_MPEG_SURROUND
}CBIOS_HDMI_AUDIO_FORMAT_TYPE, *PCBIOS_HDMI_AUDIO_FORMAT_TYPE;

typedef struct _CBIOS_HDMI_AUDIO_INFO
{
    CBIOS_HDMI_AUDIO_FORMAT_TYPE Format;
    unsigned int                    MaxChannelNum;
    union
    {
        struct
        {
            unsigned int  SR_32kHz                 :1; /* Bit0 = 1, support sample rate of 32kHz */
            unsigned int  SR_44_1kHz               :1; /* Bit1 = 1, support sample rate of 44.1kHz */
            unsigned int  SR_48kHz                 :1; /* Bit2 = 1, support sample rate of 48kHz */
            unsigned int  SR_88_2kHz               :1; /* Bit3 = 1, support sample rate of 88.2kHz */
            unsigned int  SR_96kHz                 :1; /* Bit4 = 1, support sample rate of 96kHz */
            unsigned int  SR_176_4kHz              :1; /* Bit5 = 1, support sample rate of 176.4kHz */
            unsigned int  SR_192kHz                :1; /* Bit6 = 1, support sample rate of 192kHz */
            unsigned int  Reserved                 :25;
        }SampleRate;

        unsigned int                SampleRateUnit;
    };

    union
    {
        unsigned int Unit;
        
        // for audio format: LPCM
        struct
        {
            unsigned int  BD_16bit                 :1; /* Bit0 = 1, support bit depth of 16 bits */
            unsigned int  BD_20bit                 :1; /* Bit1 = 1, support bit depth of 20 bits */
            unsigned int  BD_24bit                 :1; /* Bit2 = 1, support bit depth of 24 bits */
            unsigned int  Reserved                 :29;
        }BitDepth;

        // for audio format: AC-3, MPEG-1, MP3, MPED-2, AAC LC, DTS, ATRAC
        unsigned int                MaxBitRate; // unit: kHz

        // for audio format: DSD, E-AC-3, DTS-HD, MLP, DST
        unsigned int                AudioFormatDependValue; /* for these audio formats, this value is defined in 
                                                            it's corresponding format-specific documents*/

        // for audio format: WMA Pro
        struct
        {
            unsigned int  Value                    :3;
            unsigned int  Reserved                 :29;
        }Profile;
    };
}CBIOS_HDMI_AUDIO_INFO, *PCBIOS_HDMI_AUDIO_INFO;

typedef struct _CBIOS_EDID_STRUCTURE_DATA
{
	unsigned char				Version;
	CBIOS_S3GMODE_INFO			EstTimings[CBIOS_ESTABLISHMODECOUNT];
	CBIOS_S3GMODE_INFO			StdTimings[CBIOS_STDMODECOUNT];
	CBIOS_MODE_INFO_EXT			DltTimings[CBIOS_DTLMODECOUNT];
	CBIOS_MODE_INFO_EXT			DTDTimings[CBIOS_DTDTIMINGCOUNT];

	CBIOS_MONITOR_MISC_ATTRIB	Attribute;
	CBIOS_HDMI_FORMAT_DESCRIPTOR	HDMIFormat[CBIOS_HDMIFORMATCOUNT];
	CBIOS_HDMI_AUDIO_INFO		HDMIAudioFormat[CBIOS_HDMI_AUDIO_FORMAT_COUNT];
	unsigned int				TotalModeNum;
	unsigned int				TotalHDMIAudioFormatNum;
}CBIOS_EDID_STRUCTURE_DATA, *PCBIOS_EDID_STRUCTURE_DATA;


typedef struct _CBIOS_Module_EDID_ESTTIMINGS
{
	unsigned short	XResolution;
	unsigned short	YResolution;
	unsigned short	RefreshRate;
}CBIOS_Module_EDID_ESTTIMINGS;


class ParseEDIDClass
{
private:
	bool cbEDIDModule_IsEDIDValid(unsigned char* pEDID);
	bool cbEDIDModule_IsEDIDHeaderValid(unsigned char* pEDIDBuffer, unsigned int ulBufferSize);
	unsigned int cbEDIDModule_GetEstablishMode(unsigned char* pEDID, PCBIOS_S3GMODE_INFO pEstablishMode);
	unsigned int cbEDIDModule_GetStandardMode(unsigned char* pEDID, PCBIOS_S3GMODE_INFO pStandardMode);
	unsigned int cbEDIDModule_GetDetailedMode(unsigned char* pEDID, PCBIOS_MODE_INFO_EXT pDetailedMode, unsigned int byTotalModeNum);

	
public:
	bool cbEDIDModule_ParseEDID(unsigned char* pEDID, PCBIOS_EDID_STRUCTURE_DATA pEDIDStruct, unsigned int ulBufferSize);


};