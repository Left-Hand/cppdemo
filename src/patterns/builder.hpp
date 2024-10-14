#pragma once


#include <iostream>
#include <string>

// 定义 Person 类
class Person {
public:
    std::string name;
    int age;
    std::string address;

    Person() : name(""), age(0), address("") {}

    void display() const {
        std::cout << "Name: " << name << ", Age: " << age << ", Address: " << address << std::endl;
    }
};

// 定义 PersonBuilder 接口
class PersonBuilder {
public:
    virtual ~PersonBuilder() {}
    virtual PersonBuilder& withName(const std::string& name) = 0;
    virtual PersonBuilder& withAge(int age) = 0;
    virtual PersonBuilder& withAddress(const std::string& address) = 0;
    virtual Person build() const = 0;
};

// 实现具体的 ConcretePersonBuilder 类
class ConcretePersonBuilder : public PersonBuilder {
private:
    Person person;

public:
    ConcretePersonBuilder& withName(const std::string& name) override {
        person.name = name;
        return *this;
    }

    ConcretePersonBuilder& withAge(int age) override {
        person.age = age;
        return *this;
    }

    ConcretePersonBuilder& withAddress(const std::string& address) override {
        person.address = address;
        return *this;
    }

    Person build() const override {
        return person;
    }
};

// Director 类来控制构建过程
class PersonDirector {
public:
    static Person createPerson() {
        ConcretePersonBuilder builder;
        return builder
            .withName("Alice")
            .withAge(30)
            .withAddress("123 Main St")
            .build();
    }
};

void builder_tb() {
    Person person = PersonDirector::createPerson();
    person.display();
}