#include "Process.h"
#include <iostream>

Process::Process(
    const std::string &name,
    const std::string &description,
    const std::vector<std::string> &requiredResourcesNames,
    int durationInUnits) :
Executable(name, description, requiredResourcesNames, durationInUnits) {}

void Process::addResource(std::unique_ptr<Resource> resource) {
    resourcePool.push_back(std::move(resource));
}

void Process::addTask(std::unique_ptr<Executable> task) {
    tasks.push_back(std::move(task));
}

void Process::execute() const {
    if (!requiredResourcesNames.empty() && assignedResources.size() != requiredResourcesNames.size()) {
        throw std::runtime_error("Resources not properly assigned for process: " + name);
    }
    std::cout << "Executing process: " << name << ": "
    << description
    << " (Duration: " << durationInUnits << " units)"
    << std::endl;
    if (!assignedResources.empty()) {
        for (const auto &resource : assignedResources) {
            resource->use();
        }
    }

    for (const auto &task : tasks) {
        try {
            if (task->canExecute(resourcePool)) {
                task->assignResources(resourcePool);
                std::cout << "  ";
                task->execute();
                task->releaseResources();
            } else {
                std::cout << "  Task " << task->getName() << " skipped: insufficient resources." << std::endl;
            }
        } catch (const std::exception &e) {
            std::cerr << "Error in task " << task->getName() << ": " << e.what() << std::endl;
        }
    }
}

void Process::run() {
    try {
        if (requiredResourcesNames.empty() || canExecute(resourcePool)) {
            if (!requiredResourcesNames.empty()) {
                assignResources(resourcePool);
            }
            execute();
            releaseResources();
            std::cout << "Process " << name << " completed successfully." << std::endl;
        } else {
            throw std::runtime_error("Process " + name + " cannot be executed due to insufficient resources.");
        }
    } catch (std::exception &e) {
        std::cerr << "Error in process " << name << ": " << e.what() << std::endl;
    }
}


