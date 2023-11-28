#include "funcional_tests.hpp"

void exponentialFuncionalTest()
{
    Model *model = new Model_Impl();
    System *system1 = new System_Impl("pop1", 100.0);
    System *system2 = new System_Impl("pop2", 0.0);
    Flow *flow = new Exponential_Flow("Exponencial", system1, system2);

    model->setName("Sistema exponencial");
    model->add(system1);
    model->add(system2);
    model->add(flow);

    model->run(0, 99);

    assert(fabs(system1->getValue() - 36.6032) < 0.0001);
    assert(fabs(system2->getValue() - 63.3968) < 0.0001);

    model->clear();

    delete (Model_Impl*) model;
    delete (System_Impl*) system1;
    delete (System_Impl*) system2;
    delete (Exponential_Flow*) flow;
}

void logisticalFuncionalTest()
{
    Model *model = new Model_Impl();
    System *system1 = new System_Impl("p1", 100.0);
    System *system2 = new System_Impl("p2", 10.0);
    Flow *flow = new Logistic_Flow("Logistic", system1, system2);

    model->setName("Sistema logistic");

    model->add(system1);
    model->add(system2);
    model->add(flow);

    model->run(0, 99);

    assert(fabs(system1->getValue() - 88.2167) < 0.0001);
    assert(fabs(system2->getValue() - 21.7833) < 0.0001);

    model->clear();

    delete (Model_Impl*) model;
    delete (System_Impl*) system1;
    delete (System_Impl*) system2;
    delete (Logistic_Flow*) flow;
}

void complexFuncionalTest()
{
    Model *model = new Model_Impl();
    System *q1 = new System_Impl("q1", 100.0);
    System *q2 = new System_Impl("q2", 0.0);
    System *q3 = new System_Impl("q3", 100.0);
    System *q4 = new System_Impl("q4", 0.0);
    System *q5 = new System_Impl("q5", 0.0);
    Flow *f = new Exponential_Flow("f", q1, q2);
    Flow *t = new Exponential_Flow("f", q2, q3);
    Flow *u = new Exponential_Flow("f", q3, q4);
    Flow *v = new Exponential_Flow("f", q4, q1);
    Flow *g = new Exponential_Flow("f", q1, q3);
    Flow *r = new Exponential_Flow("f", q2, q5);

    model->setName("Sistema completo");

    model->add(q1);
    model->add(q2);
    model->add(q3);
    model->add(q4);
    model->add(q5);
    model->add(f);
    model->add(t);
    model->add(u);
    model->add(v);
    model->add(g);
    model->add(r);

    model->run(0, 99);

    assert(fabs(q1->getValue() - 31.8513) < 0.0001);
    assert(fabs(q2->getValue() - 18.4003) < 0.0001);
    assert(fabs(q3->getValue() - 77.1143) < 0.0001);
    assert(fabs(q4->getValue() - 56.1728) < 0.0001);
    assert(fabs(q5->getValue() - 16.4612) < 0.0001);

    model->clear();

    delete (Model_Impl*) model;
    delete (System_Impl*) q1;
    delete (System_Impl*) q2;
    delete (System_Impl*) q3;
    delete (System_Impl*) q4;
    delete (System_Impl*) q5;
    delete (Exponential_Flow*) f;
    delete (Exponential_Flow*) t;
    delete (Exponential_Flow*) u;
    delete (Exponential_Flow*) v;
    delete (Exponential_Flow*) g;
    delete (Exponential_Flow*) r;
}