#pragma once

#include "Weasel/Base/Asserts.hpp"

#include <math.h>
#include <sstream>

namespace Weasel {
    struct Point2D {
        Point2D(f64 x, f64 y) : X(x), Y(y) {}
        Point2D() {}
        f64 X;
        f64 Y;
        inline Point2D operator+ (const Point2D& other) const { return {X + other.X, Y + other.Y}; }
        inline Point2D operator- (const Point2D& other) const { return {X - other.X, Y - other.Y}; }
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

    namespace Maths {
        inline f64 Clamp(f64 x, f64 min, f64 max) { return fmin(fmax(x, min), max); }
        inline f32 Clamp(f32 x, f32 min, f32 max) { return fmin(fmax(x, min), max); }
        inline i64 Clamp(i64 x, i64 min, i64 max) { return fmin(fmax(x, min), max); }
        inline i32 Clamp(i32 x, i32 min, i32 max) { return fmin(fmax(x, min), max); }
        inline Point2D Clamp(Point2D p, Point2D bl, Point2D tr) { 
            return { Maths::Clamp(p.X, bl.X, tr.X), Maths::Clamp(p.Y, bl.Y, tr.Y) };
        }
    }
}

