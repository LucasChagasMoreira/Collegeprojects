#ifndef LOGISTIC_FLOW_HPP
    #define LOGISTIC_FLOW_HPP

    #include "../../src/Flow.hpp"

    /// @brief A Class that inherits "Flow" implementing the virtual function "execute" with a logistic equation.
    class LogisFlow : public Flow
    {
        public:
            LogisFlow(const string name, System *origin, System *target);
            

            virtual double execute();
    };
#endif