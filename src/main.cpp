#include <iostream>

// #include "../iqmath/IQmathLib.h"
#include "../iqmath/iqt.hpp"

void test_f(floating auto x){
    std::cout << "float: " << x << std::endl;
}

int main() {
    iq_t a = 1.0;
    iq_t b = 1.0;
    // std::cout << a + sin(b) << std::endl;
    std::cout << a + b << std::endl;
    return 0;
}
