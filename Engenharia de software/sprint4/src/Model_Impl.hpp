#ifndef MODEL_IMPL_HPP
    #define MODEL_IMPL_HPP

    #include <cstring>
    #include <ostream>
    #include <vector>
    
    #include "Model.hpp"

    /// A Model is what integrates flows and systems.
    ///
    /// By creating a Model, you can run() simulations.
    class Model_Impl : public Model
    {
        public:
            Model_Impl();
            virtual ~Model_Impl();

        protected:
            string name;
            vector<Flow *> flow_list;
            vector<System *> system_list;
        
        public:
            Model_Impl(const string name);

            Model_Impl(Model &obj);
            // Model& operator= (const Model& obj);

            typedef typename vector<Flow *>::iterator itFlow;
            typedef typename vector<System *>::iterator itSystem;

            /// @return The model name.
            string getName() const;
            void setName(const string name);

            /// @return the first element of the flow container
            itFlow getFlowBegin();
            /// @return the last element of the flow container
            itFlow getFlowEnd();
            /// @return the number of elements in the flow container
            int getFlowSize();

            /// @return the first element of the System container
            itSystem getSystemBegin();
            /// @return the last element of the System container
            itSystem getSystemEnd();
            /// @return the number of elements in the flow container
            int getSystemSize();

            /// @return adds a System into the model
            void add(System *);
            /// @return adds a Flow into the model
            
            void add(Flow *);
            /// @return removes a System into the model
            bool remove(System *);
            /// @return removes a Flow into the model
            bool remove(Flow *);
            /// @return removes all elements in Flow or System container
            void clear();
            /// @return print the model
            void show();
            
            /// @brief Run a model simulation by passing the time information.
            /// @param ini_time  Initial time.
            /// @param fin_time  Final time.
            /// @return the final values of the systems
            int run(int, int);
    };
#endif
