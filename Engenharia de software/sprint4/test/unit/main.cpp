#include "unit_Model.hpp"
#include "unit_Flow.hpp"
#include "unit_System.hpp"


int main()
{
    cout << "Running unit tests..." << endl;

    cout << "System tests: ";
    run_unit_test_System();
    cout << "OK" << endl;

    cout << "Flow tests: ";
    run_unit_test_Flow();
    cout << "OK" << endl;

    cout << "Model tests: ";
    run_unit_test_Model();
    cout << "OK" << endl;

    cout << "All unit tests succeed." << endl;
    
    return 0;
}