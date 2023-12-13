#ifndef EXPONENTIAL_FLOW_HPP
    #define EXPONENTIAL_FLOW_HPP

    #include "../../src/Flow_Impl.hpp"

    /// @brief A Flow with an exponential equation.
    class Exponential_Flow : public Flow_Impl
    {
        public:
            Exponential_Flow();
            Exponential_Flow(Flow &obj);
            Exponential_Flow(const string name, System *origin, System *target);
            virtual ~Exponential_Flow();

            virtual double execute();
    };
#endif