#include <iostream>

// #include "../iqmath/IQmathLib.h"
#include "../iqmath/iqt.hpp"

void test_f(floating auto x){
    std::cout << "float: " << x << std::endl;
}
#include <iostream>
#include <vector>
#include <functional>
#include <any>
#include <type_traits>

// 定义Lambda类型
template<typename... Args>
using LambdaType = std::function<void(Args...)>;

// 定义Lambda池
class LambdaPool {
public:
    // 添加Lambda到池中
    template<typename... Args, typename Callable>
    void addLambda(Callable&& lambda) {
        // lambdas_.emplace_back(std::bind(&LambdaPool::invokeLambda, this, std::forward<Callable>(lambda), std::placeholders::_1));
    }

    // 执行所有Lambda
    template<typename... Args>
    void executeAll(Args&&... args) {
        for (auto& lambda : lambdas_) {
            // lambda(std::forward<Args>(args)...);
        }
    }

private:
    std::vector<LambdaType<std::any>> lambdas_; // 存储Lambda的容器

    // 用于调用Lambda
    template<typename Callable, typename... Args>
    void invokeLambda(Callable&& lambda, Args&&... args) {
        lambda(std::forward<Args>(args)...);
    }
};

// 示例使用
int main() {
    // LambdaPool pool;
    // pool.addLambda([](int a, double b) { std::cout << "Called with int and double: " << a << ", " << b << std::endl; });
    // pool.addLambda([](std::string s) { std::cout << "Called with string: " << s << std::endl; });

    // pool.executeAll(10, 20.5); // 调用第一个Lambda
    // pool.executeAll("hello"); // 调用第二个Lambda

    iq_t a = sin(iq_t(1));
    std::cout << a << std::endl;
    return 0;
}