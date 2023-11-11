@page Summary and Examples
@tableofcontents

@section Summary

This project revolves around the theory of systems and comprises three main classes: "Model," "System," and "Flow." The "Model" class functions as a container for storing instances of both "System" and "Flow." Additionally, it oversees the execution of the entire process through the "run" method. The "Flow" class plays a crucial role in connecting 2 systems and is designed to receive mathematical functions. Lastly, the "System" class is responsible for storing and managing integer values exclusively. Overall, these classes work together to implement a system theory-based project, with each class serving a distinct purpose in the overall functionality of the system.


@section Examples

@subsection inherited_flow 1 - Create a subclass of Flow
Example:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
class Exponential_Flow : public Flow
{
    public:
        Exponential_Flow();
        Exponential_Flow(Flow &obj);
        Exponential_Flow(const string name, System *origin, System *target);
        virtual ~Exponential_Flow();

        virtual double execute();
};
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


@subsection flow_equation 2 - Implement the equation for the subclass
Example:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
double Exponential_Flow::execute()
{
    return getOrigin()->getValue() * 0.05;
};
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


@subsection program_example 3 - Use the API
Example:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
Model *model = new Model();
System *system1 = new System("s1", 50.0);
System *system2 = new System("s2", 0.0);
Flow *flow = new Exponential_Flow("Exponential", system1, system2);

model->setName("Exponential System");
model->add(system1);
model->add(system2);
model->add(flow);

model->run(1, 100);
model->clear();

delete model;
delete system1;
delete system2;
delete flow;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~