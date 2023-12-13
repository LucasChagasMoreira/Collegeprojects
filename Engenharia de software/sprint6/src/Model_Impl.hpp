#ifndef MODEL_IMPL_HPP
    #define MODEL_IMPL_HPP

    #include <cstring>
    #include <ostream>
    #include <vector>
    
    #include "Model.hpp"
    #include "handleBody.hpp"

    /// A Model is what integrates flows and systems.
    ///
    /// By creating a Model, you can run() simulations.
    class Model_Impl : public Body
    {
        public:
            Model_Impl();
            virtual ~Model_Impl();

        protected:
            string name;
            vector<Flow *> flow_list;
            vector<System *> system_list;
            static vector<Model *> models;

        
        public:
        
            /// @return adds a System into the model
            void add(System *);
            /// @return adds a Flow into the model
            void add(Flow *);
            Model_Impl(const string name);

            void setSource(Flow*, System*);
            void setDestiny(Flow*, System*);

            typedef typename vector<Flow *>::iterator itFlow;
            typedef typename vector<System *>::iterator itSystem;
            typedef typename vector<Model *>::iterator itModel;
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

            itModel getModelbegin();
            itModel getModelEnd();
            static int getModelsize();
            
            void eraseModel(Model::itModel m);

            /// @return removes a System into the model
            bool remove(System *);
            /// @return removes a Flow into the model
            bool remove(Flow *);
            /// @return removes all elements in Flow or System container
            void clear();
            /// @return print the model
            void show();

            static Model* createModel(string name);
            System *createSystem(string name_s, double value_s);
            /// @brief Run a model simulation by passing the time information.
            /// @param ini_time  Initial time.
            /// @param fin_time  Final time.
            /// @return the final values of the systems
            int run(int, int);
        private:
            Model_Impl(Model_Impl &obj);
            Model_Impl& operator= (const Model_Impl& obj);
    };

    class ModelHandle : public Model, public Handle<Model_Impl>{
    public:
        /**
     * @brief Adds a pointer to a flow in the flows vector
     * @param f pointer to a flow
     * @return bool representing whether the operation completed successfully
    */
        void add(Flow* f){
            pImpl_->add(f);
        };
         /**
     * @brief Adds a pointer to a system in the systems vector
     * @param s pointer to a system
     * @return bool representing whether the operation completed successfully
    */
        void add(System* s){
            pImpl_->add(s);
        };
         /**
     * @brief Model constructor that works as default as well
     * @param name model name
     * @param clock model clock value
    */
        ModelHandle(const string& name = ""){
            pImpl_->setName(name);
        };
        /**
     * @brief Virtual class destructor
    */
        ~ModelHandle(){
            for(Model::itModel it = getModelbegin(); it < getModelEnd(); it++){
                if(*it == this){
                    pImpl_->eraseModel(it);
                    break;
                }     
            }
        };
        /**
     * @brief Creates a new System and add it to the model
    */
        System *createSystem(string name,double values_s){
            return pImpl_->createSystem(name,values_s);
        };
            /**
     * @brief Removes the system pointer 's' of the systems vector and deletes it of the memory
     * @param s pointer to a system
     * @return bool representing whether the operation completed successfully
    */
        bool remove(Flow * f){
            return pImpl_->remove(f);
        };
        /**
     * @brief Removes the flow pointer 'f' of the flows vector and deletes it of the memory
     * @param f pointer to a flow
     * @return bool representing whether the operation completed successfully
    */
        bool remove(System * s){
            return pImpl_->remove(s);
        };
        void show(){
            pImpl_->show();
        };
        void clear(){
            pImpl_->clear();
        };

        int getSystemSize(){
            return pImpl_->getSystemSize();
        };
            /**
     * @brief Returns the iterator of the beginning of the systems vector
     * @return systemsIterator being the iterator of the beginning of the vector
    */
        itSystem getSystemBegin(){
            return pImpl_->getSystemBegin();
        };
            /**
     * @brief Returns the iterator of the end of the systems vector
     * @return systemsIterator being the iterator of the end of the vector
    */
        itSystem getSystemEnd(){
            return pImpl_->getSystemEnd();
        };
            /**
     * @brief Returns the iterator of the end of the models vector
     * @return modelsIterator iterator of the end of the models vector
    */

        itModel getModelEnd(){
            return pImpl_->getModelEnd();
        };
           /**
     * @brief Returns the iterator of the beginning of the models vector
     * @return modelsIterator iterator of the beginning of the models vector
    */
        itModel getModelbegin(){
            return pImpl_->getModelbegin();
        };
        static int getModelsize();
    /**
     * @brief Returns the iterator of the beginning of the flows vector
     * @return flowsIterator being the iterator of the beginning of the vector
    */
        itFlow getFlowBegin(){
            return pImpl_->getFlowBegin();
        };
        /**
     * @brief Returns the iterator of the end of the flows vector
     * @return flowsIterator being the iterator of the end of the vector
    */
        itFlow getFlowEnd(){
            return pImpl_->getFlowEnd();
        };
        int getFlowSize(){
            return pImpl_->getFlowSize();
        };

        void setName(const string name){
            pImpl_->setName(name);
        };
        /**
     * @brief Returns the model name
     * @return string containing the model name
    */
        string getName() const{
            return pImpl_->getName();
        };
    /**
     * @brief Returns the model name
     * @return string containing the model name
    */
        void setSource(Flow*f,System* s){
            pImpl_->setSource(f,s);
        };

        void setDestiny(Flow*f1,System* t){
            pImpl_->setDestiny(f1,t);
        };
        /**
     * @brief Executes the model, performing flow operations and updating system values
     * @param startTime when the execution of the model starts
     * @param finalTime when the execution of the model ends
     * @return bool representing whether the execution completed successfully
    */
        int run(int inicial,int final){
            return pImpl_->run(inicial,final);
        };
    };
#endif
