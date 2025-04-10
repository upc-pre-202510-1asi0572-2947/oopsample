#include "Executable.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

Executable::Executable(
    const std::string &name,
    const std::string &description,
    const std::vector<std::string> &requiredResourcesNames,
    const int durationInUnits) :
    name(name),
description(std::move(description)),
requiredResourcesNames(requiredResourcesNames),
durationInUnits(durationInUnits),
assignedResources() {
    if (name.empty()) throw std::invalid_argument("Executable name cannot be empty");
    if (durationInUnits <= 0) throw std::invalid_argument("Duration for " + name + "must be positive");
}

std::string Executable::getName() const {
    return name;
}

int Executable::getDurationInUnits() const {
    return durationInUnits;
}

void Executable::assignResources(const std::vector<std::unique_ptr<Resource> > &resourcePool) {
    assignedResources.clear();
    if (requiredResourcesNames.empty()) return;
    for (const auto &resourceName: requiredResourcesNames) {
        bool found = false;
        for (const auto &resource: resourcePool) {
            if (resource->getName() == resourceName && resource->isAvailableForUse()) {
                resource->allocate();
                assignedResources.push_back(resource.get());
                found = true;
                break;
            }
        }
        if (!found) {
            releaseResources();
            throw std::invalid_argument("Resource " + resourceName + " not found or not available for " + name);
        }
    }
}

void Executable::releaseResources() {
    for (auto *resource: assignedResources) {
        try {
            resource->release();
        } catch (const std::exception &e) {
            std::cerr << "Warning: Failed to release resource " << resource->getName() << " for " << name << ": " << e.what() << std::endl;
        }
    }
    assignedResources.clear();
}

bool Executable::canExecute(const std::vector<std::unique_ptr<Resource> > &resourcePool) const {
    if (requiredResourcesNames.empty()) {
        std::cout << "No resources required for task " << name << std::endl;
        return true;
    }
    for (const auto &resourceName: requiredResourcesNames) {
        if (std::none_of(resourcePool.begin(), resourcePool.end(),
            [&resourceName](const std::unique_ptr<Resource> &resource) {
                return resource->getName() == resourceName && resource->isAvailableForUse();
            })) {
            return false;
        }
    }
    return true;
}



