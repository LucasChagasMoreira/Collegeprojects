#ifndef SYSTEM_IMPL_HPP
    #define SYSTEM_IMPL_HPP

    #include <string>
    #include <ostream>

    #include "System.hpp"

    using namespace std;

    /// @brief Implementation of System's methods
    class System_Impl : public System
    {
        public:
            System_Impl();
            virtual ~System_Impl();

        protected:
            string name;
            double value; //!< System's energy.

        public:
            System_Impl(const string name);
            System_Impl(double value);
            System_Impl(const string name, double value);

            /// @return constructor 
            System_Impl(System &obj);
            /// @return overload of the `=` operator
            System &operator=(const System &obj);
            /// @return the name of the System
            string getName() const;
            void setName(const string name);
            /// @return the value of the System
            double getValue() const;
            void setValue(double value);
    };
#endif