#include <iostream>
#include "tests.hpp"

using namespace std;

int main()
{
    cout << "Running\n";

    test_atomic();
    test_is();
    test_uri();

    cout << "Successful\n";
    return 0;
}