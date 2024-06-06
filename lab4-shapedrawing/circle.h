#pragma once

#include "shape.h"

namespace Shapes
{
    class Circle : public Shape
    {
    public:
        Circle(int xCenter, int yCenter, int radius);
        bool isIn(int x, int y) const override;

        int x() const { return center_.x_; }
        int y() const { return center_.y_; }
        int radius() const { return radius_; }

    private:
        Point center_;
        int radius_;
    };
} // namespace Shapes
