// Includes :
#pragma once
#include <string>
#include <ctime>

enum TaskStatus
{
	todo,
	inProgress,
	complete
};

class Task
{
private:
	int id;
	std::string description = "";
	TaskStatus status = todo;
	std::time_t createdAt;
	std::time_t updatedAt;

public:
	Task(const int& aID, const std::string& aDescription);
};

