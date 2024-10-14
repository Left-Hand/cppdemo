#pragma once

#include <iostream>
#include <string>

#include <memory>
#include <vector>
#include <algorithm>

// 策略接口
class TextStrategy {
public:
    virtual std::string process(const std::string& text) const = 0;

    TextStrategy(){
        addrs.push_back((uint64_t)this);
        std::cout << std::hex << "new\t\t\t" << (uint64_t)this << std::endl;
    }

    ~TextStrategy(){
        auto idx = std::find(addrs.begin(), addrs.end(), (uint64_t)this);
        if(idx != addrs.end()) addrs.erase(idx);
        else {
            std::cerr << "error: not found" << std::endl;
        }
        std::cout << std::hex << "drop\t\t\t" << (uint64_t)this << std::endl;
    }

    
    inline static std::vector<uint64_t> addrs = {};
};

// 具体的策略类 - 大写转换
class UppercaseStrategy : public TextStrategy {
public:
    std::string process(const std::string& text) const override {
        std::string result;
        for (char c : text) {
            result += std::toupper(c);
        }
        return result;
    }
};

// 具体的策略类 - 小写转换
class LowercaseStrategy : public TextStrategy {
public:
    std::string process(const std::string& text) const override {
        std::string result;
        for (char c : text) {
            result += std::tolower(c);
        }
        return result;
    }
};

// 具体的策略类 - 反转字符串
class ReverseStrategy : public TextStrategy {
public:
    std::string process(const std::string& text) const override {
        return std::string(text.rbegin(), text.rend());
    }
};

// 上下文类
class TextProcessor {
private:
    std::shared_ptr<TextStrategy> _strategy = nullptr;

public:
    // TextProcessor(std::shared_ptr<TextProcessor> strategy) : _strategy(strategy) {}

    template<typename T>
    requires std::is_base_of_v<TextStrategy, T>
    void set_strategy(std::shared_ptr<T> strategy) {
        // _strategy = std::static_pointer_cast<TextStrategy>(strategy);
        _strategy = strategy;
    }

    template<typename T>
    requires std::is_base_of_v<TextStrategy, T>
    void set_strategy(T && strategy) {
        _strategy = std::make_shared<T>(std::forward<T>(strategy));
    }

    template<typename T>
    requires std::is_base_of_v<TextStrategy, T>
    void set_strategy(const T & strategy) {
        _strategy = std::make_shared<T>(strategy);
    }

    template<typename T, typename... Args>
    void set_strategy(Args&&... args) {
        _strategy = std::make_shared<T>(std::forward<Args>(args)...);
    }

    std::string process(const std::string& text) const {
        if (_strategy == nullptr) {
            throw std::runtime_error("No strategy set.");
        }
        return _strategy->process(text);
    }
};

void strategy_tb() {
    // 创建具体的策略实例
    // UppercaseStrategy uppercase;
    // LowercaseStrategy lowercase;
    // ReverseStrategy reverse;

    // 创建上下文实例
    TextProcessor processor;

    // 使用不同的策略处理文本
    std::string input = "Hello, World!";
    // std::cout << "Original: " << input << std::endl;

    processor.set_strategy(std::move(UppercaseStrategy()));
    // processor.set_strategy(uppercase);
    // processor.set_strategy<UppercaseStrategy>();

    // processor.set_strategy(std::make_shared<LowercaseStrategy>());
    // std::cout << "Uppercase: " << processor.process(input) << std::endl;
    // std::cout << "Lowercase: " << processor.process(input) << std::endl;

    // processor.set_strategy(&reverse);
    // std::cout << "Reverse: " << processor.process(input) << std::endl;
    std::cout << std::dec << TextStrategy::addrs.size() << std::endl;
    for(const auto & item : TextStrategy::addrs){
        std::cout << std::hex << item << std::endl;
    }
}