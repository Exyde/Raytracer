#pragma once

#include <cmath>
#include <limits>
#include <memory>

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

//Headers
#include "Ray.h"
#include "Vec3.h"

