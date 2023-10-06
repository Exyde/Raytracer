#pragma once

#include "Utility.h"

#include "Color.h"
#include "Hittable.h"
#include "Material.h"

#include <iostream>

class Camera{

public:

    Camera() : imgHeight(imgWidth), center(Vec3(0)), pixel00Pos(Vec3(0)), pixelDeltaU(1), pixelDeltaV(1),
    u(Vec3(0)), v(Vec3(0)), w(Vec3(0)) {}

    double aspectRatio = 1.0;           // Aspect atio
    int imgWidth = 100;                 // Image width
    int samplesPerPixel = 500;           // Count of samples for each pixel
    int maxDepth = 10;                  // How many ray bounces

    double vFOV = 90;
    Point lookFrom = Point(0, 0, -1);   //The point we're looking from    
    Point lookAt = Point(0, 0, 0);      //The target look point
    Vec3 vUp = Vec3(0, 1, 0);      //Camera relative UP

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
                    pixelColor += RayColor(ray, maxDepth, world);    
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
    Vec3 u, v, w; // Camera Basis Vector


    void Init(){    
        //Compute height, at least 1
        imgHeight = static_cast<int>(imgWidth / aspectRatio);
        imgHeight = ( imgHeight < 1  ) ? 1 : imgHeight;

        //Camera
        auto focalLength = (lookFrom - lookAt).Length(); // Distance between eye position (camera) and the viewport. They are orthogonal.
        auto cameraCenter = lookFrom;

        //Virtual viewport - The viewport withint our ray will pass through 
        //FOV
        auto theta = DegToRad(vFOV);
        auto h = tan(theta/2); //Frustrum half height on viewport
        auto viewportHeight = 2 * h * focalLength;
        auto viewportWidth = viewportHeight * (static_cast<double>(imgWidth)/ imgHeight); //Since the ratio is an approximation, we recompute it here with reals values.

        //Calculate unit basis vector for camera coordinate frame
        w = Normalize(lookFrom - lookAt); //To the viewer 
        u = Normalize(Cross(vUp, w));
        v = Cross(w, u);

        //Kind of UV's to move along the viewport - Moves only on edges ?
        auto viewportU = viewportWidth * u; //Horizontal Edge, left to right
        auto viewportV = viewportHeight * -v; //Down Vertical Edge


        //Compute the horizontal and vertical pixel delta (Resolution kindof)
        pixelDeltaU = viewportU / imgWidth;
        pixelDeltaV = viewportV / imgHeight;

        //Location of upper left pixel
        auto viewportUpperLeft = cameraCenter - (focalLength * w) - viewportU /2 - viewportV / 2;
        pixel00Pos = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV); //Half of it, we want our pixel centered.
    }

    Color RayColor(const Ray& r, int depth,const Hittable& world){

        //If we exceed the limit, we don't call RayColor recursively anymore, and stop gathering light.
        if (depth <= 0){
            return Color(0);
        }

        HitInfo hit;

        if (world.Hit(r, Interval(0.001, infinity), hit)){ //This 0.001 tolerance is fixing "Shadow Acne" problem. Due to floating point precision
        //we might be inside the surface when we scater the next ray, and so we hit it from inside, causing some buggy artefacts.
        //So we add tolerance.
            Ray scattered;
            Color attenuation;

            if(hit.mat->Scatter(r, hit, attenuation, scattered)){
                return attenuation * RayColor(scattered, depth -1, world);
            }

            return Color(0, 0,0);
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