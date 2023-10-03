#include "Utility.h"

#include "Camera.h"
#include "HittableList.h"
#include "Sphere.h"

int main (){
    
    //Camera
    Camera cam;
    cam.aspectRatio = 16.0 / 9.0;
    cam.imgWidth = 400;

    //World
    HittableList world;
    world.Add(make_shared<Sphere>(Point(0, 0, -1), 0.5));
    world.Add(make_shared<Sphere>(Point(0, -100.5, -1), 100)); //Green
    
    /*
    world.Add(make_shared<Sphere>(Point(0, 100.5, -1), 100)); //UP
    world.Add(make_shared<Sphere>(Point(100.5, 0, -1), 100)); //LEFT
    world.Add(make_shared<Sphere>(Point(-100.5, 0, -1), 100)); //DOWN
    */

   cam.Render(world);

}