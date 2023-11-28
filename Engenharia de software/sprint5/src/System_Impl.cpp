#include "System_Impl.hpp"

System_Impl::System_Impl()
{
    name = "NULL";
    value = 0;
}

System_Impl::System_Impl(System &obj)
{
    if (&obj == this)
        return;

    name = obj.getName();
    value = obj.getValue();
};

System_Impl::System_Impl(const string name, double value) : name(name), value(value) {}
System_Impl::System_Impl(const string name) : name(name) {}
System_Impl::System_Impl(double value) : value(value) {}

string System_Impl::getName() const
{
    return name;
};

void System_Impl::setName(const string name)
{
    this->name = name;
}

double System_Impl::getValue() const
{
    return value;
}

void System_Impl::setValue(double value)
{
    this->value = value;
}

System& System_Impl::operator=(const System &obj)
{
    if (&obj == this)
        return *this;

    name = obj.getName();
    value = obj.getValue();

    return *this;
}

System_Impl::~System_Impl() {}