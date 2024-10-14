#include <iostream>
#include <cmath>
// #include "../iqmath/IQmathLib.h"
// #include "../iqmath/iqt.hpp"
#include "../iqmath/iqt2.hpp"
#include "patterns/decorate.hpp"
#include "patterns/strategy.hpp"
#include "patterns/actions.hpp"
#include "patterns/prototype.hpp"
#include "patterns/builder.hpp"
#include "patterns/adaptor.hpp"
#include "patterns/memento.hpp"

#include "coroutines/coro.hpp"
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


#define DEBUGGER std::cout

#define DEBUG_PRINTLN(...) println(__VA_ARGS__)


using OutputStream = std::ostream;

template<typename T>
requires (std::is_arithmetic_v<T>)
__inline OutputStream & operator<<(OutputStream & out, T && val) {
    return out << float(val);
}

__inline OutputStream & operator<<(OutputStream & out, const _iq val) {
    return out << int32_t(val);
}

void print_entity(auto && any){
    if constexpr(std::is_arithmetic_v<decltype(any)>){
        DEBUGGER << float(any);
    }else{
        DEBUGGER << any;
    }
}

template <class... Args>
void println(Args&&... args){
    (..., print_entity(args));
    DEBUGGER << "\r\n";
}


#define DEBUG_VALUE(x) DEBUG_PRINTLN(#x, "\t\t\t\t\t:", float(x));

template<int Q>
void print_q(const iq2_t<Q> & qv){
    DEBUG_PRINTLN(Q);
}
// 示例使用
void iq_tb() {
    // LambdaPool pool;
    // pool.addLambda([](int a, double b) { std::cout << "Called with int and double: " << a << ", " << b << std::endl; });
    // pool.addLambda([](std::string s) { std::cout << "Called with string: " << s << std::endl; });

    // pool.executeAll(10, 20.5); // 调用第一个Lambda
    // pool.executeAll("hello"); // 调用第二个Lambda

    // DEBUG_VALUE(cos(iq_t(1)));
    // DEBUG_VALUE(iq_t(1).value);
    // DEBUG_VALUE(iq_t(2).value);
    // DEBUG_VALUE((iq_t(2) * iq_t(1)).value);
    // DEBUG_VALUE(((_IQ(1) * _IQ(2)) >> GLOBAL_Q));
    // DEBUG_VALUE(sqrt(iq_t(2)));
    // DEBUG_VALUE(sqrt(iq_t(1.2)));
    // DEBUG_VALUE(log(iq_t(2)));
    // DEBUG_VALUE(atan(iq_t(2)));
    // DEBUG_VALUE(atan(iq_t(1)));
    // DEBUG_VALUE(atan(iq_t(1.01)));
    // DEBUG_VALUE(atan(iq_t(1.99)));
    // DEBUG_VALUE(tan(iq_t(M_PI/2 - 0.01)));
    // DEBUG_VALUE(atan(iq_t(0)));
    // DEBUG_VALUE(atan(iq_t(0.01)));
    // DEBUG_VALUE(atan(iq_t(0.5)));
    // DEBUG_VALUE(atan(iq_t(2)));

    // DEBUG_VALUE(_IQatan2(_IQ(1), _IQ(2)) * (1.0 / (1 << GLOBAL_Q)));
    // DEBUG_VALUE(acos(iq_t(0.2)));
    // DEBUG_VALUE(fmod(iq_t(0.2), iq_t(0.12)));
    // DEBUG_VALUE(lerp(iq_t(0.2), iq_t(0), iq_t(1)));

    
    // DEBUG_VALUE(pow(iq_t(1.5), iq_t(2)))
    // DEBUG_VALUE(iq_t(2) * log(iq_t(1.5)))
    // DEBUG_VALUE(iq_t(1) * iq_t(2))
    // DEBUG_VALUE(iq_t(1.5) * 2)
    // DEBUG_VALUE(exp(iq_t(2)));
    // DEBUG_VALUE(log(iq_t(1.5)));
    // DEBUG_VALUE(_IQlog(_IQ(1.5)));
    // DEBUG_VALUE(iq_t(1.5).value);
    // DEBUG_VALUE(iq_t(2).value);
    // DEBUG_VALUE(log(iq_t(2)));
    
    // #define DEBUG_IQ_BASICS

    // #ifdef DEBUG_IQ_BASICS
    // DEBUG_VALUE((iq_t(M_PI)));
    // DEBUG_VALUE((iq_t(M_PI)/iq_t(2)));
    // DEBUG_VALUE((iq_t(M_PI)/2));
    // DEBUG_VALUE((iq_t(M_PI)*iq_t(2)));
    // DEBUG_VALUE((iq_t(M_PI)*2));
    // DEBUG_VALUE(sqrt(iq_t(3))/2);
    // DEBUG_VALUE(sqrt(3)/2);
    // DEBUG_VALUE(fmod(iq_t(0.3), iq_t(0.2)));

    // #endif

    // #define DEBUG_IQ_SINCOS
    // #ifdef DEBUG_IQ_SINCOS
    // DEBUG_VALUE(sin(iq_t(M_PI/3)));
    // DEBUG_VALUE(cos(iq_t(M_PI/3)));
    
    // DEBUG_VALUE(acos(iq_t(sqrt(iq_t(3))/2)) / M_PI);
    // DEBUG_VALUE(acos(iq_t(sqrt(iq_t(2))/2)) / M_PI);
    // #endif
    
    // // #define DEBUG_IQ_TAN
    // #ifdef DEBUG_IQ_TAN
    // DEBUG_VALUE(atan(iq_t(sqrt(iq_t(3)))) / M_PI);
    // #endif

    // #define DEBUG_IQ_LOG
    // //FIXME
    // #ifdef DEBUG_IQ_LOG
    // DEBUG_VALUE(log(iq_t(1)));
    // DEBUG_VALUE(log(iq_t(1.29)));
    // DEBUG_VALUE(log(iq_t(1.49)));
    // DEBUG_VALUE(log(iq_t(1.51)));
    // DEBUG_VALUE(log(iq_t(2)));
    // DEBUG_VALUE(log(iq_t(6)));

    // #endif
    
    // #define DEBUG_IQ_EXP
    // #ifdef DEBUG_IQ_EXP
    // DEBUG_VALUE(exp(iq_t(1)));
    // DEBUG_VALUE(exp(iq_t(1.5)));
    // DEBUG_VALUE(exp(iq_t(2)));
    // DEBUG_VALUE(exp(iq_t(6)));

    // #endif

    // DEBUG_VALUE(atan2(iq_t(1), iq_t(2)));
    // DEBUG_VALUE(sqrt(iq_t(2)));

    #define DEBUG_IQ_BASICS

    // auto a = std::is_arithmetic_v<iq2_t<16>>;
    // DEBUG_VALUE(a);
    #ifdef DEBUG_IQ_BASICS

    // auto a = (iq2_t<16>(M_PI));
    // if constexpr(std::is_arithmetic_v<decltype(a)>){
        // DEBUGGER << a;
    // }else{
    //     // DEBUGGER << a;
    // }

    auto a = iq2_t<16>(2.5);
    // a -= iq2_t<16>(2/4);
    auto b = iq2_t<15>(12.5);
    // a -= iq2_t<16>(b);
    DEBUG_VALUE(a);
    DEBUG_VALUE(b);
    DEBUG_VALUE(a + b);
    DEBUG_VALUE(a - b);
    DEBUG_VALUE(a * b);
    DEBUG_VALUE(int(a));
    DEBUG_VALUE(uint8_t(a));
    DEBUG_VALUE(a == b - iq2_t<16>(10));
    
    // print_q(b);

    DEBUG_VALUE((iq2_t<16>(M_PI)/iq2_t<16>(2)));
    DEBUG_VALUE((iq2_t<16>(M_PI)/2));
    DEBUG_VALUE((iq2_t<16>(M_PI)*iq2_t<16>(2)));
    DEBUG_VALUE((iq2_t<16>(M_PI)*2));
    // DEBUG_VALUE(sqrt(iq2_t<16>(3))/2);
    // DEBUG_VALUE(sqrt(3)/2);
    // DEBUG_VALUE(fmod(iq2_t<16>(0.3), iq2_t<16>(0.2)));

    #endif
}

int main(){
    // decorate_tb();
    // strategy_tb();
    // actions_tb();
    // prototype_tb();
    // builder_tb();
    // adaptor_tb();
    coro_tb();
}