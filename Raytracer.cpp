#include "Utility.h"

#include "Color.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

#include <iostream>
//Todo : Fix progress bar.

Color RayColor(const Ray& r, const Hittable& world){

    HitInfo hit;
    if (world.Hit(r, Interval(0, infinity), hit)){
        return 0.5 * (hit.normal + Color(1));
    }


    Vec3 unitDirection = Normalize(r.Direction());

    auto t = 0.5 * (unitDirection.y() + 1.0); //Remap coordinate to [0, 1] and use as t for lerp.

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

    //World
    HittableList world;
    world.Add(make_shared<Sphere>(Point(0, 0, -1), 0.5));
    world.Add(make_shared<Sphere>(Point(0, -100.5, -1), 100)); //Green
    
    /*
    world.Add(make_shared<Sphere>(Point(0, 100.5, -1), 100)); //UP
    world.Add(make_shared<Sphere>(Point(100.5, 0, -1), 100)); //LEFT
    world.Add(make_shared<Sphere>(Point(-100.5, 0, -1), 100)); //DOWN
    */

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

        double percent  = j + 1;
        std::cerr << "Progress : " << percent <<  "/" << imgHeight << "\n" << std::flush;

        for (int i = 0; i < imgWidth; ++i){
            
            auto pixelCenteredPos = pixel00Pos + (i * pixelDeltaU) + (j * pixelDeltaV);
            auto rayDirection = pixelCenteredPos - cameraCenter; //Not normalized, but it's 1 for the moment
            Ray ray(cameraCenter, rayDirection);

            Color pixelColor = RayColor(ray, world);
            WriteColor(std::cout, pixelColor);
        }
    }

    std::cerr << "\nImage rendered !\n";
}