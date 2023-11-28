#ifndef MODEL_HPP
    #define MODEL_HPP

    #include <cstring>
    #include <ostream>
    #include <vector>
    
    #include "Flow.hpp"
    #include "System.hpp"

    /// A Model is what integrates flows and systems.
    ///
    /// By creating a model, you can run() simulations.
    class Model
    {   
        public:
            virtual ~Model() {}
            /// @brief iterator
            typedef typename vector<Flow *>::iterator itFlow;
            typedef typename vector<System *>::iterator itSystem;

            /// @brief getter of the atribute "name"
            virtual string getName() const = 0;
            /// @brief setter of the atribute "name"
            virtual void setName(const string name) = 0;

            /// @brief get the first element in the flow container
            virtual itFlow getFlowBegin() = 0;
            /// @brief get the last element in the flow container
            virtual itFlow getFlowEnd() = 0;
            /// @brief get the size of the flow container
            virtual int getFlowSize() = 0;

            /// @brief get the first element in the system container
            virtual itSystem getSystemBegin() = 0;
            /// @brief get the last element in the system container
            virtual itSystem getSystemEnd() = 0;
            /// @brief get the size of the system container
            virtual int getSystemSize() = 0;

            /// @brief add a system in the container
            virtual void add(System *) = 0;
            /// @brief add a flow in the container
            virtual void add(Flow *) = 0;
            /// @brief remoce a system
            virtual bool remove(System *) = 0;
            /// @brief remove a Flow
            virtual bool remove(Flow *) = 0;
            /// @brief remove all elements
            virtual void clear() = 0;
            /// @brief print the model
            virtual void show() = 0;

            /// @brief Run a model simulation by passing the time information.
            /// @param ini_time  Initial time.
            /// @param fin_time  Final time.
            virtual int run(int, int) = 0;
    };
#endif
