#pragma once

#include "Weasel/Base/Asserts.hpp"

namespace Weasel {
    struct Point2D {
        Point2D(f64 x, f64 y) : X(x), Y(y) {}
        Point2D() {}
        f64 X;
        f64 Y;

        std::string ToString();
    };

    struct Rect2D {
        Rect2D(f64 left, f64 right, f64 bottom, f64 top) : Left(left), Right(right), Bottom(bottom), Top(top) {}
        Rect2D(Point2D first, Point2D second);
        Rect2D(f64 width, f64 height, Point2D center);
        Rect2D() {}

        f64 Left;
        f64 Right;
        f64 Bottom;
        f64 Top;

        std::string ToString();
    };
}

