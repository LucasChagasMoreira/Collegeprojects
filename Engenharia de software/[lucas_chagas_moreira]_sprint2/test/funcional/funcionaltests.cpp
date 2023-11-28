#include "funcionaltests.hpp"

void exponentialFuncionalTest()
{
    Model *model = new Model();
    System *system1 = new System("pop1", 100.0);
    System *system2 = new System("pop2", 0.0);
    Flow *flow = new Expo_Flow("Exponencial", system1, system2);

    model->setName("Sistema exponencial");
    model->add(system1);
    model->add(system2);
    model->add(flow);

    model->run(0, 99);

    assert(fabs(system1->getValue() - 36.6032) < 0.0001);
    assert(fabs(system2->getValue() - 63.3968) < 0.0001);

    model->clear();

    delete model;
    delete system1;
    delete system2;
    delete flow;
}

void logisticalFuncionalTest()
{
    Model *model = new Model();
    System *system1 = new System("p1", 100.0);
    System *system2 = new System("p2", 10.0);
    Flow *flow = new LogisFlow("Logistic", system1, system2);

    model->setName("Sistema logistic");

    model->add(system1);
    model->add(system2);
    model->add(flow);

    model->run(0, 99);

    assert(fabs(system1->getValue() - 88.2167) < 0.0001);
    assert(fabs(system2->getValue() - 21.7833) < 0.0001);

    model->clear();

    delete model;
    delete system1;
    delete system2;
    delete flow;
}

void complexFuncionalTest()
{
    Model *model = new Model();
    System *q1 = new System("q1", 100.0);
    System *q2 = new System("q2", 0.0);
    System *q3 = new System("q3", 100.0);
    System *q4 = new System("q4", 0.0);
    System *q5 = new System("q5", 0.0);
    Flow *f = new Expo_Flow("f", q1, q2);
    Flow *t = new Expo_Flow("f", q2, q3);
    Flow *u = new Expo_Flow("f", q3, q4);
    Flow *v = new Expo_Flow("f", q4, q1);
    Flow *g = new Expo_Flow("f", q1, q3);
    Flow *r = new Expo_Flow("f", q2, q5);

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

    delete model;
    delete q1;
    delete q2;
    delete q3;
    delete q4;
    delete q5;
    delete f;
    delete t;
    delete u;
    delete v;
    delete g;
    delete r;
}