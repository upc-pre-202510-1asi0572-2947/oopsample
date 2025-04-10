#include "Resource.h"

Resource::Resource(std::string name, Type type)
    : name(std::move(name)), isAvailable(true), resourceType(type){}

std::string Resource::getName() const { return name; }

Resource::Type Resource::getResourceType() const { return resourceType; }


