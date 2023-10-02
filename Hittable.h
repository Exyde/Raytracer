#pragma once

#include "Ray.h"

class HitInfo{
public: 
    Point p;
    Vec3 normal;
    double t;
    bool frontFace;

    void SetFaceNormal(const Ray& r, const Vec3& outwardNormal){

        //outwardNormal is assumed to be UNIT LENGTH.
        frontFace = Dot(r.Direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable{
public:
    virtual ~Hittable() = default;

    virtual bool Hit (const Ray& r, double tMin, double tMax, HitInfo& info) const = 0;
};