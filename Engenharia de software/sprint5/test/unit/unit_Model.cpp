#include "unit_Model.hpp"
void unit_Model_getModelsize(){
    Model *m1 = Model::createModel("1");
    assert(Model::getModelsize() == 1);
    delete m1;
}

void unit_Model_createModel()
{
    assert(Model::getModelsize() == 0);
    Model *m1 = Model::createModel("1");
    assert(Model::getModelsize() == 1);
    Model *m2 = Model::createModel("2");
    assert(Model::getModelsize() == 2);
    delete m2;
    assert(Model::getModelsize() == 1);
    delete m1;
    assert(Model::getModelsize() == 0);
}
void unit_Model_setDestiny_setOrigin(){
    Model *model = Model::createModel("test");
    System *system1 = model->createSystem("pop1", 100.0);
    System *system2 = model->createSystem("pop2", 0.0);
    Flow *f = model->createFlow<Exponential_Flow>("Exponencial", system1, system2);

    model->setDestiny(f,system2);
    model->setSource(f,system1);

    assert(f->getOrigin() == system1);
    assert(f->getTarget() == system2);

    delete model;
}
void unit_Model_createSystem()
{
    Model *creator = Model::createModel("creator");
    assert(creator->getSystemSize() == 0);
    System *m1 = creator->createSystem("1",0);
    assert(creator->getSystemSize() == 1);
    System *m2 = creator->createSystem("2",0);
    assert(creator->getSystemSize() == 2);
    creator->remove(m2);
    assert(creator->getSystemSize() == 1);
    creator->remove(m1);
    assert(creator->getSystemSize() == 0);
    delete creator;
}

void unit_Model_remove(){
    Model *creator = Model::createModel("creator");
    System *m2 = creator->createSystem("2",0);
    assert(creator->getSystemSize() == 0);
    creator->remove(m2);
    assert(creator->getSystemSize() == 1);
    delete creator;
}
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

void unit_Model_destructor(){
    Model *m1 = Model::createModel("1");
    assert(Model::getModelsize() == 1);
    delete m1;
    assert(Model::getModelsize() == 0);
}

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




void unit_Model_clear()
{
    Model *model1 = Model::createModel("m1");
    System *system1 = model1->createSystem("system1",0);
    System *system2 = model1->createSystem("systemZ",0);
    model1->createFlow<Exponential_Flow>("Exponencial", system1, system2);

    assert(model1->getSystemSize() == 2);

    assert(model1->getFlowSize() == 1);

    model1->clear();

    assert(model1->getSystemSize() == 0);
    assert(model1->getFlowSize() == 0);

    delete model1;
}

void unit_Model_run()
{
    Model *model = new Model_Impl("test");

    assert(model->run(5,10));
    assert(model->run(3,100));
    assert(model->run(0,90));
    assert(model->run(-1,10));

    delete model;
}

void run_unit_test_Model()
{
    unit_Model_createSystem();
    unit_Model_setDestiny_setOrigin();
    unit_Model_createModel();
    unit_Model_getModelsize();
    unit_Model_constructor();
    unit_Model_destructor();
    unit_Model_getName();
    unit_Model_setName();
    unit_Model_clear();
    unit_Model_run();
}