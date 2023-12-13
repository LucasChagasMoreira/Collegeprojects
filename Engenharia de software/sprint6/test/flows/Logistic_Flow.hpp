#ifndef LOGISTIC_FLOW_HPP
    #define LOGISTIC_FLOW_HPP

    #include "../../src/Flow_Impl.hpp"

    /// @brief A Flow with a logistic equation.
    class Logistic_Flow : public Flow_Impl
    {
        public:
            Logistic_Flow();
            Logistic_Flow(Flow &obj);
            Logistic_Flow(const string name, System *origin, System *target);
            virtual ~Logistic_Flow();

            virtual double execute();
    };
#endif