#include "System_Impl.hpp"

System_Impl::System_Impl()
{
    name = "NULL";
    value = 0;
}

System_Impl::System_Impl(System &obj)
{
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


System_Impl::~System_Impl() {}