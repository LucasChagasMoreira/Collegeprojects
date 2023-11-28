#include "unit_Model.hpp"

void unit_Model_constructor()
{
    Model *model1 = new Model_Impl();
    assert(model1->getName() == "NULL");
    assert(model1->getFlowSize() == 0);
    assert(model1->getSystemSize() == 0);

    Model *model2 = new Model_Impl("test");
    assert(model2->getName() == "test");

    delete (Model_Impl*) model1;
    delete (Model_Impl*) model2;
}

void unit_Model_destructor(){};

void unit_Model_getName()
{
    Model *model1 = new Model_Impl();
    assert(model1->getName() == "NULL");

    delete (Model_Impl*) model1;
}

void unit_Model_setName()
{
    Model *model1 = new Model_Impl();
    model1->setName("test");
    assert(model1->getName() == "test");

    delete (Model_Impl*) model1;
}

void unit_Model_add()
{
    Model *model1 = new Model_Impl();
    System *system1 = new System_Impl("system1");
    System *system2 = new System_Impl("system2");
    Flow *flowExp1 = new Exponential_Flow("flowExp", system1, system2);

    model1->add(system1);
    model1->add(system2);

    assert(model1->getSystemSize() == 2);

    for (auto it = model1->getSystemBegin(); it != model1->getSystemEnd(); it++)
    {
        if ((*it)->getName() == system1->getName())
            assert((*it)->getName() == system1->getName());
    }

    model1->add(flowExp1);

    assert(model1->getFlowSize() == 1);

    for (auto it = model1->getFlowBegin(); it != model1->getFlowEnd(); it++)
    {
        if ((*it)->getName() == flowExp1->getName())
            assert((*it)->getName() == flowExp1->getName());
    }

    model1->clear();

    delete (Model_Impl*) model1;
    delete (System_Impl*) system1;
    delete (System_Impl*) system2;
    delete (Exponential_Flow*) flowExp1;
}

void unit_Model_remove()
{
    Model *model1 = new Model_Impl();
    System *system1 = new System_Impl("system1");

    model1->add(system1);

    assert(model1->getSystemSize() == 1);

    for (auto it = model1->getSystemBegin(); it != model1->getSystemEnd(); it++)
    {
        if ((*it)->getName() == system1->getName())
            assert((*it)->getName() == system1->getName());
    }

    model1->remove(system1);

    assert(model1->getSystemSize() == 0);

    model1->clear();

    delete (Model_Impl*) model1;
    delete (System_Impl*) system1;
}

void unit_Model_clear()
{
    Model *model1 = new Model_Impl();
    System *system1 = new System_Impl("system1");
    System *system2 = new System_Impl("system2");
    Flow *flowExp1 = new Exponential_Flow("flowExp", system1, system2);

    model1->add(system1);
    model1->add(system2);
    assert(model1->getSystemSize() == 2);

    model1->add(flowExp1);
    assert(model1->getFlowSize() == 1);

    model1->clear();

    assert(model1->getSystemSize() == 0);
    assert(model1->getFlowSize() == 0);

    delete (Model_Impl*) model1;
    delete (System_Impl*) system1;
    delete (System_Impl*) system2;
    delete (Exponential_Flow*) flowExp1;
}

void unit_Model_run()
{
    Model *model = new Model_Impl("test");

    assert(model->run(5,10));
    assert(model->run(3,100));
    assert(model->run(0,90));
    assert(model->run(-1,10));
}

void run_unit_test_Model()
{
    unit_Model_constructor();
    unit_Model_destructor();
    unit_Model_getName();
    unit_Model_setName();
    unit_Model_add();
    unit_Model_remove();
    unit_Model_clear();
    unit_Model_run();
}