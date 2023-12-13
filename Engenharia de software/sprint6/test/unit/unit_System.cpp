#include "unit_System.hpp"


void unit_System_constructor()
{
    System *system1 = new SystemHandle();
    assert(system1->getName() == ""); 
    assert(system1->getValue() == 0);

    System *system2 = new SystemHandle("test", 1);
    assert(system2->getName() == "test");
    assert(system2->getValue() == 1);

    System *system3 = new SystemHandle(*system2);
    assert(system3->getName() == "test");
    assert(system3->getValue() == 1);
    
    delete  system1;
    delete system2;
    delete system3;
}

void unit_System_destructor(){}

void unit_System_getValue(void)
{
    System *system1 = new SystemHandle(10);
    assert(system1->getValue() == 10);

    delete system1;
}

void unit_System_setValue(void)
{
    System *system1 = new SystemHandle();
    system1->setValue(10);
    assert(system1->getValue() == 10);

    delete  system1;
}

void unit_System_getName()
{
    System *system1 = new SystemHandle("test");
    assert(system1->getName() == "test");

    delete system1;
}

void unit_System_setName()
{
    System *system1 = new SystemHandle();
    system1->setName("test");
    assert(system1->getName() == "test");

    delete system1;
}

void run_unit_test_System()
{
    unit_System_constructor();
    unit_System_destructor();
    unit_System_getValue();
    unit_System_setValue();
    unit_System_getName();
    unit_System_setName();
}