// Includes :
#include "TaskManager.h"
#include <iostream>
#include <fstream>

TaskManager::TaskManager(void)
{
    ReadData();
    ListTasks();
}

const Task& TaskManager::AddTask(Task aTask, const TaskStatus& aStatus)
{
    for (const Task& currentTask : tasks)
    {
        if (aTask.description == currentTask.description)
        {
            std::cout << "This Task already exists in the list." << std::endl;
            return currentTask;
        }
    }

    aTask.ID = tasks.size();
    tasks.push_back(aTask);
    return tasks.back();
}


void TaskManager::DeleteTask(const int& aID)
{
    if (tasks.empty() == true)
    {
        std::cout << "There are no current tasks to delete." << std::endl;
        return;
    }

    if (FindTask(aID) != nullptr)
    {
        tasks.erase(tasks.begin() + aID);
        std::cout << "Task was Successfully delted" << std::endl;

        for (int i = 0; i < tasks.size(); i = i + 1)
        {
            tasks[i].ID = i;
        }

        return;
    }

    std::cerr << "Not a valid ID for a task : ID is out of range for Tasks.\nCurrent Range for Tasks is : " << 0 << " - " << tasks.size() << std::endl;
}


void TaskManager::DeleteTask(const std::string& aDescription)
{
    if (tasks.empty() == true)
    {
        std::cout << "There are no current tasks to delete." << std::endl;
        return;
    }

    for (std::vector<Task>::iterator iteratedTask = tasks.begin(); iteratedTask != tasks.end(); ++iteratedTask)
    {
        if (iteratedTask->description == aDescription)
        {
            iteratedTask = tasks.erase(iteratedTask);
            std::cout << "Task was Successfully delted" << std::endl;

            for (int i = 0; i < tasks.size(); i = i + 1)
            {
                tasks[i].ID = i;
            }

            return;
        }
    }

    std::cerr << "No matching Task of the description " << aDescription << " was found." << std::endl;
    return;
}

const Task& TaskManager::MarkTask(Task& aTask, const TaskStatus aStatus)
{
    aTask.status = aStatus;
    aTask.updatedAt = std::time(nullptr);
    return aTask;
}

const Task* TaskManager::MarkTask(const std::string& aDescription, const TaskStatus aStatus)
{
    Task* foundTask = FindTask(aDescription);
    if (foundTask != nullptr)
    {
        MarkTask(*foundTask, aStatus);
    }

    return foundTask;
}

const Task* TaskManager::MarkTask(const int& aID, const TaskStatus aStatus)
{
    Task* foundTask = FindTask(aID);
    if (foundTask != nullptr)
    {
        MarkTask(*foundTask, aStatus);
    }

    return foundTask;
}

void TaskManager::UpdateTaskDescription(Task& aTask, const std::string& aNewDescription)
{
    aTask.description = aNewDescription;
    aTask.updatedAt = std::time(nullptr);
}

void TaskManager::UpdateTaskDescription(const std::string& aTargetDescription, const std::string& aNewDescription)
{
    Task* foundTask = FindTask(aTargetDescription);
    if (foundTask != nullptr)
    {
        UpdateTaskDescription(*foundTask, aNewDescription);
    }
}

void TaskManager::UpdateTaskDescription(const int aTaskID, const std::string& aNewDescription)
{
    Task* foundTask = FindTask(aTaskID);
    if (foundTask != nullptr)
    {
        UpdateTaskDescription(*foundTask, aNewDescription);
    }
}

const Task& TaskManager::PrintTaskOneLine(const Task& aTask) const
{
    std::string taskStatusStrings[3] = { "Todo", "In Progress", "Completed" };

    std::tm localTime{};
    if (localtime_s(&localTime, &aTask.createdAt) != 0)
    {
        std::cerr << "Error converting time." << std::endl;
    }

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%c");
    std::string creationTime = oss.str();

    if (localtime_s(&localTime, &aTask.updatedAt) != 0)
    {
        std::cerr << "Error converting time." << std::endl;
    }

    oss.str("");
    oss.clear();
    oss << std::put_time(&localTime, "%c");
    std::string updationTime = oss.str();

    std::cout << aTask.ID << " : " << aTask.description << " : " << taskStatusStrings[aTask.status] << " : " << creationTime << " : " << updationTime << std::endl;
    return aTask;
}

const Task& TaskManager::PrintTaskLog(const Task& aTask) const
{
    std::string taskStatusStrings[3] = { "Todo", "In Progress", "Completed" };

    std::tm localTime{};
    if (localtime_s(&localTime, &aTask.createdAt) != 0)
    {
        std::cerr << "Error converting time." << std::endl;
    }

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%c");
    std::string creationTime = oss.str();

    if (localtime_s(&localTime, &aTask.updatedAt) != 0)
    {
        std::cerr << "Error converting time." << std::endl;
    }

    oss.str("");
    oss.clear();
    oss << std::put_time(&localTime, "%c");
    std::string updationTime = oss.str();

    std::cout << "----------" << std::endl;

    std::cout << "Task: " << aTask.description << std::endl;
    std::cout << "ID : " << aTask.ID << std::endl;
    std::cout << "Status : " << taskStatusStrings[aTask.status] << std::endl;
    std::cout << "Created At: " << creationTime << std::endl;
    std::cout << "Updated At: " << updationTime << std::endl;
    
    std::cout << "----------" << std::endl;

    return aTask;
}




Task* TaskManager::FindTask(const std::string& aDescription)
{
    auto it = std::find_if(tasks.begin(), tasks.end(), [aDescription](const Task& currentTask)
        {
            return currentTask.description == aDescription;
        });

    if (it != tasks.end())
    {
        return &*it;
    }

    std::cerr << "No matching Task of the description " << aDescription << " was found." << std::endl;
    return nullptr;
}

const Task* TaskManager::FindTask(const std::string& aDescription) const
{
    auto it = std::find_if(tasks.begin(), tasks.end(), [aDescription](const Task& currentTask)
    {
        return currentTask.description == aDescription;
    });

    if (it != tasks.end())
    {
        return &*it;
    }

    std::cerr << "No matching Task of the description " << aDescription << " was found." << std::endl;
    return nullptr;
}

Task* TaskManager::FindTask(const int aID) 
{
    if (aID > -1 && static_cast<std::size_t>(aID) < tasks.size())
    {
        return &tasks[aID];
    }

    std::cerr << "Not a valid ID for a task : ID is out of range for Tasks.\nCurrent Range for Tasks is : " << 0 << " - " << tasks.size() << std::endl;
    return nullptr;
}

const Task* TaskManager::FindTask(const int aID) const
{
    if (aID > -1 && static_cast<std::size_t>(aID) < tasks.size())
    {
        return &tasks[aID];
    }

    std::cerr << "Not a valid ID for a task : ID is out of range for Tasks.\nCurrent Range for Tasks is : " << 0 << " - " << tasks.size() << std::endl;
    return nullptr;
}

const Task* TaskManager::PrintTaskDetails(const int aID, const bool oneline) const
{
    const Task* foundTask = FindTask(aID);
    if (foundTask != nullptr)
    {
        if (oneline == true)
        {
            PrintTaskOneLine(*foundTask);
        }
        else
        {
            PrintTaskLog(*foundTask);
        }
    }

    return foundTask;
}


const Task* TaskManager::PrintTaskDetails(const std::string& aDescription, const bool oneline) const
{
    const Task* foundTask = FindTask(aDescription);
    if (foundTask != nullptr)
    {
        if (oneline == true)
        {
            PrintTaskOneLine(*foundTask);
        }
        else
        {
            PrintTaskLog(*foundTask);
        }
    }

    return foundTask;
}


void TaskManager::ListTasks(void) const
{
    for (const Task& currentTask : tasks)
    {
        PrintTaskOneLine(currentTask);
    }
}

void TaskManager::ListTasks(TaskStatus aStatus) const
{
    int count = 0;
    for (const Task& currentTask : tasks)
    {
        if (currentTask.status == aStatus)
        {
            PrintTaskOneLine(currentTask);
            count = count + 1;
        }
    }

    if (count == 0)
    {
        std::string taskStatusStrings[3] = { "Todo", "In Progress", "Completed" };
        std::cout << "There are currently no tasks that are: " << taskStatusStrings[aStatus] << "." << std::endl;
    }
}

void TaskManager::ReadData(void)
{
    std::ifstream inputTasksFile("Data/tasks.json");

    nlohmann::json tasksJsonFile = nlohmann::json::parse(inputTasksFile);
    std::vector<nlohmann::json> jsonTasks = tasksJsonFile["tasks"];

    for (const nlohmann::json& currentJSON : jsonTasks)
    {
       tasks.push_back(Task(currentJSON));
    }

    inputTasksFile.close();
}

void TaskManager::SaveData(void) const
{
	std::ofstream outputTasksFile("Data/tasks.json");

    nlohmann::json tasksJsonObject;
    tasksJsonObject["tasks"] = nlohmann::json::array();

    for (const Task& currentTask : tasks)
    {
        tasksJsonObject["tasks"].push_back(TaskToJSON(currentTask));
    }

	outputTasksFile << std::setw(4) << tasksJsonObject;
    outputTasksFile.close();
}

const nlohmann::json TaskManager::TaskToJSON(const Task& aTask) const
{
    nlohmann::json taskJson;
    taskJson["id"] = aTask.ID;
    taskJson["description"] = aTask.description;
    taskJson["status"] = aTask.status;
    taskJson["created at"] = aTask.createdAt;
    taskJson["updated at"] = aTask.updatedAt;
    return taskJson;
}

