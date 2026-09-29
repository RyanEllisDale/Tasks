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

struct Task
{
	std::string description = "Default Task Description";
	std::time_t createdAt = std::time(nullptr);
	std::time_t updatedAt = std::time(nullptr);
	int ID = 0;
	TaskStatus status = todo;	

	Task() = default;
	Task(const std::string& aDescription, const TaskStatus& aStatus = todo, const int aID = 0) : description(aDescription), status(aStatus), ID(aID) {}
	explicit Task(const nlohmann::json& aTaskJson) : description(aTaskJson["description"]), createdAt(aTaskJson["created at"]), updatedAt(aTaskJson["updated at"]), ID(aTaskJson["id"]), status(aTaskJson["status"]) {}
};

