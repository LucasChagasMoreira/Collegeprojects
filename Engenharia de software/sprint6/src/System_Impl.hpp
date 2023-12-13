#ifndef SYSTEM_IMPL_HPP
    #define SYSTEM_IMPL_HPP

    #include <string>
    #include <ostream>

    #include "System.hpp"
    #include "handleBody.hpp"

    using namespace std;

    /// @brief Implementation of System's methods
    class System_Impl : public Body
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

    class SystemHandle : public System, public Handle<System_Impl>{
    public:
        SystemHandle(){
            pImpl_->setName("");
            pImpl_->setValue(0.0);
        }
        /**
     * @brief System constructor that works as default as well
     * @param name system name
     * @param value system initial value
    */
        SystemHandle(const string name,double value){
            pImpl_->setName(name);
            pImpl_->setValue(value);
        };
        SystemHandle(double value){
            pImpl_->setValue(value);
            pImpl_->setName("");
        };
        SystemHandle(const string name){
            pImpl_->setName(name);
            pImpl_->setValue(0);
        };
            /**
     * @brief Constructor for copy of system
     * @param s system object that will be copied
    */
        SystemHandle(System &obj){
            pImpl_->setName(obj.getName());
            pImpl_->setValue(obj.getValue());
        };
    /**
     * @brief Sets the system name
     * @param name system name
    */
        void setName(const string name){
            pImpl_->setName(name);
        };
            /**
     * @brief Returns the system name
     * @return a string containing the system name
    */
        string getName() const{
            return pImpl_->getName();
        };
            /**
     * @brief Returns the system value
     * @return a double containing the system value
    */
        double getValue() const{
            return pImpl_->getValue();
        };
            /**
     * @brief Sets the system value
     * @param value system value
    */
        void setValue(double value){
            pImpl_->setValue(value);
        };
            /**
     * @brief Defines how the '=' operator works for systems
     * @param s system object that will be copied
     * @return a reference to the copied system
    */
        System& operator=(const System &obj){
            if(this == &obj) return *this;
            pImpl_->setName(obj.getName());
            pImpl_->setValue(obj.getValue());

            return *this;
        };
    /**
     * @brief Defines how the '=' operator works for systems
     * @param s system object that will be copied
     * @return a reference to the copied system
    */
        SystemHandle& operator=(const SystemHandle& s){
            if(this == &s) return *this;

            pImpl_->setName(s.getName());
            pImpl_->setValue(s.getValue());

            return *this;
        }        
    };
#endif