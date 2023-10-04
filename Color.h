#pragma once

#include "Vec3.h"
#include <iostream>

inline double LinearToGamma(double linearComponent){
    return sqrt(linearComponent);
}

inline Color LinearToGamma(Color color){
    return Color(LinearToGamma(color.x()),LinearToGamma(color.y()), LinearToGamma(color.z()));
}


void WriteColor(std::ostream &out, Color pixelColor, int samplesPerPixel){

    auto r = pixelColor.x();
    auto g = pixelColor.y();
    auto b = pixelColor.z();

    auto scale = 1.0 / samplesPerPixel;
    r *= scale;
    g *= scale;
    b *= scale;

    //Applying linear to gamma
    r = LinearToGamma(r);
    g = LinearToGamma(g);
    b = LinearToGamma(b);


    static const Interval intensity(0.000, 0.999);

    out << static_cast<int>(256 * intensity.Clamp(r)) << ' '
        << static_cast<int>(256 * intensity.Clamp(g)) << ' '
        << static_cast<int>(256 * intensity.Clamp(b)) << '\n';
}