#include "CondorEngine/object.h"
#include "CondorEngine/serialization.hpp"

CondorEngine::Object::Object(std::string name)
{
    this->name = name;
    this->enabled = true;

    static unsigned int idIndex = 0;
    this->id = idIndex++;
}

CondorEngine::Object::Object() : Object("Object") {}

std::string CondorEngine::Object::to_string()
{
    std::string str = name;
    str.append("(");
    str.append(GetType());
    str.append(")");
    return str;
}
