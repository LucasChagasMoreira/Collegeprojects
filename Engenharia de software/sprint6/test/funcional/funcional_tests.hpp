#ifndef FUNCIONAL_TESTS_HPP
#define FUNCIONAL_TESTS_HPP

/**
 * @file funcional_tests.hpp
 * @brief Contém declarações dos testes funcionais.
 */

#include "../../src/Model.hpp"
#include "../flows/Exponential_Flow.hpp"
#include "../flows/Logistic_Flow.hpp"

#include <assert.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <cstring>

/**
 * @class Complex
 * @brief Representa um fluxo complexo.
 */
class Complex : public Flow_Impl{
public:
    /**
     * @brief Default constructor
    */
    Complex() : Flow_Impl(){}

    /**
     * @brief Complex flow constructor that receives pointers to the source and target systems
     * @param source pointer to the source system of the flow
     * @param target pointer to the target system of the flow
    */
    Complex(System* source, System* target) : Flow_Impl("",source, target){}

    /**
     * @brief Copy Constructor
    */
    Complex(Flow& f) : Flow_Impl(f){}

    /**
     * @brief Executes the complex equation that must be performed by the flow
     * @return double containing the result of the equation
    */
    double execute(){
        return origin->getValue() * 0.01;
    }
};

/**
 * @brief Função de teste para o fluxo exponencial.
 */
void exponentialFuncionalTest();

/**
 * @brief Função de teste para o fluxo logístico.
 */
void logisticalFuncionalTest();

/**
 * @brief Função de teste para um caso complexo.
 */
void complexFuncionalTest();

#endif

