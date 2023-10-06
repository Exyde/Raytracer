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

        auto compilerWarningThrower = in; //Just because the compiler is yelling at me because in is not used there.
        auto scatterDirection = hit.normal + RandomOnUnitSphere(); //Dispersed direction

        if (scatterDirection.NearZero()){
            scatterDirection = hit.normal + compilerWarningThrower.Direction() - compilerWarningThrower.Direction();
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

class Dielectric : public Material{
public:

    Dielectric(double refractionIndice) : ir(refractionIndice) {}

    bool Scatter(const Ray& in, const HitInfo& hit, Color& attenuation, Ray& scattered) const override{
        attenuation = Color(1.0);
        double refractionRatio = hit.frontFace ? (1.0/ir) : ir;

        Vec3 unitDirection = Normalize(in.Direction());
        double cosTheta = fmin(Dot(-unitDirection, hit.normal), 1.0);
        double sinTheta = sqrt(1.0 - cosTheta * cosTheta);
        
        bool cannotRefract = refractionRatio * sinTheta > 1.0;
        Vec3 direction;;

        if (cannotRefract || Reflectance(cosTheta, refractionRatio) > RandomDouble01()){ 
            direction = Reflect(unitDirection, hit.normal);
        } else{
            direction = Refract(unitDirection, hit.normal, refractionRatio);
        }


        scattered = Ray(hit.p, direction);
        return true;
    }
private:
    double ir;

    static double Reflectance(double cosine, double refIdx){
        //Using Shlick's approximation for reflectance, instead of a big and ugly equation
        auto r0 = (1-refIdx) / (1+refIdx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};