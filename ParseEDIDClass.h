#pragma once

#define		CBIOS_ESTABLISHMODECOUNT		17
#define		CBIOS_STDMODECOUNT				8
#define		CBIOS_DTLMODECOUNT				4
#define		CBIOS_DTDTIMINGCOUNT			6

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