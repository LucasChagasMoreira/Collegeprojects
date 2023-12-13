#include "Logistic_Flow.hpp"

Logistic_Flow::Logistic_Flow() : Flow_Impl(){}


Logistic_Flow::Logistic_Flow(Flow &obj) : Flow_Impl(obj){}


Logistic_Flow::Logistic_Flow(const string name, System *origin, System *target) : Flow_Impl(name, origin, target){};
Logistic_Flow::~Logistic_Flow() {}

double Logistic_Flow::execute()
{
    return ((0.01 * getTarget()->getValue()) * (1 - getTarget()->getValue() / 70));
};