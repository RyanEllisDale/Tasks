// Includes : 
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "json.hpp"
#include "Task.h"

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

	// Reading : 
	std::ifstream inputTasksFile("Data/tasks.json");
	nlohmann::json tasksJsonFile = nlohmann::json::parse(inputTasksFile);
	std::vector<nlohmann::json> jsonTasks = tasksJsonFile["tasks"];
	inputTasksFile.close();

	// Make Task :
	Task debugTask(jsonTasks[0]);
	debugTask.Print();

	// Writing :
	std::ofstream outputTasksFile("Data/tasks.json");
	nlohmann::json taskJson = debugTask.ToJson();
	jsonTasks.push_back(taskJson);
	tasksJsonFile["tasks"] = jsonTasks;
	outputTasksFile << std::setw(4) << tasksJsonFile;
	outputTasksFile.close();

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
