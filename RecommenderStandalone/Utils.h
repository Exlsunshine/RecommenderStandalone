#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

namespace RS
{
	void displayError(const std::string msg, const int errCode)
	{
		std::cout << msg << std::endl << "Press anykey to exit...";
		std::cin.get();
		exit(errCode);
	}

	const int OPEN_FILE_ERROR = 0x0001;
	const int READ_FILE_INFO_ERROR = 0x0002;
	const int READ_TIME_INFO_ERROR = 0x0003;
	const int FEATURE_NOT_SUPPORT_ERROR = 0x0004;
	const int DELIMIETER_NOT_FOUND_ERROR = 0x0005;
}

#endif