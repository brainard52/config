#include <iostream>

#include "../inc/config.h"

int main()
{
	Configuration config("config");

	std::cout << config.GetWidth() << '\n';
	return 0;
}
