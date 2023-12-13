#ifndef UNITMODEL_HPP
#define UNITMODEL_HPP

#include <iostream>
#include <cmath>
#include <cstring>
#include <assert.h>

#include "../../src/Model.hpp"
#include "../flows/Exponential_Flow.hpp"
#include "../flows/Logistic_Flow.hpp"
#include "../../src/Model_Impl.hpp"
#include "../../src/System_Impl.hpp"
#include "../flows/Exponential_Flow.hpp"
#include "../flows/Logistic_Flow.hpp"

/// @brief Function to get the model size
void unit_Model_getModelsize();

/// @brief Function to create a system for the model
void unit_Model_createSystem();

/// @brief Function to set the source of the model
void unit_Model_setSource();

/// @brief Function to set the target of the model
void unit_Model_setTarget();

/// @brief Function to create the model
void unit_Model_createModel();

/// @brief Function to run the unit test of the model
void run_unit_test_Model();

/// @brief Function to perform the unit test of the Constructor
void unit_Model_constructor();

/// @brief Function to perform the unit test of the destructor
void unit_Model_destructor();

/// @brief Function to perform the unit test of getting the name
void unit_Model_getName();

/// @brief Function to perform the unit test of setting the name
void unit_Model_setName();

/// @brief Function to perform the unit test of adding
void unit_Model_add();

/// @brief Function to perform the unit test of removing
void unit_Model_remove();

/// @brief Function to perform the unit test of clearing
void unit_Model_clear();

/// @brief Function to perform the unit test of running the model
void unit_Model_run();

#endif
