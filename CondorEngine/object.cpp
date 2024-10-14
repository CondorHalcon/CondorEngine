#include "object.h"

CondorEngine::Object::Object(std::string name)
{
    this->name = name;
    this->enabled = true;
}

CondorEngine::Object::Object() : Object("CondorEngine::Object") {}

std::string CondorEngine::Object::to_string() 
{
    return name;
}
