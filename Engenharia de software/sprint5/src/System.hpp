#ifndef SYSTEM_HPP
    #define SYSTEM_HPP

    #include <string>
    #include <ostream>

    using namespace std;

    /// @brief A System is a stock of energy.
    class System
    {
        public:
            /// @brief destructor
            virtual ~System() {}
             /// @brief overload of the "=" operator
            virtual System &operator=(const System &obj) = 0;
            /// @brief getter of the name
            virtual string getName() const = 0;
            /// @brief setter of the name
            virtual void setName(const string name) = 0;
            /// @brief getter of the Value
            virtual double getValue() const = 0;
            /// @brief setter of the Value
            virtual void setValue(double value) = 0;
    };
#endif