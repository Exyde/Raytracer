#pragma once

#include "Utility.h"

class HitInfo; //Tell the compiler : eh it exists somewhere else, trust me

class Material{

public:
    virtual ~Material() = default; //Virtual default destuctor. Must me public

    virtual bool Scatter(const Ray& in, const HitInfo& hit, Color& attenuation, Ray& scattered) const = 0;    
};