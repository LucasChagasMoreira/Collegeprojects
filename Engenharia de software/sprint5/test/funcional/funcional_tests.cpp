#include "funcional_tests.hpp"

void exponentialFuncionalTest()
{
    Model *model = Model::createModel("test");
    System *system1 = model->createSystem("pop1", 100.0);
    System *system2 = model->createSystem("pop2", 0.0);
    model->createFlow<Exponential_Flow>("Exponencial", system1, system2);

    model->run(0, 100);

    assert(fabs(system1->getValue() - 36.6032) < 0.0001);
    assert(fabs(system2->getValue() - 63.3968) < 0.0001);

    delete model;
}

void logisticalFuncionalTest()
{
    Model *model = Model::createModel("Logistic");
    System *system1 = model->createSystem("p1", 100.0);
    System *system2 = model->createSystem("p2", 10.0);
    model->createFlow<Logistic_Flow>("Logistic", system1, system2);

    model->run(0, 100);

    assert(fabs(system1->getValue() - 88.2167) < 0.0001);
    assert(fabs(system2->getValue() - 21.7833) < 0.0001);

    delete model;
}

void complexFuncionalTest()
{
    Model *m = Model::createModel("Complex test");
    System *q1 = m->createSystem("Q1", 100);
    System *q2 = m->createSystem("Q2", 0);
    System *q3 = m->createSystem("Q3", 100);
    System *q4 = m->createSystem("Q4", 0);
    System *q5 = m->createSystem("Q5", 0);
    Flow *f_f = m->createFlow<Complex>("f", q1, q2);
    Flow *f_t = m->createFlow<Complex>("t", q2, q3);
    Flow *f_u = m->createFlow<Complex>("u", q3, q4);
    Flow *f_v = m->createFlow<Complex>("v", q4, q1);
    Flow *f_g = m->createFlow<Complex>("g", q1, q3);
    Flow *f_r = m->createFlow<Complex>("r", q2, q5);

    assert(q1->getName() == "Q1");
    assert(q2->getName() == "Q2");
    assert(q3->getName() == "Q3");
    assert(q4->getName() == "Q4");
    assert(q5->getName() == "Q5");
    assert(f_f->getName() == "f");
    assert(f_t->getName() == "t");
    assert(f_u->getName() == "u");
    assert(f_v->getName() == "v");
    assert(f_g->getName() == "g");
    assert(f_r->getName() == "r");
    assert(m->getName() == "Complex test");

    assert(fabs(q1->getValue() - 100.0) < 0.0001);
    assert(fabs(q2->getValue() - 0.0) < 0.0001);
    assert(fabs(q3->getValue() - 100.0) < 0.0001);
    assert(fabs(q4->getValue() - 0.0) < 0.0001);
    assert(fabs(q5->getValue() - 0.0) < 0.0001);

    m->run(0, 100);

    assert(fabs(q1->getValue() - 31.8513) < 0.0001);
    assert(fabs(q2->getValue() - 18.4003) < 0.0001);
    assert(fabs(q3->getValue() - 77.1143) < 0.0001);
    assert(fabs(q4->getValue() - 56.1728) < 0.0001);
    assert(fabs(q5->getValue() - 16.4612) < 0.0001);

    delete m;
}