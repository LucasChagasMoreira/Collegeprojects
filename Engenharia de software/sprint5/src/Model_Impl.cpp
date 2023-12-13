#include "Model_Impl.hpp"
#include "System_Impl.hpp"
#include "Flow_Impl.hpp"
vector<Model *> Model_Impl::models;
Model_Impl::Model_Impl()
{
    name = "NULL";
    flow_list.clear();
    system_list.clear();
}

Model_Impl::Model_Impl(const string name) : name(name) {}

Model_Impl::Model_Impl(Model &obj)
{
    if (&obj == this)
        return;

    name = obj.getName();
}

Model_Impl::~Model_Impl()
{
    for(auto system : system_list){
        delete system;
    }
    for(auto flow : flow_list){
        delete flow;
    }
    for(itModel it = getModelbegin(); it<getModelEnd(); it++){
        if((*it)==this){
            models.erase(it);
            break;
        }
    }
}

string Model_Impl::getName() const
{
    return name;
}

void Model_Impl::setName(const string name)
{
    this->name = name;
}

Model* Model_Impl :: createModel(string name){
    Model * model = new Model_Impl(name);
    models.push_back(model);
    return model;
}

Model* Model :: createModel(string name_m)
{
    return Model_Impl::createModel(name_m);
}

System *Model_Impl::createSystem(string name_s, double value_s)
{
    System *sys = new System_Impl(name_s, value_s);
    add(sys);
    return sys;
}

void Model_Impl::setSource(Flow* flow, System* system)
{
    flow->setOrigin(system);
}

void Model_Impl::setDestiny(Flow* flow, System* system)
{
    flow->setTarget(system);
}

Model_Impl::itFlow Model_Impl::getFlowBegin()
{
    return flow_list.begin();
}

Model_Impl::itFlow Model_Impl::getFlowEnd()
{
    return flow_list.end();
}

int Model_Impl::getFlowSize()
{
    return flow_list.size();
}

Model_Impl::itSystem Model_Impl::getSystemBegin()
{
    return system_list.begin();
}

Model_Impl::itSystem Model_Impl::getSystemEnd()
{
    return system_list.end();
}

int Model_Impl::getSystemSize()
{
    return system_list.size();
}

Model_Impl::itModel Model_Impl::getModelbegin(){
    return models.begin();
}

Model_Impl::itModel Model_Impl::getModelEnd(){
    return models.end();
}

int Model :: getModelsize(){
    return Model_Impl::getModelsize();
}

int Model_Impl :: getModelsize(){
    return models.size();
}
void Model_Impl::add(System *subSystem)
{
    system_list.push_back(subSystem);
}

void Model_Impl::add(Flow *flow)
{
    flow_list.push_back(flow);
}

bool Model_Impl::remove(System *obj)
{
    for (auto thisystem = system_list.begin(); thisystem != system_list.end(); thisystem++)
    {
        if (*thisystem == obj)
        {
            system_list.erase(thisystem);
            return true;
        }
    }
    return false;
}

bool Model_Impl::remove(Flow *obj)
{
    for (auto thisFlows = flow_list.begin(); thisFlows != flow_list.end(); thisFlows++)
    {
        if (*thisFlows == obj)
        {
            flow_list.erase(thisFlows);
            return true;
        }
    }
    return false;
}

Model_Impl& Model_Impl::operator=(const Model_Impl &obj)
{
    if (this != &obj)
    {
        this->flow_list.clear();
        this->system_list.clear();
        this->flow_list.insert(this->flow_list.begin(), obj.flow_list.begin(), obj.flow_list.end());
        this->system_list.insert(this->system_list.begin(), obj.system_list.begin(), obj.system_list.end());
    }
    return *this;
}

void Model_Impl::clear()
{
    name = "NULL";
    flow_list.clear();
    system_list.clear();
}

int Model_Impl::run(int ini_time, int fin_time)
{
    vector<Flow *>::iterator flow_iterator;

    System *origin_system;
    System *target_system;

    vector<double> flow_values;
    const double flow_init_value = 0.0;

    for (int i = 0; i < int(flow_list.size()); i++)
        flow_values.push_back(flow_init_value);
    
    int i, j;
    for (int time_count = ini_time; time_count < fin_time; time_count++)
    {
        i = 0;
        flow_iterator = flow_list.begin();
        while (i < int(flow_list.size()))
        {
            flow_values[i] = (*flow_iterator)->execute();
            flow_iterator++;
            i++;
        }

        j = 0;
        while (j < int(flow_list.size()))
        {
            origin_system = flow_list[j]->getOrigin();
            origin_system->setValue(origin_system->getValue() - flow_values[j]);

            target_system = flow_list[j]->getTarget();
            target_system->setValue(target_system->getValue() + flow_values[j]);
            j++;
        }
    }
    return 1;
}

void Model_Impl::show()
{
    cout << endl;
}