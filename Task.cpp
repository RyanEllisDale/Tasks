// Includes :
#include "Task.h"
#include <iostream>

Task::Task(const int& aID, const std::string& aDescription) : id(aID), description(aDescription)
{
	status = todo;
	std::time(&createdAt);
	std::time(&updatedAt);
}

void Task::Print() const
{
	std::cout << "Task: " << description << std::endl;
	std::cout << "ID: " << id << std::endl;
	std::string taskStatusStrings[3] = { "Todo", "In Progress", "Completed" };
	std::cout << "Status: " << taskStatusStrings[status] << std::endl;


	struct tm localTime;
	char buffer[50];

	if (localtime_s(&localTime, &createdAt) == 0)
	{
		asctime_s(buffer, sizeof(buffer), &localTime);
		std::cout << "Created At: Working: " << buffer << std::endl;
	}
	else
	{
		std::cerr << "Error converting time." << std::endl;
	}

	if (localtime_s(&localTime, &updatedAt) == 0)
	{
		asctime_s(buffer, sizeof(buffer), &localTime);
		std::cout << "updated At: Working: " << buffer << std::endl;
	}
	else
	{
		std::cerr << "Error converting time." << std::endl;
	}
}
