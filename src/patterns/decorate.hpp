#pragma once

#include <iostream>
#include <string>

#include <memory>

// ���������ӿ�
class Component {
public:
    virtual void operation() const = 0;
    virtual ~Component() {}
};

// ����������
class ConcreteComponent : public Component {
public:
    void operation() const override {
        std::cout << "Concrete component operation." << std::endl;
    }
};

// װ��������
class Decorator : public Component {
protected:
    std::shared_ptr<Component> _component;
public:
    Decorator(std::shared_ptr<Component>component) : _component(component) {}
    void operation() const override {
        _component->operation();
    }
};

// �����װ������ - �ı���ɫ
class ColorDecorator : public Decorator {
public:
    ColorDecorator(std::shared_ptr<Component>component) : Decorator(component) {}
    void operation() const override {
        std::cout << "ColorDecorator: ";
        Decorator::operation();
    }
};

// ��һ�������װ������ - ��ӱ߿�
class BorderDecorator : public Decorator {
public:
    BorderDecorator(std::shared_ptr<Component>component) : Decorator(component) {}
    void operation() const override {
        std::cout << "BorderDecorator: ";
        Decorator::operation();
    }
};

__inline void decorate_tb() {
    // auto component = std::reinterpret_pointer_cast<Component>(std::make_shared<ConcreteComponent>());

    // component = std::reinterpret_pointer_cast<Component>(std::make_shared<ColorDecorator>(component));
    // component = std::reinterpret_pointer_cast<Component>(std::make_shared<BorderDecorator>(component));
    
    // std::shared_ptr<Component> component = std::make_shared<ConcreteComponent>();
    // component = std::make_shared<ColorDecorator>(component);
    // component = std::make_shared<BorderDecorator>(component);
    // component = std::make_shared<BorderDecorator>(component);

    std::shared_ptr<Component> component = std::make_unique<ConcreteComponent>();
    component = std::make_unique<ColorDecorator>(component);
    component = std::make_unique<BorderDecorator>(component);
    component = std::make_unique<BorderDecorator>(component);

    component->operation();
}

