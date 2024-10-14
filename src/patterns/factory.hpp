#pragma once

#include <iostream>

// 抽象产品
class Product {
public:
    virtual void display() const = 0;
};

// 具体产品A
class ConcreteProductA : public Product {
public:
    void display() const override {
        std::cout << "ConcreteProductA" << std::endl;
    }
};

// 具体产品B
class ConcreteProductB : public Product {
public:
    void display() const override {
        std::cout << "ConcreteProductB" << std::endl;
    }
};

// 抽象工厂
class Factory {
public:
    virtual Product* createProduct() = 0;
};

// 具体工厂A
class ConcreteFactoryA : public Factory {
public:
    Product* createProduct() override {
        return new ConcreteProductA();
    }
};

// 具体工厂B
class ConcreteFactoryB : public Factory {
public:
    Product* createProduct() override {
        return new ConcreteProductB();
    }
};

void clientCode(Factory& factory) {
    Product* product = factory.createProduct();
    product->display();
    delete product; // 确保释放内存
}

int main() {
    ConcreteFactoryA factoryA;
    clientCode(factoryA);

    ConcreteFactoryB factoryB;
    clientCode(factoryB);

    return 0;
}