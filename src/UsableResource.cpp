#include "UsableResource.h"
#include <iostream>
#include <stdexcept>

UsableResource::UsableResource(const std::string &name, const int capacity)
    : Resource(name, Type::Usable), capacity(capacity){
    if (capacity <= 0) {
        throw std::invalid_argument("Capacity for resource " + name + " must be positive");
    }
}

bool UsableResource::isAvailableForUse() const {
    return isAvailable;
}

void UsableResource::allocate() {
    if (!isAvailable) {
        throw std::runtime_error("Usable Resource " + name + " is already allocated");
    }
    isAvailable = false;
}

void UsableResource::release() {
    if (isAvailable) {
        std::cerr << "Warning: Attempting to release an already available resource " << name << std::endl;
    }
}

void UsableResource::use() const {
    std::cout << "    Using resource " << name << " (capacity: " << capacity << " GHz)" << std::endl;
}



