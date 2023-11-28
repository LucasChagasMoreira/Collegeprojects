#ifndef UNITMODEL_HPP
    #define UNITMODEL_HPP

    #include <iostream>
    #include <cmath>
    #include <cstring>
    #include <assert.h>

    #include "../funcional/Exponential_Flow.hpp"
    #include "../funcional/Logistic_Flow.hpp"
    #include "../../src/Model_Impl.hpp"
    #include "../../src/System_Impl.hpp"

    /// @brief This function run the unit test of the model
    void run_unit_test_Model();

    /// @brief This function does the unit test of the Constructor
    void unit_Model_constructor();

    /// @brief This function does the unit test of the destructor
    void unit_Model_destructor();

    /// @brief This function does the unit test of the Getname
    void unit_Model_getName();

    /// @brief This function does the unit test of the Setname
    void unit_Model_setName();

    /// @brief This function does the unit test of the add
    void unit_Model_add();

    /// @brief This function does the unit test of the remove
    void unit_Model_remove();

    /// @brief This function does the unit test of the clear
    void unit_Model_clear();

    /// @brief This function does the unit test of the run
    void unit_Model_run();
#endif