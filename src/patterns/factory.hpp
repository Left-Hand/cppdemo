#pragma once

#include <iostream>

// �����Ʒ
class Product {
public:
    virtual void display() const = 0;
};

// �����ƷA
class ConcreteProductA : public Product {
public:
    void display() const override {
        std::cout << "ConcreteProductA" << std::endl;
    }
};

// �����ƷB
class ConcreteProductB : public Product {
public:
    void display() const override {
        std::cout << "ConcreteProductB" << std::endl;
    }
};

// ���󹤳�
class Factory {
public:
    virtual Product* createProduct() = 0;
};

// ���幤��A
class ConcreteFactoryA : public Factory {
public:
    Product* createProduct() override {
        return new ConcreteProductA();
    }
};

// ���幤��B
class ConcreteFactoryB : public Factory {
public:
    Product* createProduct() override {
        return new ConcreteProductB();
    }
};

void clientCode(Factory& factory) {
    Product* product = factory.createProduct();
    product->display();
    delete product; // ȷ���ͷ��ڴ�
}

int main() {
    ConcreteFactoryA factoryA;
    clientCode(factoryA);

    ConcreteFactoryB factoryB;
    clientCode(factoryB);

    return 0;
}