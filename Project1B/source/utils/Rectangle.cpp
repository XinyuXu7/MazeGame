#include "../../include/utils/Rectangle.h"


bool Rectangle::inside(float x, float y) const
{
    // IX.A Implement this function, that returns true if the point <x,y> is inside this rectangle.
    
    if (x >= topLeft.x && x <= bottomRight.x && y >= topLeft.y && y <= bottomRight.y)
    {
        return true;
    }
    return false;
}

bool Rectangle::intersects(const Rectangle& rect) const
{
    // IX.B Implement this function, that returns true if the rectangle "rect" overlaps with this rectangle.

    return inside(rect.topLeft.x, rect.topLeft.y)|| inside(rect.topLeft.x, rect.bottomRight.y)
        || inside(rect.bottomRight.x, rect.topLeft.y)|| inside(rect.bottomRight.x, rect.bottomRight.y);

}

