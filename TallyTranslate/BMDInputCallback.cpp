#include "BMDInputCallback.h"
#include <iostream>



BMDInputCallback::BMDInputCallback(BMDSwitcherInputId switcherInputID)
{
	input_id = switcherInputID;
	std::cout << "Created BMDInputCallback for switcher input " << input_id << std::endl;
}

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

BMDInputCallback::~BMDInputCallback()
{
	std::cout << "Deleted BMDInputCallback for switcher input " << input_id << std::endl;
	delete &input_id;
}
