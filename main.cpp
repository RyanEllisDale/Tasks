// Includes : 
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "json.hpp"
#include "TaskManager.h"
#include <cstdlib>
#include <filesystem>
#include <map>

void PrintHello(const std::vector<std::string>&)
{
	std::cout << "Welcome to your Task Tracker !" << std::endl;
}

void PrintGoodbye(const std::vector<std::string>&)
{
	std::cout << "Goodbye~ Thanks for using your Task Tracker !" << std::endl;
}

void PrintCredits(const std::vector<std::string>&)
{
	std::cout << "----------\n"
		<< "Developer: Ryan Dale\n"
		<< "JSON library: nlohmann json | MIT license | Copyright (c) 2013-2026 Niels Lohmann\n"
		<< "Inspired By Roadmaps.sh's Task Tracker Project : https://roadmap.sh/projects/task-tracker\n"
		<< "----------" << std::endl;
}

bool CreateAppDataFile()
{
	char* appdataDir = nullptr;
	if (_dupenv_s(&appdataDir, nullptr, "APPDATA") != 0 || appdataDir == nullptr)
	{
		std::cout << "Could not retrieve APPDATA environment variable." << std::endl;
		return false;
	}

	std::filesystem::path baseDir = std::filesystem::path(appdataDir) / "Tasks"; // App Data Folder
	std::filesystem::path filePath = baseDir / "tasks.json"; // Tasks File in App Data Folder
	free(appdataDir);

	try
	{
		// Directory Creation :
		if (std::filesystem::create_directories(baseDir) == true)
		{
			std::cout << "Tasks Directory Not Found, Creating Tasks Directory\nSuccessfully Created Tasks Directory in " << baseDir << std::endl;
		}

		// File Creation :
		if (std::filesystem::exists(filePath) == false)
		{
			std::ofstream ouputTasksFile(filePath);
			if (ouputTasksFile.is_open())
			{
				std::cout << "Creating new Tasks File for User." << std::endl;

				nlohmann::json tasksJsonObject;
				tasksJsonObject["tasks"] = nlohmann::json::array();
				ouputTasksFile << std::setw(4) << tasksJsonObject;
				ouputTasksFile.close();

				std::cout << "File created successfully at: " << filePath << std::endl << std::endl;
				return true;
			}
			else
			{
				std::cout << "Could not open file for writing: " << filePath << std::endl;
				return false;
			}
		}
	}
	// Error Handling :
	catch (const std::filesystem::filesystem_error& error)
	{
		std::cerr << "Filesystem Error: " << error.what() << '\n';
		std::cerr << "Path: " << error.path1().string() << '\n';
		return false;
	}

	return true;
}

int main(int n, char* args[])
{	
	// Data Handling : 
	if (CreateAppDataFile() == false)
	{
		std::cerr << "Could not Create / Load Tasks Data, Terminating Program" << std::endl;
		return 0;
	}

	// Basic Print : 
	TaskManager taskManager;
	if (n == 1)
	{
		taskManager.ListTasksHandle(std::vector<std::string>());
		return 1;
	}


	// Input :
	std::string command;
	std::vector<std::string> subCommands;
	if (n > 1)
	{
		command = args[1];
		std::transform(command.begin(), command.end(), command.begin(), ::tolower);

		for (int i = 2; i < n; i = i + 1)
		{
			std::string subCommand = args[i];
			std::transform(subCommand.begin(), subCommand.end(), subCommand.begin(), ::tolower);
			subCommands.push_back(subCommand);
		}
	}

	// Command Lookups:
	std::map<std::string, std::function<void(const std::vector<std::string>&)>> commandLookup = {
		{"hello", PrintHello},
		{"exit", PrintGoodbye},
		{"end", PrintGoodbye},
		{"leave", PrintGoodbye},
		{"credits", PrintCredits},
		{"list", [&taskManager](const std::vector<std::string>& subCommands) { taskManager.ListTasksHandle(subCommands); }},
		{"view", [&taskManager](const std::vector<std::string>& subCommands) { taskManager.PrintTaskHandle(subCommands); }},
		{"print", [&taskManager](const std::vector<std::string>& subCommands) { taskManager.PrintTaskHandle(subCommands); }},
		{"add", [&taskManager](const std::vector<std::string>& subCommands) { taskManager.AddTaskHandle(subCommands); }},
		{"+", [&taskManager](const std::vector<std::string>& subCommands) { taskManager.AddTaskHandle(subCommands); }},
		{"del", [&taskManager](const std::vector<std::string>& subCommands) { taskManager.DeleteTaskHandle(subCommands); }},
		{"delete", [&taskManager](const std::vector<std::string>& subCommands) { taskManager.DeleteTaskHandle(subCommands); }},
		{"-", [&taskManager](const std::vector<std::string>& subCommands) { taskManager.DeleteTaskHandle(subCommands); }},
		{"mark", [&taskManager](const std::vector<std::string>& subCommands) { taskManager.MarkTaskHandle(subCommands); }},
		{"status", [&taskManager](const std::vector<std::string>& subCommands) { taskManager.MarkTaskHandle(subCommands); }},
		{"change", [&taskManager](const std::vector<std::string>& subCommands) { taskManager.UpdateTaskHandle(subCommands); }},
		{"retitle", [&taskManager](const std::vector<std::string>& subCommands) { taskManager.UpdateTaskHandle(subCommands); }},
		{"re-title", [&taskManager](const std::vector<std::string>& subCommands) { taskManager.UpdateTaskHandle(subCommands); }},
		{"rename", [&taskManager](const std::vector<std::string>& subCommands) { taskManager.UpdateTaskHandle(subCommands); }},
		{"re-name", [&taskManager](const std::vector<std::string>& subCommands) { taskManager.UpdateTaskHandle(subCommands); }},
		{"clear", [&taskManager](const std::vector<std::string>& subCommands) { taskManager.ClearTasksHandle(subCommands); }},
	};

	// Executing Commands : 
	if (commandLookup.find(command) != commandLookup.end())
	{
		commandLookup[command](subCommands);
	}
	else
	{
		std::cerr << "Command not recognised" << std::endl;
	}

	return 0;
}
