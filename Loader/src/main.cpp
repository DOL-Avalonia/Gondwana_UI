#include "Log.h"
#include "Config/ConfigurationManager.h"
#include <iostream>

int main(int argc, char* argv[])
{
	using namespace Gondwana;
	using namespace Gondwana::Loader;
	using Logger::log;

	ConfigurationManager config({ argv, argv + argc });

	return 0;
}

