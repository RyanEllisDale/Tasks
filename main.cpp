// Includes : 
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "json.hpp"
#include "Task.h"
#include "TaskManager.h"

// Checks if there is an existing tasks file and creates one if there is not.
void CreateTasksFile()
{
	struct stat buffer;
	int taskFileExists = stat("Data/tasks.json", &buffer);
	if (taskFileExists == -1)
	{
		// Writing :
		std::cout << "Creating new Tasks File for User." << std::endl;
		std::ofstream ouputTasksFile("Data/tasks.json");
		nlohmann::json tasksJsonObject;
		tasksJsonObject["tasks"] = nlohmann::json::array();
		ouputTasksFile << std::setw(4) << tasksJsonObject;
		ouputTasksFile.close();
	}
}

int main()
{
	// Start :
	std::cout << "Welcome to your Task Tracker !" << std::endl;
	
	CreateTasksFile();
	TaskManager taskManager;

	while (1)
	{
		// Input :
		std::string input = "";
		std::cin >> input;
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);

		// Input Handling : 
		if (input == "exit")
		{
			std::cout << "Thank you for using your Task Tracker !" << std::endl;
			break;
		}
	}

	return 0;
}
