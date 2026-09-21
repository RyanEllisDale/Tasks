// Includes : 
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "json.hpp"

// Checks if there is an existing tasks file and creates one if there is not.
void CreateTasksFile()
{
	struct stat buffer;
	int taskFileExists = stat("Data/tasks.json", &buffer);
	if (taskFileExists == -1)
	{
		std::cout << "Creating new Tasks File for User." << std::endl;
		std::ofstream file("Data/tasks.json");
		file.close();
	}
}

int main()
{
	std::cout << "Welcome to your Task Tracker !" << std::endl;
	CreateTasksFile();

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
