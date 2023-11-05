#ifndef SYSTEM_HPP
    #define SYSTEM_HPP

    #include <string>
    #include <ostream>

    using namespace std;

    /// @brief A System is a stock of energy.
    class System
    {
        public:
            System();
            virtual ~System();

        protected:
            string name;
            double value; //!< System's energy.

        public:
            System(const string name);
            System(double value);
            System(const string name, double value);

            System(System &obj);
            System &operator=(const System &obj);

            string getName() const;
            void setName(const string name);
            double getValue() const;
            void setValue(double value);
    };
#endif