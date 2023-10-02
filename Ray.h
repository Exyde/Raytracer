#pragma once

#include "Vec3.h"

class Ray{
public:

    Ray(): origin(Vec3(0)), direction(Vec3(0)) {}
    Ray (const Point& _origin, const Vec3& _direction) : origin(_origin), direction(_direction) {}


    Point Origin() const { return origin; }
    Vec3 Direction() const { return direction; }

    Point At(double t) const{
        return origin + t * direction;
    }

private:
    Point origin;
    Vec3 direction;

};