#include <iostream>
#include "Vec3.h"
#include "Color.h"
#include "Ray.h"

//Todo : Fix progress bar.

double HitSphere(const Point& center, double radius, const Ray& r){

    //Sphere equation : x² + y² + z² = r² is on sphere, < is inside, > is outside.
    //We solve this by putting this in the vector form.

    Vec3 oc = r.Origin() - center; //Arbitrary point to center the sphere at.

    auto a = Dot(r.Direction(), r.Direction());
    auto b = 2.0 * Dot(oc, r.Direction()); //is that commutative ? - it seems
    auto c = Dot(oc, oc) - (radius * radius);
    auto discriminant = b*b - 4*a*c;

    //Not on point
    if (discriminant < 0){
        return -1.0;
    } else {
        return (-b - sqrt(discriminant) / (2.0 * a));
    }
}

Color RayColor(const Ray& r){

    auto t = HitSphere(Point(0, 0, -1), 0.5, r);

    if (t > 0.0){
        Vec3 N = Normalize(r.At(t) - Vec3(0, 0,-1)); //Direction from the surface hit point to the center.
        return 0.5 *Color(N.x() + 1, N.y() + 1, N.z() + 1);
    }


    Vec3 unitDirection = Normalize(r.Direction());

    t = 0.5 * (unitDirection.y() + 1.0); //Remap coordinate to [0, 1] and use as t for lerp.

    //Lerp : blenderValue = (1 - a) * startValue + a * endValue - SkyGradient
    return Color (1.0 - t) * Color(1.0) + t * Color(0.5, 0.7, 1.0);
}

int main (){

    //Aspect Ratio
    auto const ASPECT_RATIO = 16.0 / 9.0; //Ideal ratio, but not 100% accurate.
    int imgWidth = 400;
    int imgHeight;

    //Compute height, at least 1
    imgHeight = static_cast<int>(imgWidth / ASPECT_RATIO);
    imgHeight = ( imgHeight < 1  ) ? 1 : imgHeight;

    //Virtual viewport - The viewport withint our ray will pass through 
    auto viewportHeight = 2.0; // Arbitrary
    auto viewportWidth = viewportHeight * (static_cast<double>(imgWidth)/ imgHeight); //Since the ratio is an approximation, we recompute it here with reals values.

    //Camera
    auto focalLength = 1.0; // Distance between eye position (camera) and the viewport. They are orthogonal.
    auto cameraCenter = Point(0, 0, 0);

    //Kind of UV's to move along the viewport - Moves only on edges ?
    auto viewportU = Vec3(viewportWidth, 0 , 0); //That's the length, and we might lerp from 0 to length
    auto viewportV = Vec3(0, -viewportHeight, 0);

    //Compute the horizontal and vertical pixel delta (Resolution kindof)
    auto pixelDeltaU = viewportU / imgWidth;
    auto pixelDeltaV = viewportV / imgHeight;

    //Location of upper left pixel
    auto viewportUpperLeft = cameraCenter - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2; //Top Left Pos
    auto pixel00Pos = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV); //Half of it, we want our pixel centered.

    //Render --

    std::cout << "P3\n" << imgWidth << " " << imgHeight << "\n255\n";

    for (int j = 0; j < imgHeight; ++j){

        std::cerr << "Progress : " << ((j - imgHeight)) / (double)imgHeight * 100.0<<  "%\n" << std::flush;

        for (int i = 0; i < imgWidth; ++i){
            
            auto pixelCenteredPos = pixel00Pos + (i * pixelDeltaU) + (j * pixelDeltaV);
            auto rayDirection = pixelCenteredPos - cameraCenter; //Not normalized, but it's 1 for the moment
            Ray ray(cameraCenter, rayDirection);


            Color pixelColor = RayColor(ray);
            WriteColor(std::cout, pixelColor);
        }
    }

    std::cerr << "\nImage rendered !\n";
}