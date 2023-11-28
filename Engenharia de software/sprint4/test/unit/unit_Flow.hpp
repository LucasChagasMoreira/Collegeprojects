#ifndef UNITFLOW_HPP
    #define UNITFLOW_HPP

    #include <iostream>
    #include <cmath>
    #include <cstring>
    #include <assert.h>

    #include "../funcional/Exponential_Flow.hpp"
    #include "../funcional/Logistic_Flow.hpp"
    #include "../../src/System_Impl.hpp"
    #include "../../src/Model_Impl.hpp"

    /// @brief This function runs all unit tests for the Flow methods
    void run_unit_test_Flow();

    /// @brief This function does the unit test of the constructor
    void unit_Flow_constructor();

    /// @brief This function does the unit test of the destructor
    void unit_Flow_destructor();

    /// @brief This function does the unit test of the Getname
    void unit_Flow_getName();

    /// @brief This function does the unit test of the Setname
    void unit_Flow_setName();

    /// @brief This function does the unit test of the getorigin
    void unit_Flow_getOrigin();

    /// @brief This function does the unit test of the setorigin
    void unit_Flow_setOrigin();

    /// @brief This function does the unit test of the getTarget
    void unit_Flow_getTarget();

    /// @brief This function does the unit test of the setTarget
    void unit_Flow_setTarget();
#endif