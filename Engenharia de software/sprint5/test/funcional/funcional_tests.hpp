#ifndef FUNCIONAL_TESTS_HPP
    #define FUNCIONAL_TESTS_HPP
    /// @brief all functional tests
    #include "../../src/System_Impl.hpp"
    #include "../../src/Model_Impl.hpp"
    #include "../flows/Exponential_Flow.hpp"
    #include "../flows/Logistic_Flow.hpp"
    

    #include <assert.h>
    #include <cmath>
    #include <iostream>
    #include <cstdlib>
    #include <cstring>
    
    class Complex : public Flow_Impl
    {
        public:
            Complex(string name, System *source, System *Destiny) : Flow_Impl(name, source, Destiny) {}

            double execute()
            {
                return 0.01 * getOrigin()->getValue();
            }
    };

    void exponentialFuncionalTest();
    void logisticalFuncionalTest();
    void complexFuncionalTest();
#endif