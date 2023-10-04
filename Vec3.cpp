#include "Vec3.h"

Vec3::Vec3() : e{0, 0, 0} {}; //Default
Vec3::Vec3(double x, double y, double z) : e{x, y, z}{}
Vec3::Vec3(double s): e{s, s, s}{}

double Vec3::x() const { return e[0];}
double Vec3::y() const { return e[1];}
double Vec3::z() const { return e[2];}

Vec3 Vec3::operator-() const {return Vec3(-e[0], -e[1], -e[2]);}
double Vec3::operator[](int i) const {return e[i];}
double& Vec3::operator[](int i) {return e[i];}

Vec3& Vec3::operator+=(const Vec3 &v){
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

Vec3& Vec3::operator-=(const Vec3 &v){
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}


Vec3& Vec3::operator*=(const Vec3 &v){
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

Vec3& Vec3::operator/=(const Vec3 &v){
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}
Vec3& Vec3::operator+=(const double s){
    return *this += Vec3(s, s, s);    
}

Vec3& Vec3::operator-=(const double s){
    return *this += Vec3(-s, -s, -s);    
}

Vec3& Vec3::operator*=(const double s){
    e[0] *= s;
    e[1] *= s;
    e[2] *= s;
    return *this;
}

Vec3& Vec3::operator/=(const double s){
    return *this *= 1/s;
}

double Vec3::Length() const{
    return sqrt(LengthSquared());
}

double Vec3::LengthSquared() const{
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}
