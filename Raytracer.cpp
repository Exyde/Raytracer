#include "Utility.h"

#include "Camera.h"
#include "HittableList.h"
#include "Sphere.h"

int main (){
    
    //Camera
    Camera cam;
    cam.aspectRatio = 16.0 / 9.0;
    cam.imgWidth = 400;
    cam.samplesPerPixel = 500; //Anti-aliasing
    cam.maxDepth = 50;
    cam.vFOV = 20;

    cam.lookFrom = Point(-2, -2, 2);
    cam.lookAt = Point(0, 0, -1);
    cam.vUp = Vec3(0, 1 , 0);

    //Materials
    std::shared_ptr<Lambertian> M_Ground = make_shared<Lambertian>(Color(0.3, 0.1, 0.75));
    auto M_Center = make_shared<Dielectric>(1.5);
    auto M_Right = make_shared<Metallic>(Color(0.2, 0.6, 0.4), 0);
    auto M_Left = make_shared<Metallic>(Color(0.1, 0.1, 0.89), 1);
    auto M_Meh = make_shared<Metallic>(Color(0.75, 0.1, 0.89), 0.3);


    //World
    HittableList world;

    //Two Spheres
    double R = cos(PI/4);
    world.Add(make_shared<Sphere>(Point(-R, 0 , -1), R/2, M_Right));
    world.Add(make_shared<Sphere>(Point(R, 0 , -1), R/2, M_Meh));
    world.Add(make_shared<Sphere>(Point(0 , R , -1), R/2, M_Left));
    world.Add(make_shared<Sphere>(Point(0, -R , -1), R/2, M_Center));


    world.Add(make_shared<Sphere>(Point(0, -100.5, -1), 100, M_Ground));
    world.Add(make_shared<Sphere>(Point(0, 0, -1), 0.5, M_Center));
    world.Add(make_shared<Sphere>(Point(-1, 0, -1), 0.5, M_Right));
    world.Add(make_shared<Sphere>(Point(1, 0, -1), 0.5, M_Center));
    world.Add(make_shared<Sphere>(Point(0, 1, -1), 0.5, M_Meh));

    //Hollow sphere trick (negative radius)
//    world.Add(make_shared<Sphere>(Point(0, -1, -1), -0.4, M_Center));

   cam.Render(world);
}