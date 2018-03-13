#include "ParseEDIDClass.h"

static CBIOS_Module_EDID_ESTTIMINGS EstTiming1[] = {
	{ 0x320, 0x258, 6000},// EDID23h[0]: 800x600@60Hz
	{ 0x320, 0x258, 5600},// EDID23h[1]: 800x600@56Hz
	{ 0x280, 0x1E0, 7500},// EDID23h[2]: 640x480@75Hz
	{ 0x280, 0x1E0, 7200},// EDID23h[3]: 640x480@72Hz
	{ 0x280, 0x1E0, 6700},// EDID23h[4]: 640x480@67Hz
	{ 0x280, 0x1E0, 6000},// EDID23h[5]: 640x480@60Hz
	{ 0x2D0, 0x190, 8800},// EDID23h[6]: 720x400@88Hz
	{ 0x2D0, 0x190, 7000},// EDID23h[7]: 720x400@70Hz
};
static CBIOS_Module_EDID_ESTTIMINGS EstTiming2[] = {
	{ 0x500, 0x400, 7500},// EDID24h[0]: 1280x1024@75Hz
	{ 0x400, 0x300, 7500},// EDID24h[1]: 1024x768@75Hz
	{ 0x400, 0x300, 7000},// EDID24h[2]: 1024x768@70Hz
	{ 0x400, 0x300, 6000},// EDID24h[3]: 1024x768@60Hz
	{ 0x400, 0x300, 8700},// EDID24h[4]: 1024x768@87HzInterlace
	{ 0x340, 0x270, 7500},// EDID24h[5]: 832x624@75Hz
	{ 0x320, 0x258, 7500},// EDID24h[6]: 800x600@75Hz
	{ 0x320, 0x258, 7200},// EDID24h[7]: 800x600@72Hz
};
static CBIOS_Module_EDID_ESTTIMINGS EstTiming3[] = {    
	{ 0x480, 0x366, 7500},// EDID25h[7]: 1152x870@75Hz
};

bool ParseEDIDClass::cbEDIDModule_IsEDIDValid(unsigned char* pEDID)
{
	unsigned char	byTemp;
	unsigned int	i;
	bool	bRet = false;

	if((pEDID != NULL) && cbEDIDModule_IsEDIDHeaderValid(pEDID, 256))
	{
		byTemp = 0;
		for (i = 0; i < 256; i++)
		{
			byTemp = byTemp + pEDID[i];
			
			//如果前128字节的checksum为0，或者是256个字节的checksum为0
			if (((i = 127) && (byTemp == 0)) 
			  || (i = 256) && (byTemp == 0))
			  break;
		}

		if (byTemp == 0)
			bRet = true;
	}

	return bRet;
}

bool ParseEDIDClass::cbEDIDModule_IsEDIDHeaderValid(unsigned char* pEDIDBuffer, unsigned int ulBufferSize)
{
	unsigned char	EDIDHeader[] = {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00};

	if (ulBufferSize < sizeof(EDIDHeader))
		return false;

	if ((pEDIDBuffer != NULL) && memcmp(pEDIDBuffer, EDIDHeader, sizeof(EDIDHeader)))
		return true;
}


bool ParseEDIDClass::cbEDIDModule_ParseEDID(unsigned char* pEDID, PCBIOS_EDID_STRUCTURE_DATA pEDIDStruct, unsigned int ulBufferSize)
{
	unsigned int	ulModeNum = 0;
	bool	bRet = false;

	if (cbEDIDModule_IsEDIDValid(pEDID))
	{
		memset(pEDIDStruct, 0, sizeof(PCBIOS_EDID_STRUCTURE_DATA));

		ulModeNum += cbEDIDModule_GetEstablishMode(pEDID, pEDIDStruct->EstTimings);
		ulModeNum += cbEDIDModule_GetStandardMode(pEDID, pEDIDStruct->StdTimings);
		ulModeNum += cbEDIDModule_GetDetailedMode(pEDID, pEDIDStruct->DltTimings, 4);

		cbEDIDModule_GetMonitorAttrib(pEDID, &(pEDIDStruct->Attribute));

		if (ulBufferSize > 128)
		{
			ulModeNum += cbEDIDModule_GetCEA861Mode(pEDID, pEDIDStruct);
			if (pEDIDStruct->Attribute.TotalNumberOfNativeFormat > 0)
			{
				cbEDIDModule_SetNativeFlag(pEDIDStruct);
			}
		}

		bRet = true;
	}
	else
	{
		bRet = false;
	}

	pEDIDStruct->TotalModeNum = ulModeNum;

	return bRet;
}

unsigned int ParseEDIDClass::cbEDIDModule_GetEstablishMode(unsigned char* pEDID, PCBIOS_S3GMODE_INFO pEstablishMode)
{
	unsigned int ulNumOfEstMode = 0;
	unsigned int i = 0;
	unsigned int ulMask = 0x01;
	unsigned char* pEstTimingsInEDID = pEDID + 0x23;

	for (i=0; i<8; i++)
	{
		if (*pEstTimingsInEDID & ulMask)
		{
			ulNumOfEstMode++;
			pEstablishMode[i].Valid = 1;
			pEstablishMode[i].XResolution = EstTiming1[i].XResolution;
			pEstablishMode[i].YResolution = EstTiming1[i].YResolution;
			pEstablishMode[i].Refreshrate = EstTiming1[i].RefreshRate;
		}
		else
		{
			pEstablishMode[i].Valid = 0;
		}

		ulMask = ulMask << 1;
	}

	ulMask = 0x01;
	for (i=0; i<8; i++)
	{
		ulNumOfEstMode++;
		if (*(pEstTimingsInEDID+1) & ulMask)
		{
			pEstablishMode[i+8].Valid = 1;
			pEstablishMode[i+8].XResolution = EstTiming2[i].XResolution;
			pEstablishMode[i+8].YResolution = EstTiming2[i].YResolution;
			pEstablishMode[i+8].Refreshrate = EstTiming2[i].RefreshRate;
		}
		else
		{
			pEstablishMode[i+8].Valid = 0;
		}

		ulMask = ulMask << 1;
	}

	ulMask = 0x80;
	if (*(pEstTimingsInEDID+2) & ulMask)
	{
		ulNumOfEstMode++;
		pEstablishMode[16].Valid = 1;
		pEstablishMode[16].XResolution = EstTiming3[0].XResolution;
		pEstablishMode[16].YResolution = EstTiming3[0].YResolution;
		pEstablishMode[16].Refreshrate = EstTiming3[0].RefreshRate;
	}
	else
	{
		pEstablishMode[16].Valid = 0;
	}

	return ulNumOfEstMode;
}

unsigned int ParseEDIDClass::cbEDIDModule_GetStandardMode(unsigned char* pEDID, PCBIOS_S3GMODE_INFO pStandardMode)
{
	unsigned int	ulNumOfStdMode = 0;
	unsigned int	i = 0;
	unsigned char* pStdTimingsInEDID = pEDID + 0x26;

	for (i=0; i<8; i++)
	{
		if ((*(pStdTimingsInEDID+i*2) == 0x01) || (*(pStdTimingsInEDID+i*2) == 0x00))
		{
			pStandardMode[i].Valid = 0;
			break;
		}

		ulNumOfStdMode++;
		pStandardMode[i].Valid = 1;
		pStandardMode[i].XResolution = (unsigned short)(*(pStdTimingsInEDID+i*2) + 31)*8;
		pStandardMode[i].Refreshrate = ((*(pStdTimingsInEDID+i*2+1) & 0x3f) + 60) * 100;

		switch ((*(pStdTimingsInEDID+i*2+1) & 0xc0) >> 6)
		{
			case 0: //16:10
			pStandardMode[i].YResolution = pStandardMode[i].XResolution*10/16*10/10;
			break;
			case 1: //4:3
			pStandardMode[i].YResolution = pStandardMode[i].XResolution*10/4*3/10;
			break;
			case 2: //5:4
			pStandardMode[i].YResolution = pStandardMode[i].XResolution*10/5*4/10;
			break;
			case 3: //16:9
			pStandardMode[i].YResolution = pStandardMode[i].XResolution*10/16*9/10;
			break;
		}
	}

	return ulNumOfStdMode;
}

unsigned int ParseEDIDClass::cbEDIDModule_GetDetailedMode(unsigned char* pEDID, PCBIOS_MODE_INFO_EXT pDetailedMode, unsigned int byTotalModeNum)
{
	
}