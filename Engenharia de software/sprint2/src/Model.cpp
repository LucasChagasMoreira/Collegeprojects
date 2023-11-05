#include "Model.hpp"

Model::Model()
{
    name = "NULL";
    flow_list.clear();
    system_list.clear();
}

Model::Model(const string name) : name(name) {}

Model::Model(const Model &obj)
{
    if (&obj == this)
        return;

    name = obj.getName();
}

Model::~Model() {}

string Model::getName() const
{
    return name;
}

void Model::setName(const string name)
{
    this->name = name;
}

Model::itFlow Model::getFlowBegin()
{
    return flow_list.begin();
}

Model::itFlow Model::getFlowEnd()
{
    return flow_list.end();
}

int Model::getFlowSize()
{
    return flow_list.size();
}

Model::itSystem Model::getSystemBegin()
{
    return system_list.begin();
}

Model::itSystem Model::getSystemEnd()
{
    return system_list.end();
}

int Model::getSystemSize()
{
    return system_list.size();
}

void Model::add(System *subSystem)
{
    system_list.push_back(subSystem);
}

void Model::add(Flow *flow)
{
    flow_list.push_back(flow);
}

bool Model::remove(System *obj)
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

bool Model::remove(Flow *obj)
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

Model &Model::operator=(const Model &obj)
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

void Model::clear()
{
    name = "NULL";
    flow_list.clear();
    system_list.clear();
}

void Model::run(int ini_time, int fin_time)
{
    vector<Flow *>::iterator flow_iterator;

    System *origin_system;
    System *target_system;

    vector<double> flow_values;
    const double flow_init_value = 0.0;

    for (int i = 0; i < flow_list.size(); i++)
        flow_values.push_back(flow_init_value);
    
    int i, j;
    for (int time_count = ini_time; time_count <= fin_time; time_count++)
    {
        i = 0;
        flow_iterator = flow_list.begin();
        while (i < flow_list.size())
        {
            flow_values[i] = (*flow_iterator)->execute();
            flow_iterator++;
            i++;
        }

        j = 0;
        while (j < flow_list.size())
        {
            origin_system = flow_list[j]->getOrigin();
            origin_system->setValue(origin_system->getValue() - flow_values[j]);

            target_system = flow_list[j]->getTarget();
            target_system->setValue(target_system->getValue() + flow_values[j]);
            j++;
        }
    }
}

void Model::show()
{
    cout << endl;
}
