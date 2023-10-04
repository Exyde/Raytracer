#pragma once

#include "Utility.h"
#include "Hittable.h" //We shouldn't include this, but seems we need it aswell... ><

class HitInfo; //Tell the compiler : eh it exists somewhere else, trust me

class Material{

public:
    virtual ~Material() = default; //Virtual default destuctor. Must me public

    virtual bool Scatter(const Ray& in, const HitInfo& hit, Color& attenuation, Ray& scattered) const = 0;    
};

class Lambertian : public Material {
public:

    Lambertian(Color color) : albedo(color){}

    bool Scatter(const Ray& in, const HitInfo& hit, Color& attenuation, Ray& scattered) const override{

        auto scatterDirection = hit.normal + RandomOnUnitSphere(); //Dispersed direction

        if (scatterDirection.NearZero()){
            scatterDirection = hit.normal;
        }

        scattered = Ray(hit.p, scatterDirection);
        attenuation = albedo;
        return true;
    }
    

private:
    Color albedo;
};

class Metallic : public Material{

public:

    Metallic(Color color, double fuzzRadius) : albedo(color), fuzz(fuzzRadius < 1 ? fuzzRadius : 1) {}

    bool Scatter(const Ray& in, const HitInfo& hit, Color& attenuation, Ray& scattered) const override{

        Vec3 reflected = Reflect(Normalize(in.Direction()), hit.normal);
        scattered = Ray(hit.p, reflected + fuzz * RandomOnUnitSphere());
        attenuation = albedo;
        return (Dot(scattered.Direction(), hit.normal) > 0);
    }
    
private:
    Color albedo;
    double fuzz;
};