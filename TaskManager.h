// Includes : 
#pragma once
#include <vector>
#include "Task.h"

class TaskManager
{
private:
	std::vector<Task> tasks;

public:
	TaskManager(void);
	~TaskManager(void);

	void AddTaskHandle(const std::vector<std::string>& aSubCommands);
	void DeleteTaskHandle(const std::vector<std::string>& aSubCommands);
	void MarkTaskHandle(const std::vector<std::string>& aSubCommands);
	void UpdateTaskHandle(const std::vector<std::string>& aSubCommands);
	void PrintTaskHandle(const std::vector<std::string>& aSubCommands) const;
	void ListTasksHandle(const std::vector<std::string>& aSubCommands) const;
	void ClearTasksHandle(const std::vector<std::string>& aSubCommands);

private:
	const Task& AddTask(Task aTask, const TaskStatus& aStatus = todo);
	const Task& AddTask(const std::string& aDescription, const TaskStatus& aStatus = todo) { return AddTask(Task(aDescription, aStatus)); }
	const Task& AddTask(const nlohmann::json& aTaskJson, const TaskStatus& aStatus = todo) { return AddTask(Task(aTaskJson)); }
	const Task& AddTask(const char* aCharString, const TaskStatus& aStatus = todo) { return AddTask(std::string(aCharString), aStatus); }

	void DeleteTask(const int& aID);
	void DeleteTask(const std::string& aDescription);
	void DeleteTask(const Task& aTask) { DeleteTask(aTask.ID); }

	const Task& MarkTask(Task& aTask, const TaskStatus aStatus = complete);
	const Task* MarkTask(const std::string& aDescription, const TaskStatus aStatus = complete);
	const Task* MarkTask(const int& aID, const TaskStatus aStatus = complete);

	void UpdateTaskDescription(Task& aTask, const std::string& aNewDescription);
	void UpdateTaskDescription(const std::string& aTargetDescription, const std::string& aNewDescription);
	void UpdateTaskDescription(const int aTaskID, const std::string& aNewDescription);

	const Task* PrintTaskDetails(const int aID, const bool oneline = false) const;
	const Task* PrintTaskDetails(const std::string& aDescription, const bool oneline = false) const;
	const Task& PrintTaskOneLine(const Task& aTask) const;
	const Task& PrintTaskLog(const Task& aTask) const;

	void ListTasks(void) const;
	void ListTasks(TaskStatus aStatus) const;

	Task* FindTask(const std::string& aDescription);
	const Task* FindTask(const std::string& aDescription) const;
	Task* FindTask(const int aID);
	const Task* FindTask(const int aID) const;

	const nlohmann::json TaskToJSON(const Task& aTask) const;

	void ReadData(void);
	void SaveData(void);
};

