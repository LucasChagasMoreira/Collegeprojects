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
class Complex : public Flow_Impl
{
public:
    /**
     * @brief Construtor da classe Complex.
     * @param name Nome do fluxo.
     * @param source Sistema de origem.
     * @param Destiny Sistema de destino.
     */
    Complex(string name, System *source, System *Destiny) : Flow_Impl(name, source, Destiny) {}

    /**
     * @brief Função para executar o fluxo complexo.
     * @return Valor resultante do cálculo do fluxo.
     */
    double execute()
    {
        return 0.01 * getOrigin()->getValue();
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
