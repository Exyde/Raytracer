#include "Utility.h"

#include "Camera.h"
#include "HittableList.h"
#include "Sphere.h"

int main (){
    
    //Camera
    Camera cam;
    cam.aspectRatio = 16.0 / 9.0;
    cam.imgWidth = 400;
    cam.samplesPerPixel = 100; //Anti-aliasing
    cam.maxDepth = 50;

    //World
    HittableList world;
    world.Add(make_shared<Sphere>(Point(0, 0, -1), 0.5));
    world.Add(make_shared<Sphere>(Point(0, -100.5, -1), 100)); //Green
    
   cam.Render(world);
}