#ifndef LOGISTIC_FLOW_HPP
    #define LOGISTIC_FLOW_HPP

    #include "Flow.hpp"

    /// @brief A Flow with a logistic equation.
    class LogisFlow : public Flow
    {
        public:
            LogisFlow();
            LogisFlow(Flow &obj);
            LogisFlow(const string name, System *origin, System *target);
            virtual ~LogisFlow();

            virtual double execute();
    };
#endif