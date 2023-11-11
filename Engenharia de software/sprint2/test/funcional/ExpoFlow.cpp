#include "ExpoFlow.hpp"

Expo_Flow::Expo_Flow(const string name, System *origin, System *target) : Flow(name, origin, target){};


double Expo_Flow::execute()
{
    return getOrigin()->getValue() * 0.01;
};