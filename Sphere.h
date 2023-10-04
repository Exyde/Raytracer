#pragma once

#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable{

public:
    Sphere(Point _center, double _radius, shared_ptr<Material> _material) : center(_center), radius(_radius), mat(_material) {}

    bool Hit(const Ray& r, Interval tRange, HitInfo& info) const override{

        Vec3 oc = r.Origin() - center; //Arbitrary point to center the sphere at.

        //auto a = Dot(r.Direction(), r.Direction()); //A vector dotter with itself is equal to it's lentgh squared.
        auto a = r.Direction().LengthSquared();
        //auto b = 2.0 * Dot(oc, r.Direction()); //is that commutative ? - it seems
        auto half_b = Dot(oc, r.Direction());
        auto c = oc.LengthSquared() - (radius * radius);
        auto discriminant = half_b * half_b - a*c;

        if (discriminant < 0) return false;

        auto sqrtd = sqrt(discriminant);

        //Find the nearest root in acceptable range.
        auto root = (-half_b - sqrtd) / a; //Well, that's the distance to the point?

        if (!tRange.Surrounds(root)){
            root = (-half_b + sqrtd) / a;
            if (!tRange.Surrounds(root)){
                return false;
            }
        }

        info.t = root;
        info.p = r.At(info.t);
        Vec3 outwardNormal = (info.p - center) / radius;
        info.SetFaceNormal(r, outwardNormal);
        info.mat = mat;

        return true;
    }


private:
    Point center;
    double radius;
    shared_ptr<Material> mat;
};