#pragma once

#include "Ray.h"

class HitInfo{
public: 
    Point p;
    Vec3 normal;
    double t;
    bool frontFace;

    HitInfo(): p(Vec3(0)), normal(Vec3(0)), t(0), frontFace(false){}

    void SetFaceNormal(const Ray& r, const Vec3& outwardNormal){

        //outwardNormal is assumed to be UNIT LENGTH.
        frontFace = Dot(r.Direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable{
public:
    virtual ~Hittable() = default;

    virtual bool Hit (const Ray& r, Interval tRange, HitInfo& info) const = 0;
};