#ifndef FLOW_HPP
#define FLOW_HPP
#include <iostream>
#include <string>
#include "System.hpp"
/// @brief A Flow is a connection between two systems.
class Flow
{
        public:
            Flow();
            virtual ~Flow();

        protected:
            string name;
            System *origin;
            System *target;

        public:
            Flow(const string name, System *origin, System *target);

            Flow(const Flow &obj);
            Flow &operator=(const Flow &obj);

            string getName() const;
            void setName(const string name);
            System *getOrigin() const;
            void setOrigin(System *origin);
            System *getTarget() const;
            void setTarget(System *target);


            /// @brief Virtual function to be implemented.
            
            virtual double execute() = 0;
            
};
#endif