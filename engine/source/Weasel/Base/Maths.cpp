#include "Weasel/Base/Maths.hpp"

#include <math.h>
#include <sstream>

namespace Weasel {
    std::string Point2D::ToString() {
        std::stringstream ss;
        ss << "(" << X << ", " << Y << ")";
        return ss.str();
    }

    Rect2D::Rect2D(Point2D first, Point2D second) {
        Left = fmin(first.X, second.X);
        Right = fmax(first.X, second.X);
        Bottom = fmin(first.Y, second.Y);
        Top = fmax(first.Y, second.Y);
    }

    Rect2D::Rect2D(f64 width, f64 height, Point2D center) {
        Left = center.X - width/2;
        Right = center.X + width/2;
        Bottom = center.Y - height/2;
        Top = center.Y + height/2;
    }    
}