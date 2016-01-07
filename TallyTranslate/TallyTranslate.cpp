// TallyTranslate.cpp : Defines the entry point for the console application.
//

#include "TallyTranslate.h"
#include <iostream>



int main()
{
	getSwitcher();
    return 0;
};

int getTSLThing(int version)
{
	if (version == TSLUMDVersion::v50)
	{
		const int TSL_MAX_PACKET_LENGTH = 2048;
		const int TSL_DLE = 0xFE;
		const int TSL_STX = 0x02;
	}

	return 0;
};


BMDInputCallback::BMDInputCallback(BMDSwitcherInputId switcherInputID)
{
	input_id = switcherInputID;
};

HRESULT STDMETHODCALLTYPE BMDInputCallback::Notify(BMDSwitcherInputEventType eventType)
{
	if (eventType == bmdSwitcherInputEventTypeLongNameChanged)
	{
		return S_OK;
	}
	else if (eventType == bmdSwitcherInputEventTypeShortNameChanged)
	{
		return S_OK;
	}
	else if (eventType == bmdSwitcherInputEventTypeIsPreviewTalliedChanged)
	{
		return S_OK;
	}
	else if (eventType == bmdSwitcherInputEventTypeIsProgramTalliedChanged)
	{
		return S_OK;
	}
	else
	{
		return S_OK;
	}
};

int getSwitcher()
{
	const char* ATEM_SOFTWARE_VERSION = "6.6";

	// Firstly, we need to initialize COM.
	if (CoInitializeEx(NULL, COINIT::COINIT_MULTITHREADED))
	{
		std::cerr << "Failed to initialize COM." << std::endl;
		return 1;
	}
	else {
		std::cout << "Successfully initialized COM." << std::endl;
	}

	/*
	That done, let's Discover a Switcher. We create the IBMDSwitcherDiscovery
	and use that to look for a switcher at a given address.
	*/
	
	IBMDSwitcherDiscovery* switcherDiscovery = NULL;

	HRESULT switcherDiscoveryRes = CoCreateInstance(CLSID_CBMDSwitcherDiscovery, NULL, CLSCTX_ALL, IID_IBMDSwitcherDiscovery,
		(void**)&switcherDiscovery);

	if (switcherDiscoveryRes == S_OK)
	{
		// We've successfully created the IBMDSwitcherDiscovery
		std::cout << "Created IBMDSwitcherDiscovery" << std::endl;
	}
	else if(switcherDiscoveryRes == REGDB_E_CLASSNOTREG){
		// The COM class probably isn't registered - meaning that the user doesn't have the ATEM control software installed.
		std::cerr << "Couldn't find ATEM software. Make sure that ATEM control software v" << ATEM_SOFTWARE_VERSION << " is installed." << std::endl;
		return 1;
	}
	else
	{
		// Programming problem - CLASS_E_NOAGGREGATION, E_NOINTERFACE or E_POINTER
		std::cerr << "Internal problem. Error code: " << switcherDiscoveryRes << std::endl;
		return 1;
	}

	// We've got the SwitcherDiscovery - now we'll try and connect to an ATEM.

	BSTR ATEMIPAddr = BSTR("localhost");

	IBMDSwitcher*					switcherDevice;
	BMDSwitcherConnectToFailure		failReason;
	HRESULT switcherConnectRes = switcherDiscovery->ConnectTo(ATEMIPAddr, &switcherDevice, &failReason);

	if (switcherConnectRes == S_OK)
	{
		// Found and connected to an ATEM at the specified IP.
		std::cout << "Found a device at " << ATEMIPAddr << std::endl;
	}
	else if (switcherConnectRes == E_FAIL)
	{
		 // Cannot connect to ATEM there. failReason will tell us why.
		std::cerr << "Couldn't connect to ATEM at " << ATEMIPAddr << std::endl;
		if (failReason == BMDSwitcherConnectToFailure::bmdSwitcherConnectToFailureCorruptData)
		{
			std::cerr << "\tReason: Corrupt data received from ATEM." << std::endl;
		}
		else if (failReason == BMDSwitcherConnectToFailure::bmdSwitcherConnectToFailureIncompatibleFirmware)
		{
			std::cerr << "\tReason: ATEM firmware incompatible. Make sure that ATEM control software and firmware versions match." << std::endl;
		}
		else if (failReason == BMDSwitcherConnectToFailure::bmdSwitcherConnectToFailureNoResponse)
		{
			std::cerr << "\tReason: Got no response from ATEM." << std::endl;
		}
		else if (failReason == BMDSwitcherConnectToFailure::bmdSwitcherConnectToFailureStateSync)
		{
			std::cerr << "\tReason: State synchronisation failed." << std::endl;
		}
		else if (failReason == BMDSwitcherConnectToFailure::bmdSwitcherConnectToFailureStateSyncTimedOut)
		{
			std::cerr << "\tReason: State synchronisation timed out." << std::endl;
		}
		return 1;
	}
	else
	{
		// Can only really be E_POINTER - but let's be sure.
		std::cerr << "Internal problem conencting to switcher. Error code " << switcherConnectRes << std::endl;
		return 1;
	}

	/*
	So, if we've gotten this far, we should have an ATEM device at IBMDSwitcher* switcherDevice.
	Let's find out what kind of ATEM it is.
	*/

	BSTR productName = NULL;
	HRESULT getPNRes = switcherDevice->GetProductName(&productName);

	if (getPNRes == S_OK)
	{
		std::cout << "Product name: " << productName << std::endl;
	}
	else
	{
		std::cerr << "Could not retrieve product name." << std::endl;
	}

	return 0;
}
