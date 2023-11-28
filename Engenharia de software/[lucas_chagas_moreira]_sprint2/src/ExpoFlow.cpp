#include "ExpoFlow.hpp"

Expo_Flow::Expo_Flow()
{
    name = "NULL";
    origin = NULL;
    target = NULL;
}

Expo_Flow::Expo_Flow(Flow &obj)
{
    if (&obj == this)
        return;

    name = obj.getName();
    origin = obj.getOrigin();
    target = obj.getTarget();
};

Expo_Flow::Expo_Flow(const string name, System *origin, System *target) : Flow(name, origin, target){};
Expo_Flow::~Expo_Flow() {}

double Expo_Flow::execute()
{
    return getOrigin()->getValue() * 0.01;
};