#pragma once

#include <iostream>
#include <cmath>

// 定义圆钉类
class RoundPeg {
public:
    RoundPeg(double radius) : _radius(radius) {}

    double getRadius() const {
        return _radius;
    }

private:
    double _radius;
};

// 定义圆孔类
class RoundHole {
public:
    RoundHole(double radius) : _radius(radius) {}

    double getRadius() const {
        return _radius;
    }

    bool fits(const RoundPeg& peg) const {
        return _radius >= peg.getRadius();
    }

private:
    double _radius;
};



// 定义方钉类
class SquarePeg {
public:
    SquarePeg(double width) : _width(width) {}

    double getWidth() const {
        return _width;
    }

private:
    double _width;
};

// 定义适配器类，使方钉可以适应圆孔
class SquarePegAdapter : public RoundPeg {
public:
    SquarePegAdapter(const SquarePeg& peg) : RoundPeg(peg.getWidth() * sqrt(2) / 2) {}

// private:
    // SquarePeg _peg;
};

void adaptor_tb() {
    RoundHole hole(5);
    RoundPeg rpeg(5);

    std::cout << "RoundPeg fits in the hole: " << hole.fits(rpeg) << std::endl; // 应输出 1 (true)

    SquarePeg small_sqpeg(5);
    SquarePeg large_sqpeg(10);

    SquarePegAdapter small_sqpeg_adapter(small_sqpeg);
    SquarePegAdapter large_sqpeg_adapter(large_sqpeg);

    std::cout << "Small SquarePeg fits in the hole: " << hole.fits(small_sqpeg_adapter) << std::endl; // 应输出 1 (true)
    std::cout << "Large SquarePeg fits in the hole: " << hole.fits(large_sqpeg_adapter) << std::endl; // 应输出 0 (false)

}