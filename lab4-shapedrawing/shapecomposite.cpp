#include "shapecomposite.h"

namespace Shapes
{
    ShapeComposite::ShapeComposite(std::shared_ptr<Shape> shape1, std::shared_ptr<Shape> shape2, ShapeOperation operation)
        : shape1_(shape1), shape2_(shape2), operation_(operation) {}

    bool ShapeComposite::isIn(int x, int y) const
    {
        switch (operation_)
        {
        case ShapeOperation::INTERSECTION:
            return isInIntersection(x, y);
        case ShapeOperation::SUM:
            return isInSum(x, y);
        case ShapeOperation::DIFFERENCE:
            return isInDifference(x, y);
        default:
            return false;
        }
    }

    bool ShapeComposite::isInIntersection(int x, int y) const
    {
        return shape1_->isIn(x, y) && shape2_->isIn(x, y);
    }

    bool ShapeComposite::isInSum(int x, int y) const
    {
        return shape1_->isIn(x, y) || shape2_->isIn(x, y);
    }

    bool ShapeComposite::isInDifference(int x, int y) const
    {
        return shape1_->isIn(x, y) && !shape2_->isIn(x, y);
    }
} // namespace Shapes
