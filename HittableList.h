#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable{

public:
    std::vector<shared_ptr<Hittable>> hittables;

    HittableList(){}
    HittableList(shared_ptr<Hittable> object) { Add(object);}

    void Clear() { hittables.clear(); }

    void Add(shared_ptr<Hittable> object){
        hittables.push_back(object);
    }

    bool Hit(const Ray& r, double tMin, double tMax, HitInfo& info) const override{
        HitInfo tempInfo;
        bool hitSomething = false;
        auto closestT = tMax;

        for (const auto& object : hittables){
            if (object->Hit(r, tMin, closestT, tempInfo)){
                hitSomething = true;
                closestT = tempInfo.t;
                info = tempInfo;
            }
        }

        return hitSomething;
    }

};