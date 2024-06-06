#pragma once

#include "shape.h"

namespace Shapes
{
    class Rectangle : public Shape
    {
    public:
        Rectangle(int xFrom, int yFrom, int xTo, int yTo);
        bool isIn(int x, int y) const override;


        int x() const { return bottomLeft_.x_; }
        int y() const { return bottomLeft_.y_; }
        int xTo() const { return topRight_.x_; }
        int yTo() const { return topRight_.y_; }

    private:
        Point bottomLeft_;
        Point topRight_;
    };
} // namespace Shapes
