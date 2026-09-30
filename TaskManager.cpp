// Includes :
#include "TaskManager.h"
#include <iostream>
#include <fstream>

TaskManager::TaskManager(void)
{
    ReadData();
}

TaskManager::~TaskManager(void)
{
    SaveData();
}

void TaskManager::AddTaskHandle(const std::vector<std::string>& aSubCommands)
{
    if (aSubCommands.empty() == true)
	{
		std::cerr << "You must specify a task to add : Title & Status(optional)" << std::endl;
        return;
	}

	if (aSubCommands.size() == 1)
	{
		AddTask(aSubCommands[0]);
        return;
	}

    std::map<std::string, TaskStatus> stringToStatus =
    {
        {"todo",todo}, {"to-do",todo}, {"to do", todo},
        {"inprogress", inProgress}, {"in-progress", inProgress}, {"in progress", inProgress},
        {"complete", complete}, {"completed", complete}
    };

	if (stringToStatus.find(aSubCommands[1]) != stringToStatus.end())
	{
        AddTask(aSubCommands[0], stringToStatus[aSubCommands[1]]);
        return;
	}

    std::cout << "Only Status arguments accepted are: todo | inprogress | complete" << std::endl;
}

void TaskManager::DeleteTaskHandle(const std::vector<std::string>& aSubCommands)
{
    if (aSubCommands.empty() == true)
    {
        std::cerr << "You must specify a task to delete : Title or ID" << std::endl;
        return;
    }

    int index;
    if (sscanf_s(aSubCommands[0].c_str(), "%d", &index) == 1)
    {
        DeleteTask(index);
    }
    else
    {
        DeleteTask(aSubCommands[0]);
    }
}

void TaskManager::MarkTaskHandle(const std::vector<std::string>& aSubCommands)
{
    if (aSubCommands.empty() == true)
    {
        std::cerr << "you must specify a task to mark either through Title or ID + a Status" << std::endl;
        return;
    }

    int index;
    if (aSubCommands.size() == 1)
    {
        if (sscanf_s(aSubCommands[0].c_str(), "%d", &index) == 1)
        {
            MarkTask(index);
        }
        else
        {
            MarkTask(aSubCommands[0]);
        }

        return;
    }

    std::map<std::string, TaskStatus> stringToStatus =
    {
        {"todo",todo}, {"to-do",todo}, {"to do", todo},
        {"inprogress", inProgress}, {"in-progress", inProgress}, {"in progress", inProgress},
        {"complete", complete}, {"completed", complete}
    };

    if (stringToStatus.find(aSubCommands[1]) != stringToStatus.end())
    {
        if (sscanf_s(aSubCommands[0].c_str(), "%d", &index) == 1)
        {
            MarkTask(index, stringToStatus[aSubCommands[1]]);
        }
        else
        {
            MarkTask(aSubCommands[0], stringToStatus[aSubCommands[1]]);
        }

        return;
    }

    std::cout << "Only Status arguments accepted are: todo | inprogress | complete" << std::endl;
}

void TaskManager::UpdateTaskHandle(const std::vector<std::string>& aSubCommands)
{
    if (aSubCommands.empty() == true)
    {
        std::cerr << "you must specify a task to mark either through Title or ID + a new title" << std::endl;
        return;
    }

    if (aSubCommands.size() != 2)
    {
        std::cerr << "invalid arguments, 2 arguments required, target task (ID or Title), new title (String)" << std::endl;
        return;
    }

    int index;
    if (sscanf_s(aSubCommands[0].c_str(), "%d", &index) == 1)
    {
        UpdateTaskDescription(index, aSubCommands[1]);
    }
    else
    {
        UpdateTaskDescription(aSubCommands[0], aSubCommands[1]);
    }
}

void TaskManager::PrintTaskHandle(const std::vector<std::string>& aSubCommands) const
{
    if (aSubCommands.empty() == true)
    {
        std::cerr << "you must specify a task to view either through Title or ID" << std::endl;
        return;
    }


    bool oneline = false;
    if (aSubCommands.size() > 1)
    {
        if (aSubCommands[1] == "true" || aSubCommands[1] == "oneline" || aSubCommands[1] == "--oneline" || aSubCommands[1] == "one line")
        {
            oneline = true;
        }
    }


    int index;
    if (sscanf_s(aSubCommands[0].c_str(), "%d", &index) == 1)
    {
        PrintTaskDetails(index, oneline);
    }
    else
    {
        PrintTaskDetails(aSubCommands[0], oneline);
    }
}

void TaskManager::ListTasksHandle(const std::vector<std::string>& aSubCommands) const
{
    if (aSubCommands.empty() == true)
    {
        ListTasks();
        return;
    }

    std::map<std::string, TaskStatus> stringToStatus =
    {
        {"todo",todo}, {"to-do",todo}, {"to do", todo},
        {"inprogress", inProgress}, {"in-progress", inProgress}, {"in progress", inProgress},
        {"complete", complete}, {"completed", complete}
    };

    if (stringToStatus.find(aSubCommands[0]) != stringToStatus.end())
    {
        ListTasks(stringToStatus[aSubCommands[0]]);
        return;
    }

    std::cout << "Only Status arguments accepted are: todo | inprogress | complete" << std::endl;
}

void TaskManager::ClearTasksHandle(const std::vector<std::string>& aSubCommands)
{
    tasks.clear();
    std::cout << "Tasks successfully Cleared" << std::endl;
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

    std::cout << "Task: " << aTask.description << " was Successfully added" << std::endl;
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
        Task copyReadTask = tasks[aID];
        tasks.erase(tasks.begin() + aID);
        std::cout << "Task : " << copyReadTask.description << " was Successfully delted" << std::endl;

        for (int i = 0; i < tasks.size(); i = i + 1)
        {
            tasks[i].ID = i;
        }

        return;
    }
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
            Task copyReadTask = *iteratedTask;
            iteratedTask = tasks.erase(iteratedTask);
            std::cout << "Task : " << copyReadTask.description << " was Successfully delted" << std::endl;

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

    std::string taskStatusStrings[3] = { "Todo", "In Progress", "Completed" };
    std::cout << "Task: " << aTask.description << " was succesffuly marked as : " << taskStatusStrings[aStatus] << std::endl;
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
    std::cout << "Task: " << aTask.description << " was changed to: " << aNewDescription << std::endl;
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
    // Converting / Formatting Created At Time : 
    std::tm localTime{};
    if (localtime_s(&localTime, &aTask.createdAt) != 0)
    {
        std::cerr << "Error converting time." << std::endl;
    }

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%a %m/%d/%y %H:%M:%S");
    std::string creationTime = oss.str();

    // Converting / Formatting Updated At Time : 
    if (localtime_s(&localTime, &aTask.updatedAt) != 0)
    {
        std::cerr << "Error converting time." << std::endl;
    }

    oss.str("");
    oss.clear();
    oss << std::put_time(&localTime, "%a %m/%d/%y %H:%M:%S");
    std::string updationTime = oss.str();

    // Print Details :
    std::string taskStatusStrings[3] = { "Todo", "In Progress", "Completed" };
    std::cout << aTask.ID << " : " << aTask.description << " : " << taskStatusStrings[aTask.status] << " : " << creationTime << " : " << updationTime << std::endl;
    return aTask;
}

const Task& TaskManager::PrintTaskLog(const Task& aTask) const
{
    // Converting / Formatting Created At Time : 
    std::tm localTime{};
    if (localtime_s(&localTime, &aTask.createdAt) != 0)
    {
        std::cerr << "Error converting time." << std::endl;
    }

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%a %m/%d/%y %H:%M:%S");
    std::string creationTime = oss.str();

    // Converting / Formatting Updated At Time : 
    if (localtime_s(&localTime, &aTask.updatedAt) != 0)
    {
        std::cerr << "Error converting time." << std::endl;
    }

    oss.str("");
    oss.clear();
    oss << std::put_time(&localTime, "%a %m/%d/%y %H:%M:%S");
    std::string updationTime = oss.str();

    // Print Details : 
    std::string taskStatusStrings[3] = { "Todo", "In Progress", "Completed" };
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
    if (tasks.size() == 0)
    {
        std::cout << "There are currently no tasks to do" << std::endl;
        return;
    }

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
    // Checking Enviroment :
    char* appdataDir = nullptr;
    if (_dupenv_s(&appdataDir, nullptr, "APPDATA") != 0 || appdataDir == nullptr)
    {
        std::cout << "Could not retrieve APPDATA environment variable." << std::endl;
        return;
    }

    // Making File Path :
    std::string filePath = std::string(appdataDir) + "\\Tasks\\tasks.json";
    free(appdataDir);

    // Reading Data :
    std::ifstream inputFile(filePath);
    if (inputFile.is_open())
    {
        nlohmann::json tasksJsonFile = nlohmann::json::parse(inputFile);
        std::vector<nlohmann::json> jsonTasks = tasksJsonFile["tasks"];

        for (const nlohmann::json& currentJSON : jsonTasks)
        {
            tasks.push_back(Task(currentJSON));
        }

        inputFile.close();
        return;
    }

    std::cerr << "Could not open file at: " << filePath << std::endl;
}

void TaskManager::SaveData(void)
{
    // Checking Enviroment :
    char* appdataDir = nullptr;
    if (_dupenv_s(&appdataDir, nullptr, "APPDATA") != 0 || appdataDir == nullptr)
    {
        std::cout << "Could not retrieve APPDATA environment variable." << std::endl;
        return;
    }

    // Making File Path : 
    std::string filePath = std::string(appdataDir) + "\\Tasks\\tasks.json";
    free(appdataDir);

    // Write file contents :
    std::ofstream outputFile(filePath);
    if (outputFile.is_open())
    {
        nlohmann::json tasksJsonObject;
        tasksJsonObject["tasks"] = nlohmann::json::array();

        for (const Task& currentTask : tasks)
        {
            tasksJsonObject["tasks"].push_back(TaskToJSON(currentTask));
        }

        outputFile << std::setw(4) << tasksJsonObject;
        outputFile.close();

        return;
    }
        
    std::cout << "Could not open file at: " << filePath << std::endl;
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

