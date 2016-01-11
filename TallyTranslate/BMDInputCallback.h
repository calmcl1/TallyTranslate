#pragma once

#ifndef BMDINPUTCALLBACK_H
#define BMDINPUTCALLBACK_H


#include "BMDSwitcherAPI_h.h"

class BMDInputCallback :
	public IBMDSwitcherInputCallback
{
	BMDSwitcherInputId input_id;
public:
	BMDInputCallback(BMDSwitcherInputId);
	HRESULT STDMETHODCALLTYPE Notify(BMDSwitcherInputEventType);

	virtual ~BMDInputCallback();
};

#endif // BMDINPUTCALLBACK_H