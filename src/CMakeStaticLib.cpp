#include <CMakeStaticLib.h>
#include <iostream>

namespace CMakeStaticLib
{
	void About()
	{
		::std::cout << "Hello from CMakeStaticLib" << ::std::endl;
		::std::cout << __FUNCTION__ << ":" << __FILE__ << ":" << __LINE__ << std::endl;
		::std::cout << "=== 2.3.0 ===" << ::std::endl;
	}

}

