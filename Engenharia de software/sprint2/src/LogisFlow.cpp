#include "LogisFlow.hpp"

LogisFlow::LogisFlow()
{
    name = "NULL";
    origin = NULL;
    target = NULL;
}

LogisFlow::LogisFlow(Flow &obj)
{
    if (&obj == this)
        return;

    name = obj.getName();
    origin = obj.getOrigin();
    target = obj.getTarget();
};

LogisFlow::LogisFlow(const string name, System *origin, System *target) : Flow(name, origin, target){};
LogisFlow::~LogisFlow() {}

double LogisFlow::execute()
{
    return ((0.01 * getTarget()->getValue()) * (1 - getTarget()->getValue() / 70));
};