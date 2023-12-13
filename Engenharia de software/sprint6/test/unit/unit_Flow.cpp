#include "unit_Flow.hpp"

void unit_Flow_constructor()
{
    System *system1 = new SystemHandle();
    System *system2 = new SystemHandle();

    // exponential
    Flow *flowExp1 = new FlowHandle<Exponential_Flow>();
    assert(flowExp1->getName() == "");
    assert(flowExp1->getOrigin() == NULL);
    assert(flowExp1->getTarget() == NULL);

    Flow *flowExp2 = new FlowHandle<Exponential_Flow>("test", system1, system2);
    assert(flowExp2->getName() == "test");
    assert(flowExp2->getOrigin() == system1);
    assert(flowExp2->getTarget() == system2);

    Flow *flowExp3 = new FlowHandle<Exponential_Flow>(*flowExp2);

    // logistic
    Flow *flowLogist1 = new FlowHandle<Logistic_Flow>();
    assert(flowLogist1->getName() == "");
    assert(flowLogist1->getOrigin() == NULL);
    assert(flowLogist1->getTarget() == NULL);

    Flow *flowLogist2 = new FlowHandle<Logistic_Flow>("test", system1, system2);
    assert(flowLogist2->getName() == "test");
    assert(flowLogist2->getOrigin() == system1);
    assert(flowLogist2->getTarget() == system2);

    Flow *flowLogist3 = new FlowHandle<Logistic_Flow>(*flowLogist2);

    delete system1;
    delete system2;
    delete flowExp1;
    delete flowExp2;
    delete flowExp3;
    delete flowLogist1;
    delete flowLogist2;
    delete flowLogist3;
}

void unit_Flow_destructor(){}

void unit_Flow_getName()
{
    System *system1 = new SystemHandle();
    System *system2 = new SystemHandle();

    // exponential
    Flow *flowExp1 = new FlowHandle<Exponential_Flow>("test", system1, system2);
    assert(flowExp1->getName() == "test");

    // logistic
    Flow *flowLogist1 = new FlowHandle<Logistic_Flow>("test", system1, system2);
    assert(flowLogist1->getName() == "test");

    delete system1;
    delete system2;
    delete flowExp1;
    delete flowLogist1;
}

void unit_Flow_setName()
{
    // exponential
    Flow *flowExp1 = new FlowHandle<Exponential_Flow>();
    flowExp1->setName("test");
    assert(flowExp1->getName() == "test");

    // logistic
    Flow *flowLogist1 = new FlowHandle<Logistic_Flow>();
    flowLogist1->setName("test");
    assert(flowLogist1->getName() == "test");

    delete (Exponential_Flow*) flowExp1;
    delete (Logistic_Flow*) flowLogist1;
}

void unit_Flow_getOrigin()
{
    System *system1 = new SystemHandle();
    System *system2 = new SystemHandle();

    // exponential
    Flow *flowExp1 = new FlowHandle<Exponential_Flow>("test", system1, system2);
    assert(flowExp1->getOrigin() == system1);

    // logistic
    Flow *flowLogist1 = new FlowHandle<Logistic_Flow>("test", system1, system2);
    assert(flowLogist1->getOrigin() == system1);

    delete system1;
    delete system2;
    delete flowExp1;
    delete flowLogist1;
}

void unit_Flow_setOrigin()
{
    System *system1 = new SystemHandle();
    System *system2 = new SystemHandle();
    System *system3 = new SystemHandle();

    // exponential
    Flow *flowExp1 = new FlowHandle<Exponential_Flow>("teste", system1, system2);
    flowExp1->setOrigin(system3);
    assert(flowExp1->getOrigin() == system3);

    // logistic
    Flow *flowLogist1 = new FlowHandle<Logistic_Flow>("teste", system1, system2);
    flowLogist1->setOrigin(system3);
    assert(flowLogist1->getOrigin() == system3);

    delete system1;
    delete system2;
    delete flowExp1;
    delete flowLogist1;
}

void unit_Flow_getTarget()
{
    System *system1 = new SystemHandle();
    System *system2 = new SystemHandle();

    // exponential
    Flow *flowExp1 = new FlowHandle<Exponential_Flow>("teste", system1, system2);
    assert(flowExp1->getTarget() == system2);

    // logistic
    Flow *flowLogist1 = new FlowHandle<Logistic_Flow>("teste", system1, system2);
    assert(flowLogist1->getTarget() == system2);

    delete system1;
    delete system2;
    delete flowExp1;
    delete flowLogist1;
}

void unit_Flow_setTarget()
{
    System *system1 = new SystemHandle();
    System *system2 = new SystemHandle();
    System *system3 = new SystemHandle();

    // exponential
    Flow *flowExp1 = new FlowHandle<Exponential_Flow>("test", system1, system2);
    flowExp1->setTarget(system3);
    assert(flowExp1->getTarget() == system3);

    // logistic
    Flow *flowLogist1 = new FlowHandle<Logistic_Flow>("test", system1, system2);
    flowLogist1->setTarget(system3);
    assert(flowLogist1->getTarget() == system3);

    delete system1;
    delete system2;
    delete flowExp1;
    delete flowLogist1;
}

void run_unit_test_Flow()
{
    unit_Flow_constructor();
    unit_Flow_destructor();
    unit_Flow_getName();
    unit_Flow_setName();
    unit_Flow_getOrigin();
    unit_Flow_setOrigin();
    unit_Flow_getTarget();
    unit_Flow_setTarget();
}