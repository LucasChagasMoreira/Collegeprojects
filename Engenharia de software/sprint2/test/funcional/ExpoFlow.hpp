#ifndef EXPONENTIAL_FLOW_HPP
#define EXPONENTIAL_FLOW_HPP

    #include "../../src/Flow.hpp"

    /// @brief A Class that inherits "Flow" implementing the virtual function "execute" with a exponential equation.
    class Expo_Flow : public Flow
    {
        public:
           
            Expo_Flow(const string name, System *origin, System *target);
            
            virtual double execute();
    };
#endif