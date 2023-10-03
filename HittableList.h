#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable{

public:
    std::vector<shared_ptr<Hittable>> hittables;

    HittableList(): hittables(){}
    HittableList(shared_ptr<Hittable> object):hittables(){ Add(object);}

    void Clear() { hittables.clear(); }

    void Add(shared_ptr<Hittable> object){
        hittables.push_back(object);
    }

    bool Hit(const Ray& r, Interval tRange, HitInfo& info) const override{
        HitInfo tempInfo;
        bool hitSomething = false;
        auto closestT = tRange.max;

        for (const auto& object : hittables){
            if (object->Hit(r, Interval(tRange.min, closestT), tempInfo)){
                hitSomething = true;
                closestT = tempInfo.t;
                info = tempInfo;
            }
        }

        return hitSomething;
    }

};