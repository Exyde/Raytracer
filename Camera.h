#pragma once

#include "Utility.h"

#include "Color.h"
#include "Hittable.h"

#include <iostream>

class Camera{

public:

    Camera() : imgHeight(imgWidth), center(Vec3(0)), pixel00Pos(Vec3(0)), pixelDeltaU(1), pixelDeltaV(1) {}

    double aspectRatio = 1.0;
    int imgWidth = 100;
    int samplesPerPixel = 10;

    void Render(const Hittable& world){
        Init();

        //Render --

        std::cout << "P3\n" << imgWidth << " " << imgHeight << "\n255\n";

        for (int j = 0; j < imgHeight; ++j){

            double percent  = j + 1;
            std::cerr << "Progress : " << percent <<  "/" << imgHeight << "\n" << std::flush;

            for (int i = 0; i < imgWidth; ++i){
                
                Color pixelColor = Color(0);

                for (int sample = 0; sample < samplesPerPixel; ++sample){
                    Ray ray = GetRay(i, j);
                    pixelColor += RayColor(ray, world);    
                }

                WriteColor(std::cout, pixelColor, samplesPerPixel);
            }
        }

        std::cerr << "\nImage rendered !\n";
    }


private:

    int imgHeight;
    Point center;
    Point pixel00Pos;
    Vec3 pixelDeltaU, pixelDeltaV;

    void Init(){    
        //Compute height, at least 1
        imgHeight = static_cast<int>(imgWidth / aspectRatio);
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
        pixelDeltaU = viewportU / imgWidth;
        pixelDeltaV = viewportV / imgHeight;

        //Location of upper left pixel
        auto viewportUpperLeft = cameraCenter - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2; //Top Left Pos
        pixel00Pos = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV); //Half of it, we want our pixel centered.
    }

    Color RayColor(const Ray& r, const Hittable& world){

        HitInfo hit;
        if (world.Hit(r, Interval(0, infinity), hit)){
            Vec3 rayBounceDir = RandomOnHemisphere(hit.normal);
            return 0.5 * RayColor(Ray(hit.p, rayBounceDir), world);
        }

        Vec3 unitDirection = Normalize(r.Direction());

        auto t = 0.5 * (unitDirection.y() + 1.0); //Remap coordinate to [0, 1] and use as t for lerp.
        //Lerp : blenderValue = (1 - a) * startValue + a * endValue - SkyGradient
        return Color (1.0 - t) * Color(1.0) + t * Color(0.5, 0.7, 1.0);
    }

    Ray GetRay(int i, int j) const{
        //Get a randomly sampled camera ray forthe pixel at location [i, j]


        auto pixelCenteredPos = pixel00Pos + (i * pixelDeltaU) + (j * pixelDeltaV);
        auto pixelSample =  pixelCenteredPos + PixelSampleSquare();

        auto rayOrigin = center;
        auto rayDirection = pixelSample - rayOrigin;
        return Ray(rayOrigin, rayDirection);
    }

    Vec3 PixelSampleSquare() const{
        //Return a random point in the square surrounding a pixel centerly sampled.
        auto px = -0.5 + RandomDouble01();
        auto py = -0.5 + RandomDouble01();
        return (px * pixelDeltaU) + (py * pixelDeltaV);
    }
};