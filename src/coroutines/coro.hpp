// main.cpp
#include <iostream>
#include "coro_task.hpp"

Task hello(int max) {
    std::cout << "hello world\n";
    for (int i = 0; i < max; ++i) {
        std::cout << "hello " << i << "\n";
        co_await std::suspend_always{};
    }

    std::cout << "hello end\n";
}

void coro_tb() {
    auto co = hello(3);
    while (co.resume()) {
        std::cout << "hello coroutine suspend\n";
    }
}
