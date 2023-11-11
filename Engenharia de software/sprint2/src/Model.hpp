#ifndef MODEL_HPP
#define MODEL_HPP

    #include <cstring>
    #include <ostream>
    #include <vector>
    
    #include "Flow.hpp"
    #include "System.hpp"
    #include "Model.hpp"

    /// @brief A Model unites flows and systems. By creating a model, you can run() method to start the simulations.

    class Model
    {
        private:
            Model &operator=(const Model &obj);
        public:
            Model();
            virtual ~Model();

        protected:
            string name;
            vector<Flow *> flow_list;
            vector<System *> system_list;
        
        public:
            Model(const string name);

            Model(const Model &obj);
            

            typedef typename vector<Flow *>::iterator itFlow;
            typedef typename vector<System *>::iterator itSystem;

            string getName() const;
            void setName(const string name);

            itFlow getFlowBegin();
            itFlow getFlowEnd();
            int getFlowSize();

            itSystem getSystemBegin();
            itSystem getSystemEnd();
            int getSystemSize();

            void add(System *);
            void add(Flow *);
            bool remove(System *);
            bool remove(Flow *);
            void clear();
            void show();
            
            /// @brief Run a model simulation by passing the time information.
            /// @param ini_time  Initial time.
            /// @param fin_time  Final time.
            void run(int, int);
    };
#endif
