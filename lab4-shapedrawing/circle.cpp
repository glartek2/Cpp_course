#include "circle.h"
#include <cmath>

namespace Shapes
{
    Circle::Circle(int xCenter, int yCenter, int radius)
        : center_{xCenter, yCenter}, radius_{radius}
    {
    }

    bool Circle::isIn(int x, int y) const
    {
        
        return std::sqrt(std::pow(x - center_.x_, 2) + std::pow(y - center_.y_, 2)) <= radius_;
    }
} // namespace Shapes
