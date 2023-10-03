#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

//Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//Constants
const double infinity = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

//Functions
inline double DegToRad(double degrees){
    return degrees * PI / 180.0;
}

inline double RandomDouble01(){
    //Return a random real in [0, 1)
    return rand() / (RAND_MAX + 1.0);
}

inline double RandomDouble(double min, double max){
    //Return a random real in [min, max)
    return min + (max-min) * RandomDouble01();
}

//Headers
#include "Interval.h" 
#include "Ray.h"
#include "Vec3.h"

