#include "Exponential_Flow.hpp"

Exponential_Flow::Exponential_Flow():Flow_Impl(){}


Exponential_Flow::Exponential_Flow(Flow &obj) : Flow_Impl(obj){}


Exponential_Flow::Exponential_Flow(const string name, System *origin, System *target) : Flow_Impl(name, origin, target){};
Exponential_Flow::~Exponential_Flow() {}

double Exponential_Flow::execute()
{
    return getOrigin()->getValue() * 0.01;
};