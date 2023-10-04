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

    //Materials
    auto M_Ground = make_shared<Lambertian>(Color(0.3, 0.1, 0.75));
    auto M_Center = make_shared<Dielectric>(1.5);
    auto M_Right = make_shared<Metallic>(Color(0.2, 0.6, 0.4), 0);
    auto M_Left = make_shared<Metallic>(Color(0.1, 0.1, 0.89), 1);
    auto M_Meh = make_shared<Metallic>(Color(0.75, 0.1, 0.89), 0.3);


    //World
    HittableList world;
    world.Add(make_shared<Sphere>(Point(0, -100.5, -1), 100, M_Ground));
    world.Add(make_shared<Sphere>(Point(0, 0, -1), 0.5, M_Center));
    world.Add(make_shared<Sphere>(Point(-1, 0, -1), 0.5, M_Right));
    world.Add(make_shared<Sphere>(Point(1, 0, -1), 0.5, M_Left));
    world.Add(make_shared<Sphere>(Point(0, 1, -1), 0.5, M_Meh)); //Up

    //Hollow sphere trick (negative radius)
    world.Add(make_shared<Sphere>(Point(0, -1, -1), -0.4, M_Center));

   cam.Render(world);
}