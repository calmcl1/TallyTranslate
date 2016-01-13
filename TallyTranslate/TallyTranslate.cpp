// TallyTranslate.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "TallyTranslate.h"
#include "BMDSwitcherManagement.h"
#include "tsl/tslmanagement.h"


int main()
{

	getSwitcher("localhost");
	getTSLThing(TSLUMDVersion::v50);
    return 0;
};
