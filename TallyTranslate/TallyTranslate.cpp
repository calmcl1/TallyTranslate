// TallyTranslate.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "TallyTranslate.h"
#include "BMDSwitcherManagement.h"


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


