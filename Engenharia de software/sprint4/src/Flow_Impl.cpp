#include "Flow_Impl.hpp"

Flow_Impl::Flow_Impl()
{
    name = "NULL";
    origin = NULL;
    target = NULL;
}

Flow_Impl::Flow_Impl(Flow &obj)
{
    if (&obj == this)
        return;

    name = obj.getName();
    origin = obj.getOrigin();
    target = obj.getTarget();
}

Flow_Impl::Flow_Impl(const string name, System *origin, System *target) : name(name), origin(origin), target(target){};
Flow_Impl::~Flow_Impl(){};

string Flow_Impl::getName() const
{
    return name;
}

void Flow_Impl::setName(const string name)
{
    this->name = name;
}

System *Flow_Impl::getOrigin() const
{
    return origin;
}

void Flow_Impl::setOrigin(System *origin)
{
    this->origin = origin;
}

System *Flow_Impl::getTarget() const
{
    return target;
}

void Flow_Impl::setTarget(System *target)
{
    this->target = target;
}

Flow &Flow_Impl::operator=(const Flow &obj)
{
    if(&obj == this)
        return *this;

    name = obj.getName();
    origin = obj.getOrigin();
    target = obj.getTarget();
    
    return *this;
}