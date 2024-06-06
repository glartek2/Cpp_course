#include "rectangle.h"

namespace Shapes
{
    Rectangle::Rectangle(int xFrom, int yFrom, int xTo, int yTo)
        : bottomLeft_{xFrom, yFrom}, topRight_{xTo, yTo}
    {
    }

    bool Rectangle::isIn(int x, int y) const
    {
        return x >= bottomLeft_.x_ && x <= topRight_.x_ && y >= bottomLeft_.y_ && y <= topRight_.y_;
    }
} // namespace Shapes
