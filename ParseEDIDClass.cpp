#include "ParseEDIDClass.h"

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