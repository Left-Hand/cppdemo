#pragma once


#include <iostream>
#include <string>

// ���� Person ��
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

// ���� PersonBuilder �ӿ�
class PersonBuilder {
public:
    virtual ~PersonBuilder() {}
    virtual PersonBuilder& withName(const std::string& name) = 0;
    virtual PersonBuilder& withAge(int age) = 0;
    virtual PersonBuilder& withAddress(const std::string& address) = 0;
    virtual Person build() const = 0;
};

// ʵ�־���� ConcretePersonBuilder ��
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

// Director �������ƹ�������
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