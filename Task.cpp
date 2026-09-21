// Includes :
#include "Task.h"
#include <iostream>

Task::Task(const int& aID, const std::string& aDescription) : id(aID), description(aDescription)
{
	status = todo;
	std::time(&createdAt);
	std::time(&updatedAt);
}


