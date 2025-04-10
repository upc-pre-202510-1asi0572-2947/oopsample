#include "ConsumableResource.h"
#include <stdexcept>
#include <iostream>

/**
 * @brief Constructor for ConsumableResource with a name and capacity.
 * @param name The name of the resource.
 * @param capacity The total capacity of the resource.
 * @throws std::invalid_argument if capacity is not positive.
 */
ConsumableResource::ConsumableResource(const std::string &name, int capacity)
    : Resource(name, Type::Consumable),
      totalCapacity(capacity),
      remainingCapacity(capacity) {
    if (capacity <= 0) {
        throw std::invalid_argument("Capacity for resource "+ name + "must be positive.");
    }
}

/**
 * @brief Checks if the resource has remaining capacity for allocation.
 * @return True if the resource has remaining capacity, false otherwise.
 */
bool ConsumableResource::isAvailableForUse() const {
    return remainingCapacity > 0;
}

void ConsumableResource::allocate() {
    if (remainingCapacity <= 0) {
        throw std::runtime_error("No remaining capacity for consumable resource " + getName());
    }
    --remainingCapacity;
    isAvailable = (remainingCapacity > 0);
}

void ConsumableResource::release() {
    if (remainingCapacity == 0 && !isAvailable) {
        std::cerr << "Warning: Consumable resource " << name << " is depleted and cannot be reused without replenishment." << std::endl;
    }
    ++remainingCapacity;
    isAvailable = (remainingCapacity > 0);
}

void ConsumableResource::use() const {
    std::cout << "    Using consumable resource: " << name
    << " (remaining: " << remainingCapacity << "/"<<totalCapacity << "MB)" << std::endl;
}

int ConsumableResource::getRemainingCapacity() const {
    return remainingCapacity;
}

