#ifndef MODEL_HPP
    #define MODEL_HPP

    #include <cstring>
    #include <ostream>
    #include <vector>
    
    #include "Flow_Impl.hpp"
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
            typedef typename vector<Model *>::iterator itModel;

            virtual void setSource(Flow*, System*) = 0;
            virtual void setDestiny(Flow*, System*) = 0;


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

            virtual itModel getModelbegin()=0;
            virtual itModel getModelEnd()=0;
            static int getModelsize();

            
            /// @brief remoce a system
            virtual bool remove(System *) = 0;
            /// @brief remove a Flow
            virtual bool remove(Flow *) = 0;
            /// @brief remove all elements
            virtual void clear() = 0;
            /// @brief print the model
            virtual void show() = 0;

            ///
            static Model* createModel(string name);

            virtual System* createSystem(string name_s, double value_s) = 0;

            template <typename T>
            
            Flow* createFlow(string name_f, System *source_f, System *destiny_f)
            {
                Flow *f = new FlowHandle<T>(name_f, source_f, destiny_f);
                add(f);
                return f;
            }
            /// @brief Run a model simulation by passing the time information.
            /// @param ini_time  Initial time.
            /// @param fin_time  Final time.
            virtual int run(int, int) = 0;
            /// @brief add a system in the container
            virtual void add(System *) = 0;
            /// @brief add a flow in the container
            virtual void add(Flow *) = 0;
            /// @brief 
    };
#endif
