#pragma once

#include "Vec3.h"
#include <iostream>

void WriteColor(std::ostream &out, Color color);

void WriteColor(std::ostream &out, Color color){
    out << static_cast<int>(255.999 * color.x()) << ' '
        << static_cast<int>(255.999 * color.y()) << ' '
        << static_cast<int>(255.999 * color.z()) << '\n';
}