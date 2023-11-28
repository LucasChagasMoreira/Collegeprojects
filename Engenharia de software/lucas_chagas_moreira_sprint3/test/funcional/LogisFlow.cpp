#include "LogisFlow.hpp"

LogisFlow::LogisFlow(const string name, System *origin, System *target) : Flow(name, origin, target){};


double LogisFlow::execute()
{
    return ((0.01 * getTarget()->getValue()) * (1 - getTarget()->getValue() / 70));
};