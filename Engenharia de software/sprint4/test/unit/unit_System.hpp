#ifndef UNITSYSTEM_HPP
    #define UNITSYSTEM_HPP

    #include <iostream>
    #include <cmath>
    #include <cstring>
    #include <assert.h>
    
    #include "../../src/System_Impl.hpp"
    #include "../../src/System.hpp"

    /// @brief This function run the unit test of the system
    void run_unit_test_System();

    /// @brief This function does the unit test of the Constructor
    void unit_System_constructor();

    /// @brief This function does the unit test of the destructor
    void unit_System_destructor();

    /// @brief This function does the unit test of the get Value
    void unit_System_getValue();

    /// @brief This function does the unit test of the set Value
    void unit_System_setValue();

    /// @brief This function does the unit test of the get Name
    void unit_System_getName();

    /// @brief This function does the unit test of the set Name
    void unit_System_setName();
#endif