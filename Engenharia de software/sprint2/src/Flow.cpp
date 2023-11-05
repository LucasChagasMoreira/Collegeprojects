#include "Flow.hpp"

Flow::Flow()
{
    name = "NULL";
    origin = NULL;
    target = NULL;
}

Flow::Flow(const Flow &obj)
{
    if (&obj == this)
        return;

    name = obj.getName();
    origin = obj.getOrigin();
    target = obj.getTarget();
}

Flow::Flow(const string name, System *origin, System *target) : name(name), origin(origin), target(target){};
Flow::~Flow(){};

string Flow::getName() const
{
    return name;
}

void Flow::setName(const string name)
{
    this->name = name;
}

System *Flow::getOrigin() const
{
    return origin;
}

void Flow::setOrigin(System *origin)
{
    this->origin = origin;
}

System *Flow::getTarget() const
{
    return target;
}

void Flow::setTarget(System *target)
{
    this->target = target;
}

Flow &Flow::operator=(const Flow &obj)
{
    if (&obj == this)
        return *this;

    name = obj.getName();
    origin = obj.getOrigin();
    target = obj.getTarget();

    return *this;
}
