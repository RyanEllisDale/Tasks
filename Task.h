// Includes :
#pragma once
#include <string>
#include <ctime>
#include "json.hpp"

enum TaskStatus
{
	todo,
	inProgress,
	complete
};

NLOHMANN_JSON_SERIALIZE_ENUM(TaskStatus, {
	{todo, "ToDo"},
	{inProgress, "In Progress"},
	{complete, "Completed"},
})

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
	Task(const nlohmann::json& taskJson);
	void Print(void) const;
	nlohmann::json ToJson(void);
};

