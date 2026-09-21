// Includes : 
#include <iostream>
#include <string>
#include <algorithm>

int main()
{
	std::cout << "Welcome to your Task Tracker !" << std::endl;

	while (1)
	{
		// Input :
		std::string input = "";
		std::cin >> input;
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);

		if (input == "exit")
		{
			std::cout << "Thank you for using your Task Tracker !" << std::endl;
			break;
		}
	}

	return 0;
}
