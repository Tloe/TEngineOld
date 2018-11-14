#include "RandomTesting.h"
#include "TETimer.h"
#include "TEVariant.h"
#include <string>

int RandomTesting()
{
	TE::Core::Variant var("Test_variant");

	TE::Core::Variant var2;

	var2 = var;

	std::cout << var2.GetString();

	return 0;
}

