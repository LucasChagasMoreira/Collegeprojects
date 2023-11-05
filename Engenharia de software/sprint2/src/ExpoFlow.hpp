#ifndef EXPONENTIAL_FLOW_HPP
#define EXPONENTIAL_FLOW_HPP

    #include "Flow.hpp"

    /// @brief A Flow with an exponential equation.
    class Expo_Flow : public Flow
    {
        public:
            Expo_Flow();
            Expo_Flow(Flow &obj);
            Expo_Flow(const string name, System *origin, System *target);
            virtual ~Expo_Flow();
            virtual double execute();
    };
#endif