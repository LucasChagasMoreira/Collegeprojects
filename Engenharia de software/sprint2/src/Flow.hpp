#ifndef FLOW_HPP
#define FLOW_HPP
#include <iostream>
#include <string>
#include "System.hpp"

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

            Flow(Flow &obj);
            Flow &operator=(const Flow &obj);

            string getName() const;
            void setName(const string name);
            System *getOrigin() const;
            void setOrigin(System *origin);
            System *getTarget() const;
            void setTarget(System *target);
            virtual double execute() = 0;
            
};
#endif