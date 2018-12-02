/*******************************************************************************
* © 2011-2017, Cypress Semiconductor Corporation
* or a subsidiary of Cypress Semiconductor Corporation. All rights
* reserved.
* 
* This software, including source code, documentation and related
* materials (“Software”), is owned by Cypress Semiconductor
* Corporation or one of its subsidiaries (“Cypress”) and is protected by
* and subject to worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software (“EULA”).
* 
* If no EULA applies, Cypress hereby grants you a personal, non-
* exclusive, non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress’s
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* 
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. Cypress reserves the right to make
* changes to the Software without notice. Cypress does not assume any
* liability arising out of the application or use of the Software or any
* product or circuit described in the Software. Cypress does not
* authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death (“High Risk Product”). By
* including Cypress’s product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
********************************************************************************/
//
// Cpp_Ex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "tchar.h"
#include "atlbase.h"
#include "conio.h"
#include <iostream>
#include <vector>

#include "ppcom.h"

using namespace std;

IDispatch* pIDispatch = NULL;
std::string sErrorMsg;
char InputPath[MAX_PATH] = "\\..\\HEX-file\\PSoC4.hex";

//DispIDs for each function used in the Example
//They are initialized once after COM-object is created by GetDispIDsByName() function
DISPID dispID__StartSelfTerminator = 0;
DISPID dispID_OpenPort = 0;
DISPID dispID_ClosePort = 0;
DISPID dispID_GetPorts = 0;
DISPID dispID_SetPowerVoltage = 0;
DISPID dispID_PowerOn = 0;
DISPID dispID_SetProtocol = 0;
DISPID dispID_SetProtocolConnector = 0;
DISPID dispID_SetProtocolClock = 0;
DISPID dispID_HEX_ReadFile = 0;
DISPID dispID_SetAcquireMode = 0;
DISPID dispID_DAP_Acquire = 0;
DISPID dispID_DAP_ReleaseChip = 0;
DISPID dispID_HEX_ReadJtagID = 0;
DISPID dispID_HEX_ReadChipProtection = 0;
DISPID dispID_ReadHexChecksum = 0;
DISPID dispID_PSoC4_GetSiliconID = 0;
DISPID dispID_PSoC4_GetFlashInfo = 0;
DISPID dispID_PSoC4_ReadProtection = 0;
DISPID dispID_PSoC4_EraseAll = 0;
DISPID dispID_PSoC4_WriteProtection = 0;
DISPID dispID_PSoC4_ProgramRowFromHex = 0;
DISPID dispID_PSoC4_VerifyRowFromHex = 0;
DISPID dispID_PSoC4_CheckSum = 0;
DISPID dispID_PSoC4_ProtectAll = 0;
DISPID dispID_PSoC4_VerifyProtect = 0;
DISPID dispID_PSoC4_WriteRow = 0;
DISPID dispID_PSoC4_ReadRow = 0;

//Chip Level Protection constants
const int CHIP_PROT_VIRGIN = 0x00;
const int CHIP_PROT_OPEN = 0x01;
const int CHIP_PROT_PROTECTED = 0x02;
const int CHIP_PROT_KILL = 0x04;
const int CHIP_PROT_MASK = 0x0F;

//----------------------------------------------------------------------------------------
// Auxiliary routines for working with Automation types
//----------------------------------------------------------------------------------------
int GetDispIDsByName()
{
	int hr = S_OK;

	LPOLESTR functionName;
	//_StartSelfTerminator
	functionName = L"_StartSelfTerminator";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID__StartSelfTerminator);
	if (FAILED(hr)) return hr;
	//OpenPort
	functionName = L"OpenPort";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_OpenPort);
	if (FAILED(hr)) return hr;
	//ClosePort
	functionName = L"ClosePort";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_ClosePort);
	if (FAILED(hr)) return hr;
	//GetPorts
	functionName = L"GetPorts";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_GetPorts);
	if (FAILED(hr)) return hr;
	//SetPowerVoltage
	functionName = L"SetPowerVoltage";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_SetPowerVoltage);
	if (FAILED(hr)) return hr;
	//PowerOn
	functionName = L"PowerOn";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_PowerOn);
	if (FAILED(hr)) return hr;
    //SetProtocol
	functionName = L"SetProtocol";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_SetProtocol);
	if (FAILED(hr)) return hr;
	//SetProtocolConnector
	functionName = L"SetProtocolConnector";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_SetProtocolConnector);
	if (FAILED(hr)) return hr;
	//SetProtocolClock
	functionName = L"SetProtocolClock";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_SetProtocolClock);
	if (FAILED(hr)) return hr;
	//HEX_ReadFile
	functionName = L"HEX_ReadFile";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_HEX_ReadFile);
	if (FAILED(hr)) return hr;
	//SetAcquireMode
	functionName = L"SetAcquireMode";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_SetAcquireMode);
	if (FAILED(hr)) return hr;
	//DAP_Acquire
	functionName = L"DAP_Acquire";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_DAP_Acquire);
	if (FAILED(hr)) return hr;
	//DAP_ReleaseChip
	functionName = L"DAP_ReleaseChip";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_DAP_ReleaseChip);
	if (FAILED(hr)) return hr;
	//HEX_ReadJtagID
	functionName = L"HEX_ReadJtagID";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_HEX_ReadJtagID);
	if (FAILED(hr)) return hr;
	//HEX_ReadChipProtection
	functionName = L"HEX_ReadChipProtection";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_HEX_ReadChipProtection);
	if (FAILED(hr)) return hr;
	//ReadHexChecksum
	functionName = L"ReadHexChecksum";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_ReadHexChecksum);
	if (FAILED(hr)) return hr;
	//PSoC4_GetSiliconID
	functionName = L"PSoC4_GetSiliconID";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_PSoC4_GetSiliconID);
	if (FAILED(hr)) return hr;
	//PSoC4_GetFlashInfo
	functionName = L"PSoC4_GetFlashInfo";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_PSoC4_GetFlashInfo);
	if (FAILED(hr)) return hr;
	//PSoC4_ReadProtection
	functionName = L"PSoC4_ReadProtection";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_PSoC4_ReadProtection);
	if (FAILED(hr)) return hr;
	//PSoC4_EraseAll
	functionName = L"PSoC4_EraseAll";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_PSoC4_EraseAll);
	if (FAILED(hr)) return hr;
	//PSoC4_WriteProtection
	functionName = L"PSoC4_WriteProtection";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_PSoC4_WriteProtection);
	if (FAILED(hr)) return hr;
	//PSoC4_ProgramRowFromHex
	functionName = L"PSoC4_ProgramRowFromHex";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_PSoC4_ProgramRowFromHex);
	if (FAILED(hr)) return hr;
	//PSoC4_VerifyRowFromHex
	functionName = L"PSoC4_VerifyRowFromHex";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_PSoC4_VerifyRowFromHex);
	if (FAILED(hr)) return hr;
	//PSoC4_CheckSum
	functionName = L"PSoC4_CheckSum";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_PSoC4_CheckSum);
	if (FAILED(hr)) return hr;
	//PSoC4_ProtectAll
	functionName = L"PSoC4_ProtectAll";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_PSoC4_ProtectAll);
	if (FAILED(hr)) return hr;
	//PSoC4_VerifyProtect
	functionName = L"PSoC4_VerifyProtect";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_PSoC4_VerifyProtect);
	if (FAILED(hr)) return hr;
	//PSoC4_WriteRow
	functionName = L"PSoC4_WriteRow";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_PSoC4_WriteRow);
	if (FAILED(hr)) return hr;
	//PSoC4_ReadRow
	functionName = L"PSoC4_ReadRow";
	hr = pIDispatch->GetIDsOfNames(IID_NULL, &functionName,1,LOCALE_SYSTEM_DEFAULT,&dispID_PSoC4_ReadRow);
	if (FAILED(hr)) return hr;
	
	return hr;
}

void ConvertSA2ByteVector(VARIANT arrayIN, std::vector<BYTE> &vector)
{
	//Extract SA from VARIANT
	SAFEARRAY* psa;
	if (!(arrayIN.vt & VT_ARRAY)) {  vector.resize(0); return; }
	if (arrayIN.vt & VT_BYREF)
		psa = *(arrayIN.pparray);
	else
		psa = arrayIN.parray;

	//Convert SA to vector
	long lLBound, lUBound;
	SafeArrayGetLBound(psa, 1, &lLBound);
	SafeArrayGetUBound(psa, 1, &lUBound);
	int size = lUBound - lLBound + 1;
	vector.resize(size);
	long i,j;
	for (j=0, i=lLBound; i<=lUBound; i++, j++){
		BYTE b;
		SafeArrayGetElement(psa,&i,&b);
		vector[j] = b;
	}
}

void ConvertSA2ByteVector(VARIANT arrayIN, std::vector<std::vector<LONG>> &vector)
{
	//Extract SA from VARIANT
	SAFEARRAY* psa;
	if (!(arrayIN.vt & VT_ARRAY)) {  vector.resize(0); return; }
	if (arrayIN.vt & VT_BYREF)
		psa = *(arrayIN.pparray);
	else
		psa = arrayIN.parray;

	//Convert SA to vector
	long lLBound1, lUBound1;
	SafeArrayGetLBound(psa, 1, &lLBound1);
	SafeArrayGetUBound(psa, 1, &lUBound1);
	int size1 = lUBound1 - lLBound1 + 1;
	long lLBound2, lUBound2;
	SafeArrayGetLBound(psa, 2, &lLBound2);
	SafeArrayGetUBound(psa, 2, &lUBound2);
	int size2 = lUBound2 - lLBound2 + 1;
	vector.resize(size1);
	long i1,j1,i2,j2;
	for (j1=0, i1=lLBound1; i1<=lUBound1; i1++, j1++){
		vector[j1].resize(size2);
		for (j2=0, i2=lLBound2; i2<=lUBound2; i2++, j2++){
			long index[2] = {i1,i2};
			long element;
			SafeArrayGetElement(psa,index,&element);
			vector[j1][j2] = element;
		}
	}
}

void ConvertByteVector2SA(std::vector<BYTE> vector, VARIANT *arrayOUT)
{
	SAFEARRAY* psa;
	SAFEARRAYBOUND rgsabound[1];
	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = (ULONG)vector.size();
	psa = SafeArrayCreate(VT_UI1,1,rgsabound);
	for (UINT i=0; i<vector.size(); i++){
		SafeArrayPutElement(psa, (long *) &i, &vector[i]);
	}

	//return data in VARIANT
	VariantInit(arrayOUT);
	V_VT(arrayOUT) = VT_ARRAY | VT_UI1;
	V_ARRAY(arrayOUT) = psa;
}

//----------------------------------------------------------------------------------
// COM-object's wrapping functions
//----------------------------------------------------------------------------------

long ppStartSelfTerminator(long ClientProcessID)
{
	DISPID dispid=dispID__StartSelfTerminator;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 1;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_I4;
	dispparams.rgvarg[0].lVal = ClientProcessID;	
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	//Free allocated resources
	delete[] pArg;	
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppOpenPort(std::string portName, std::string &strError)
{
	DISPID dispid=dispID_OpenPort;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 2;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	USES_CONVERSION;
	BSTR bstrPort = ::SysAllocString(A2W(portName.c_str()));
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_BSTR;
	dispparams.rgvarg[1].bstrVal = bstrPort;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);
	
	
	strError = W2A(bstrError);
	//Free allocated resources
	delete[] pArg;
	::SysFreeString(bstrPort);
	::SysFreeString(bstrError);
	
	return vaResult.lVal;
}

long ppClosePort(std::string &strError)
{
	DISPID dispid=dispID_ClosePort;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 1;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);	
	//Free allocated resources
	delete[] pArg;
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppGetPorts(std::vector<std::string> &portNames, std::string &strError)
{
	DISPID dispid=dispID_GetPorts;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 2;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	VARIANT varPorts;
	VariantInit(&varPorts);
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_VARIANT | VT_BYREF;
	dispparams.rgvarg[1].pvarVal = &varPorts;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);
	USES_CONVERSION;
	strError = W2A(bstrError);
	//Translate Result into std::vector<std::string>
	long lLBound, lUBound;
	SAFEARRAY* psa = varPorts.parray;
	SafeArrayGetLBound(psa, 1, &lLBound);
	SafeArrayGetUBound(psa, 1, &lUBound);
	int size = lUBound - lLBound + 1;
	portNames.resize(size);
	long i,j;
	for (j=0, i=lLBound; i<=lUBound; i++, j++){
		BSTR bPort;
		SafeArrayGetElement(psa,&i,&bPort);
		USES_CONVERSION;
		portNames[j] = W2A(bPort);
	}
	//Free allocated resources
	delete[] pArg;	
	VariantClear(&varPorts);
	::SysFreeString(bstrError);
	
	return vaResult.lVal;
}

void SetErrorMsg(std::string errorMsg)
{
	errorMsg = sErrorMsg;
}

std::string GetErrorMsg()
{
	return sErrorMsg;
}

long ppSetPowerVoltage(std::string voltage, std::string &strError)
{
	DISPID dispid=dispID_SetPowerVoltage;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 2;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	USES_CONVERSION;
	BSTR bstrVoltage = ::SysAllocString(A2W(voltage.c_str()));
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_BSTR;
	dispparams.rgvarg[1].bstrVal = bstrVoltage;		
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	strError = W2A(bstrError);	
	//Free allocated resources
	delete[] pArg;
	::SysFreeString(bstrVoltage);
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppPowerOn(std::string &strError)
{
	DISPID dispid=dispID_PowerOn;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 1;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);	
	//Free allocated resources
	delete[] pArg;
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppSetProtocol(enumInterfaces protocol, std::string &strError)
{
	DISPID dispid=dispID_SetProtocol;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 2;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_I4;
	dispparams.rgvarg[1].lVal = protocol;	
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);
	//Free allocated resources
	delete[] pArg;	
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppSetProtocolConnector(long connector, std::string &strError)
{
	DISPID dispid=dispID_SetProtocolConnector;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 2;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_I4;
	dispparams.rgvarg[1].lVal = connector;	
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);
	//Free allocated resources
	delete[] pArg;	
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppSetProtocolClock(enumFrequencies clock, std::string &strError)
{
	DISPID dispid=dispID_SetProtocolClock;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 2;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_I4;
	dispparams.rgvarg[1].lVal = clock;	
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);
	//Free allocated resources
	delete[] pArg;	
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppHEX_ReadFile(std::string filename, long &imageSize, std::string &strError)
{
	DISPID dispid=dispID_HEX_ReadFile;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 3;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	USES_CONVERSION;
	BSTR bstrFileName = ::SysAllocString(A2W(filename.c_str()));
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_I4 | VT_BYREF;
	dispparams.rgvarg[1].plVal = &imageSize;
	dispparams.rgvarg[2].vt = VT_BSTR;
	dispparams.rgvarg[2].bstrVal = bstrFileName;		
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	strError = W2A(bstrError);	
	//Free allocated resources
	delete[] pArg;
	::SysFreeString(bstrFileName);
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppSetAcquireMode(std::string mode, std::string &strError)
{
	DISPID dispid=dispID_SetAcquireMode;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 2;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	USES_CONVERSION;
	BSTR bstrMode = ::SysAllocString(A2W(mode.c_str()));	
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_BSTR;
	dispparams.rgvarg[1].bstrVal = bstrMode;		
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	strError = W2A(bstrError);	
	//Free allocated resources
	delete[] pArg;
	::SysFreeString(bstrMode);
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppDAP_Acquire(std::string &strError)
{
	DISPID dispid=dispID_DAP_Acquire;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 1;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);	
	//Free allocated resources
	delete[] pArg;
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppDAP_ReleaseChip(std::string &strError)
{
	DISPID dispid=dispID_DAP_ReleaseChip;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 1;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);	
	//Free allocated resources
	delete[] pArg;
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppHEX_ReadChipProtection(std::vector<BYTE> &chipData, std::string &strError)
{
	DISPID dispid=dispID_HEX_ReadChipProtection;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 2;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	VARIANT varData;
	VariantInit(&varData);
	BSTR bstrError=0;
	
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_VARIANT | VT_BYREF;
	dispparams.rgvarg[1].pvarVal = &varData;

	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);
	ConvertSA2ByteVector(varData,chipData);
	//Free allocated resources
	delete[] pArg;	
	::SysFreeString(bstrError);
	VariantClear(&varData);

	return vaResult.lVal;
}

long ppPSoC4_GetSiliconID(std::vector<BYTE> &jtagID, std::string &strError)
{
	DISPID dispid=dispID_PSoC4_GetSiliconID;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 2;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	VARIANT varJtagID;
	VariantInit(&varJtagID);
	BSTR bstrError=0;
	
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_VARIANT | VT_BYREF;
	dispparams.rgvarg[1].pvarVal = &varJtagID;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);
	ConvertSA2ByteVector(varJtagID,jtagID);
	//Free allocated resources
	delete[] pArg;	
	::SysFreeString(bstrError);
	VariantClear(&varJtagID);

	return vaResult.lVal;
}

long ppHEX_ReadJtagID(std::vector<BYTE> &jtagID, std::string &strError)
{
	DISPID dispid=dispID_HEX_ReadJtagID;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 2;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	VARIANT varJtagID;
	VariantInit(&varJtagID);
	BSTR bstrError=0;
	
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_VARIANT | VT_BYREF;
	dispparams.rgvarg[1].pvarVal = &varJtagID;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);
	ConvertSA2ByteVector(varJtagID,jtagID);
	//Free allocated resources
	delete[] pArg;	
	::SysFreeString(bstrError);
	VariantClear(&varJtagID);

	return vaResult.lVal;
}

long ppPSoC4_ReadProtection(std::vector<BYTE> &flashProtect, std::vector<BYTE> &chipProtect, std::string &strError)
{
	DISPID dispid=dispID_PSoC4_ReadProtection;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 3;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	VARIANT varData1, varData2;
	VariantInit(&varData1);
	VariantInit(&varData2);
	BSTR bstrError=0;
	
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_VARIANT | VT_BYREF;
	dispparams.rgvarg[1].pvarVal = &varData1;
	dispparams.rgvarg[2].vt = VT_VARIANT | VT_BYREF;
	dispparams.rgvarg[2].pvarVal = &varData2;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);
	ConvertSA2ByteVector(varData1,chipProtect);
	ConvertSA2ByteVector(varData2,flashProtect);
	//Free allocated resources
	delete[] pArg;	
	::SysFreeString(bstrError);
	VariantClear(&varData1);
	VariantClear(&varData2);

	return vaResult.lVal;
}

long ppPSoC4_EraseAll(std::string &strError)
{
	DISPID dispid=dispID_PSoC4_EraseAll;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 1;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);	
	//Free allocated resources
	delete[] pArg;
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppPSoC4_WriteProtection(std::vector<BYTE> flashProtect, std::vector<BYTE> chipProtect, std::string &strError)
{
	DISPID dispid=dispID_PSoC4_WriteProtection;
	
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 3;	
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);	
	//Convert hexData into SafeArray
	VARIANT varData1, varData2;
	ConvertByteVector2SA(chipProtect, &varData1);
	ConvertByteVector2SA(flashProtect, &varData2);

	//Initialize Parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_ARRAY | VT_UI1;
	dispparams.rgvarg[1].parray = varData1.parray;
	dispparams.rgvarg[1].vt = VT_ARRAY | VT_UI1;
	dispparams.rgvarg[1].parray = varData2.parray;
	
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);	
	//Free allocated resources
	delete[] pArg;
	::SysFreeString(bstrError);
	VariantClear(&varData1);
	VariantClear(&varData2);
	
	return vaResult.lVal;
}

long ppPSoC4_CheckSum(long rowID, long &checksum, std::string &strError)
{
	DISPID dispid=dispID_PSoC4_CheckSum;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 3;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_I4 | VT_BYREF;
	dispparams.rgvarg[1].plVal = &checksum;
	dispparams.rgvarg[2].vt = VT_I4;
	dispparams.rgvarg[2].lVal = rowID;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);
	//Free allocated resources
	delete[] pArg;	
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppPSoC4_ProgramRowFromHex(long rowID, std::string &strError)
{
	DISPID dispid=dispID_PSoC4_ProgramRowFromHex;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 2;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_I4;
	dispparams.rgvarg[1].lVal = rowID;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);
	//Free allocated resources
	delete[] pArg;	
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppPSoC4_GetFlashInfo(long &rowsPerArray, long &rowSize, std::string &strError)
{
	DISPID dispid=dispID_PSoC4_GetFlashInfo;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 3;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_I4 | VT_BYREF;
	dispparams.rgvarg[1].plVal = &rowSize;
	dispparams.rgvarg[2].vt = VT_I4 | VT_BYREF;
	dispparams.rgvarg[2].plVal = &rowsPerArray;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);
	//Free allocated resources
	delete[] pArg;	
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppPSoC4_VerifyRowFromHex(long rowID, long &verResult, std::string &strError)
{
	DISPID dispid=dispID_PSoC4_GetFlashInfo;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 3;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_I4 | VT_BYREF;
	dispparams.rgvarg[1].plVal = &verResult;
	dispparams.rgvarg[2].vt = VT_I4;
	dispparams.rgvarg[2].lVal = rowID;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);
	//Free allocated resources
	delete[] pArg;	
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppPSoC4_ProtectAll(std::string &strError)
{
	DISPID dispid=dispID_PSoC4_ProtectAll;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 1;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);	
	//Free allocated resources
	delete[] pArg;
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppPSoC4_VerifyProtect(std::string &strError)
{
	DISPID dispid=dispID_PSoC4_VerifyProtect;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 1;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);	
	//Free allocated resources
	delete[] pArg;
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppHEX_ReadChecksum( unsigned short &checksum, std::string &strError)
{
	DISPID dispid=dispID_ReadHexChecksum;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 2;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_UI2 | VT_BYREF;
	dispparams.rgvarg[1].puiVal = &checksum;	
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);	
	//Free allocated resources
	delete[] pArg;
	::SysFreeString(bstrError);

	return vaResult.lVal;
}

long ppPSoC4_WriteRow(long rowID, std::vector<BYTE> writeData, std::string &strError)
{
	DISPID dispid=dispID_PSoC4_WriteRow;
	
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 3;	
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);	
	//Convert hexData into SafeArray
	VARIANT varData;
	ConvertByteVector2SA(writeData, &varData);

	//Initialize Parameters
	BSTR bstrError=0;
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_ARRAY | VT_UI1;
	dispparams.rgvarg[1].parray = varData.parray;
	dispparams.rgvarg[2].vt = VT_I4;
	dispparams.rgvarg[2].lVal = rowID;
	
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);	
	//Free allocated resources
	delete[] pArg;
	::SysFreeString(bstrError);
	VariantClear(&varData);
	
	return vaResult.lVal;
}

long ppPSoC4_ReadRow(long rowID, std::vector<BYTE> &readData, std::string &strError)
{
	DISPID dispid=dispID_PSoC4_ReadRow;
	// Set up parameters
	DISPPARAMS dispparams;
	memset( &dispparams, 0, sizeof( DISPPARAMS ));
	dispparams.cArgs = 3;
	// Allocate memory for parameters
	VARIANTARG* pArg = new VARIANTARG[dispparams.cArgs];
	dispparams.rgvarg = pArg;
	memset( pArg, 0, sizeof(VARIANT) * dispparams.cArgs);
	//Initialize parameters
	VARIANT varData;
	VariantInit(&varData);
	BSTR bstrError=0;
	
	dispparams.rgvarg[0].vt = VT_BSTR | VT_BYREF;
	dispparams.rgvarg[0].pbstrVal = &bstrError;
	dispparams.rgvarg[1].vt = VT_VARIANT | VT_BYREF;
	dispparams.rgvarg[1].pvarVal = &varData;
	dispparams.rgvarg[2].vt = VT_I4;
	dispparams.rgvarg[2].lVal = rowID;
	//Init Result (Return Value)
	VARIANTARG vaResult;
	VariantInit( &vaResult );

	HRESULT hr;
	hr = pIDispatch->Invoke(dispid,	IID_NULL, GetUserDefaultLCID(),	DISPATCH_METHOD,
							&dispparams, &vaResult, NULL, NULL);

	USES_CONVERSION;
	strError = W2A(bstrError);
	ConvertSA2ByteVector(varData,readData);
	//Free allocated resources
	delete[] pArg;	
	::SysFreeString(bstrError);
	VariantClear(&varData);

	return vaResult.lVal;
}

//----------------------------------------------------------------------------------
// Usage Example
//----------------------------------------------------------------------------------
long OpenPort()
{
	long hr;
    //Open Port - get first MiniProg3 port in the ports list
	std::vector<std::string> ports;
    hr = ppGetPorts(ports, sErrorMsg);
    if (!SUCCEEDED(hr)) return hr;
    
    if (ports.size() <= 0)
    {
		SetErrorMsg("Connect any Programmer to PC");
        return -1;
    }

	bool bFound = false;
	std::string portName = "";
    for (UINT i = 0; i < ports.size(); i++) {
		if ((ports[i].find("MiniProg3")==0) || (ports[i].find("TrueTouchBridge")==0) || (ports[i].find("KitProg")==0) ) {
			portName = ports[i];
            bFound = true;
            break;
         }
    }

    if (!bFound) 
	{
		SetErrorMsg("Connect any MiniProg3/TrueTouchBridge/KitProg device to the PC");
        return -1;
    }

	//Port should be opened just once to connect Programmer device (MiniProg1/3,etc).
	//After that you can use Chip-/Programmer- specific APIs as long as you need.
	//No need to repoen port when you need to acquire chip 2nd time, just call Acquire() again.
    //This is true for all other APIs which get available once port is opened.
	//You have to call OpenPort() again if port was closed by ClosePort() method, or 
    //when there is a need to connect to other programmer, or
    //if programmer was physically reconnected to USB-port.

	hr = ppOpenPort(portName, sErrorMsg);
            
    return hr;
}

long ClosePort()
{
	long hr;
	std:string sErrorMsg;

	hr = ppClosePort(sErrorMsg);
	
	return hr;
}

long CheckHexAndDeviceCompatibility(bool &result)
{
    long hr;	
    std::vector<byte> hexJtagID, chipJtagID;
    result = true;

    //Read silicon ID from chip
    hr = ppPSoC4_GetSiliconID(chipJtagID, sErrorMsg);
    if (!SUCCEEDED(hr)) return hr;
    
    //Read silicon ID from hex
    hr = ppHEX_ReadJtagID(hexJtagID, sErrorMsg);
    if (!SUCCEEDED(hr)) return hr;    

    result = true;
    // Currently this cycle is commented, since the real silicon ID is not generated by PSoC Creator
    for (byte i = 0; i < 4; i++)
    {
        if (i == 2) continue; //ignore revision, 11(AA),12(AB),13(AC), etc
        if (hexJtagID[i] != chipJtagID[i])
        {
            result = false;
            break;
        }
    }

    return S_OK;
}

long InitializePort()
{
    long hr;

    //Setup Power - "3.3V" and internal for reset mode
    ppSetPowerVoltage("3.3", sErrorMsg);
	hr = ppPowerOn(sErrorMsg);
    if (!SUCCEEDED(hr)) return hr;
	
	//Set protocol
    hr = ppSetProtocol(enumInterfaces::SWD, sErrorMsg); //SWD-protocol
    if (!SUCCEEDED(hr)) return hr;
    //For MiniProg3 - Set protocol, connector and frequency (do not check result, since it will fail for TTBridge - not supported)
    ppSetProtocolConnector(0, sErrorMsg); //5-pin connector
	ppSetProtocolClock(enumFrequencies::FREQ_03_0, sErrorMsg); //3.0 MHz clock on SWD bus

	return hr;
}

long PSoC4_IsChipNotProtected()
{
    long hr;

	std::vector<byte> flashProt, chipProt;

    //Chip Level Protection reliably can be read by below API (available in VIRGIN, OPEN, PROTECTED modes)
    //This API uses SROM call - to read current status of CPUSS_PROTECTION register (privileged)
    //This register contains current protection mode loaded from SFLASH during boot-up.
    hr = ppPSoC4_ReadProtection(flashProt, chipProt, sErrorMsg);
    if (!SUCCEEDED(hr)) return E_FAIL; //consider chip as protected if any communication failure

    //Check Result
    if ((chipProt[0] & CHIP_PROT_PROTECTED) == CHIP_PROT_PROTECTED)
    {
        sErrorMsg = "Chip is in PROTECTED mode. Any access to Flash is suppressed.";
        return E_FAIL;
    }

    return S_OK;
}

long PSoC4_EraseAll()
{
    long hr;

    //Check chip level protection here. If PROTECTED then move to OPEN by PSoC4_WriteProtection() API.
    //Otherwise use PSoC4_EraseAll() - in OPEN/VIRGIN modes.
    hr = PSoC4_IsChipNotProtected();
    if (SUCCEEDED(hr)) //OPEN mode
    {
        //Erase All - Flash and Protection bits. Still be in OPEN mode.
        hr = ppPSoC4_EraseAll(sErrorMsg);
    }
    else
    {   //Move to OPEN from PROTECTED. It automatically erases Flash and its Protection bits.
		std::vector<byte> flashProt; // do not care in PROTECTED mode
        std::vector<byte> chipProt; //move to OPEN
		chipProt.push_back(CHIP_PROT_OPEN);

        hr = ppPSoC4_WriteProtection(flashProt, chipProt, sErrorMsg);
        if (!SUCCEEDED(hr)) return hr;

        //Need to reacquire chip here to boot in OPEN mode.
        //ChipLevelProtection is applied only after Reset.
        hr = ppDAP_Acquire(sErrorMsg);
    }
    return hr;
}

long PSoC4_GetTotalFlashRowsCount(long flashSize, long &totalRows, long &rowSize)
{
    long hr, rowsPerArray;
    totalRows = 0;

    hr = ppPSoC4_GetFlashInfo(rowsPerArray, rowSize, sErrorMsg);
    if (!SUCCEEDED(hr)) return hr;

    totalRows = flashSize / rowSize;

    return hr;
}

long ProgramFlash(int flashSize)
{
    long hr = 0, totalRows = 0, rowSize = 0;
    hr = PSoC4_GetTotalFlashRowsCount(flashSize, totalRows, rowSize);
    if (!SUCCEEDED(hr)) return hr;

    //Program Flash array
    for (int i = 0; i < totalRows; i++)
    {
        hr = ppPSoC4_ProgramRowFromHex(i, sErrorMsg);
        if (!SUCCEEDED(hr)) return hr;
    }

    return hr;
}

long PSoC4_VerifyFlash(long flashSize)
{
    long hr = 0, totalRows = 0, rowSize = 0;
    hr = PSoC4_GetTotalFlashRowsCount(flashSize, totalRows, rowSize);
    if (!SUCCEEDED(hr)) return hr;

    //Program Flash array
    for (long i = 0; i < totalRows; i++)
    {
        long verResult;
        hr = ppPSoC4_VerifyRowFromHex(i, verResult, sErrorMsg);
        if (!SUCCEEDED(hr)) return hr;
        if (verResult == 0)
        {
			printf("Verification failed on 0x%x row.", i);
            return E_FAIL;
        }
    }
    return hr;
}

long ProgramAll()
{
    int hr;

	TCHAR buffer[MAX_PATH];
	GetCurrentDirectory(sizeof(buffer),buffer);
	std::string filePath(CW2A(buffer).m_psz);
	filePath.append(InputPath);

    //Port Initialization
    hr = InitializePort();
	if (!SUCCEEDED(hr)) return hr;

    // Set Hex File
    long hexImageSize;
    hr = ppHEX_ReadFile(filePath, hexImageSize, sErrorMsg);
    if (!SUCCEEDED(hr)) return hr;

    //Read chip level protection from hex and check Chip Level Protection mode
    //If it is VIRGIN then don't allow Programming, since it can destroy chip
	std::vector<byte> data;
    hr = ppHEX_ReadChipProtection(data, sErrorMsg);
    if (!SUCCEEDED(hr)) return hr;
    byte hex_chipProt = data[0];

    if (hex_chipProt == CHIP_PROT_VIRGIN)
    {
        sErrorMsg = "Transition to VIRGIN is not allowed. It will destroy the chip. Please contact Cypress if you need this specifically.";
        return E_FAIL;
    }

    //Set Acquire Mode
    ppSetAcquireMode("Reset", sErrorMsg);

    //Acquire Device
    hr = ppDAP_Acquire(sErrorMsg);
    if (!SUCCEEDED(hr)) return hr;

    //Check Hex File and Device compatibility
    bool fCompatibility = true;
    hr = CheckHexAndDeviceCompatibility(fCompatibility);
    if (!SUCCEEDED(hr)) return hr;
    if (!fCompatibility)
    {
        sErrorMsg = "The Hex file does not match the acquired device, please connect the appropriate device";
        return E_FAIL;
    }

    //Erase All
    hr = PSoC4_EraseAll();
    if (!SUCCEEDED(hr)) return hr;

    //Find checksum of Privileged Flash. Will be used in calculation of User CheckSum later
    long checkSum_Privileged = 0;
    hr = ppPSoC4_CheckSum(0x8000, checkSum_Privileged, sErrorMsg); //CheckSum All Flash ("Privileged + User" Rows)
    if (!SUCCEEDED(hr)) return hr;

    //Program Flash
    hr = ProgramFlash(hexImageSize);
    if (!SUCCEEDED(hr)) return hr;

    //Verify Rows
    hr = PSoC4_VerifyFlash(hexImageSize);
    if (!SUCCEEDED(hr)) return hr;

    //Protect All arrays
    hr = ppPSoC4_ProtectAll(sErrorMsg);
    if (!SUCCEEDED(hr)) return hr;

    //Verify protection ChipLevelProtection and Protection data
    hr = ppPSoC4_VerifyProtect(sErrorMsg);
    if (!SUCCEEDED(hr)) return hr;

    //CheckSum verification
    long checkSum_User = 0, checkSum_UserPrivileged;
    USHORT hexChecksum;
    hr = ppPSoC4_CheckSum(0x8000, checkSum_UserPrivileged, sErrorMsg); //CheckSum All Flash (Privileged + User)
    if (!SUCCEEDED(hr)) return hr;
    checkSum_User = checkSum_UserPrivileged - checkSum_Privileged; //find checksum of User Flash rows
	
    hr = ppHEX_ReadChecksum(hexChecksum, sErrorMsg);
    if (!SUCCEEDED(hr)) return hr;
    checkSum_User &= 0xFFFF;

	if (checkSum_User != hexChecksum)
	{
		printf("Mismatch of Checksum: Expected 0x%x ,Got 0x%x\n", checkSum_User, hexChecksum);
		return E_FAIL;
	}
	else
		printf("Checksum 0x%x\n", checkSum_User);

    //Release PSoC4 device
    hr = ppDAP_ReleaseChip(sErrorMsg);

	return hr;
}

long UpgradeBlock()
{
	long hr;
	
	//Port Initialization
    hr = InitializePort();

    //Set Acquire Mode
    ppSetAcquireMode("Reset", sErrorMsg);

    //Acquire Device
    hr = ppDAP_Acquire(sErrorMsg);
    if (!SUCCEEDED(hr)) return hr;

    //Write Block, use PSoC4_WriteRow() instead PSoC3_ProgramRow()
    long rowsPerArray, rowSize = 0;
    hr = ppPSoC4_GetFlashInfo(rowsPerArray, rowSize, sErrorMsg);
    if (!SUCCEEDED(hr)) return hr;

	std::vector<byte> writeData; //User and Config area of the Row (256+32)	
	for (long i = 0; i < rowSize; i++) writeData.push_back((byte)i);
    long rowID = rowSize - 1;
    hr = ppPSoC4_WriteRow(rowID, writeData, sErrorMsg);
    if (!SUCCEEDED(hr)) return hr;

    //Verify Row - only user area (without Config one)
    std::vector<byte> readRow;
    hr = ppPSoC4_ReadRow(rowID, readRow, sErrorMsg);
    if (!SUCCEEDED(hr)) return hr;

	for (UINT i = 0; i < readRow.size(); i++) //check 128 bytes
    {
        if (readRow[i] != writeData[i])
        {
            hr = E_FAIL;
            break;
        }
    }
    if (!SUCCEEDED(hr))
    {
        sErrorMsg = "Verification of User area failed!";
        return hr;
    }

    //Release PSoC4 chip
    hr = ppDAP_ReleaseChip(sErrorMsg);

    return hr;
}

long Execute()
{
	int hr;

	//Open Port - get last (connected) port in the ports list
    hr = OpenPort();
    if (!SUCCEEDED(hr)) return hr;

	//Execute programming
	hr = ProgramAll(); //    hr = UpgradeBlock();

	//Close the Port, so it is available for other apps
	ClosePort();

	return hr;
}

int _tmain(int argc, _TCHAR* argv[])
{
	HRESULT hr = 0;
  int Result = 1;

  if (argc == 2)
  {
    wcstombs(InputPath, argv[1], sizeof(InputPath));
  }

	cout << "Initializing COM" << endl;
	if ( FAILED(CoInitialize(NULL)))
	{
		cout << "Unable to initialize COM" << endl;
		return Result;
	}

	//Use Version Independent Prog ID to instantiate COM-object
	wchar_t progid[] = L"PSoCProgrammerCOM.PSoCProgrammerCOM_Object";
	//For version dependent Prog ID use below commented line, but update there COM-object version (e.g. 14)
	//wchar_t progid[] = L"PSoCProgrammerCOM.PSoCProgrammerCOM_Object.14";

	CLSID clsid;
	hr = ::CLSIDFromProgID(progid, &clsid);
	if (FAILED(hr))
	{
		cout << "Failed to get class id for PSoC Programmer COM object !" << endl;
		CoUninitialize();
		return Result;
	}

	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_SERVER, IID_IDispatch, (void**)&pIDispatch);
	if (FAILED(hr)) 
	{
		cout << "Failed to create instance of PSoC Programmer COM object !" << endl;
		CoUninitialize();
		return Result;
	}
	hr = GetDispIDsByName();
	if (FAILED(hr))
	{
		cout <<"Failed to get DispIDs of used methods";
		CoUninitialize();
		return Result;
	}

	ppStartSelfTerminator(GetCurrentProcessId());
	cout << "Program All using COM-object interface only" << endl;	
	std::string str;

	//Execute actual task of the example
	hr = Execute(); 

  if (SUCCEEDED(hr))
  {
    str = "Succeeded!";
    Result = 0;
  }
	else 
  {
    str = "Failed! "; 
    str.append(GetErrorMsg());
  }
	cout << str.c_str() << endl;
	cout << "Shutting down COM" << endl;
	
	pIDispatch->Release();
	CoUninitialize();

	return Result;
}