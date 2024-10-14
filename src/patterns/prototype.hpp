#pragma once


#include <iostream>
#include <memory>
#include <utility>
#include <functional>

// 基类 Shape
class Shape {
public:
    virtual ~Shape() = default;
    virtual std::shared_ptr<Shape> clone() const = 0;
    virtual void draw() const = 0;
};
// 具体的形状类 Circle
class Circle : public Shape {
public:
    Circle(int radius) : _radius(radius) {}
    std::shared_ptr<Shape> clone() const override {
        return std::make_shared<Circle>(_radius);
    }
    void draw() const override {
        std::cout << "Drawing a circle with radius " << _radius << std::endl;
    }

private:
    int _radius;
};

// 具体的形状类 Square
class Square : public Shape {
public:
    Square(int side) : _side(side) {}
    std::shared_ptr<Shape> clone() const override {
        return std::make_shared<Square>(_side);
    }
    void draw() const override {
        std::cout << "Drawing a square with side " << _side << std::endl;
    }

private:
    int _side;
};

void prototype_tb() {
    auto circle = Circle(5);
    // auto clonedCircle = std::invoke(circle,clone());
    auto clonedCircle = std::invoke(&Circle::clone, &circle);
    clonedCircle->draw(); // 输出: Drawing a circle with radius 5

    auto square = std::make_shared<Square>(4);
    auto clonedSquare = square->clone();
    clonedSquare->draw(); // 输出: Drawing a square with side 4
}