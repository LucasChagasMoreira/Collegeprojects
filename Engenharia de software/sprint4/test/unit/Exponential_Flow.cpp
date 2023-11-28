#include "Exponential_Flow.hpp"

Exponential_Flow::Exponential_Flow()
{
    name = "NULL";
    origin = NULL;
    target = NULL;
}

Exponential_Flow::Exponential_Flow(Flow &obj)
{
    if (&obj == this)
        return;

    name = obj.getName();
    origin = obj.getOrigin();
    target = obj.getTarget();
};

Exponential_Flow::Exponential_Flow(const string name, System *origin, System *target) : Flow_Impl(name, origin, target){};
Exponential_Flow::~Exponential_Flow() {}

double Exponential_Flow::execute()
{
    return getOrigin()->getValue() * 0.01;
};