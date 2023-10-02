#pragma once

#include <cmath>
#include <iostream>

using std::sqrt;

//Aliases for Vec3 ! - Might refactor this, or implement vec4 later.

class Vec3{

public:
    Vec3();
    Vec3(double x, double y, double z);
    Vec3(double s);
    
    double x() const;
    double y() const; 
    double z() const;

    Vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);


    Vec3& operator+=(const Vec3 &v);
    Vec3& operator-=(const Vec3 &v);
    Vec3& operator*=(const Vec3 &v);
    Vec3& operator/=(const Vec3 &v);


    Vec3& operator+=(const double s);
    Vec3& operator-=(const double s);
    Vec3& operator*=(const double s);
    Vec3& operator/=(const double s);

    double Length() const;
    double LengthSquared() const;

    

public:
    double e[3]; //element
};

using Point = Vec3;
using Color = Vec3;

inline Vec3 operator*(const Vec3 &a, const Vec3 &b){
    return Vec3(a.e[0] * b.e[0], a.e[1] * b.e[1], a.e[2] * b.e[2]);
}

inline Vec3 operator*(double s, const Vec3 &a){
    return Vec3(s * a.e[0], s * a.e[1], s * a.e[2]);
}

inline Vec3 operator*(const Vec3 &a, double s){
    return s * a;
}

inline std::ostream& operator<<(std::ostream& out, const Vec3 &v){
    return out << "(" << v.e[0] << "," << v.e[1] << "," << v.e[2] << ")";
}

inline Vec3 operator+(const Vec3 &a, const Vec3 &b){
    return Vec3(a.e[0] + b.e[0], a.e[1] + b.e[1], a.e[2] + b.e[2]);
}


inline Vec3 operator-(const Vec3 &a, const Vec3 &b){
    return Vec3(a.e[0] - b.e[0], a.e[1] - b.e[1], a.e[2] - b.e[2]);
}

inline Vec3 operator/(const Vec3 &a, double s){
    return a * (1/s);
}

inline double Dot (const Vec3 &a, const Vec3 &b){
    return a.e[0] * b.e[0] + a.e[1] * b.e[1] + a.e[2] * b.e[2];
}

inline Vec3 Cross(const Vec3 &a, const Vec3 &b){
    return Vec3( a.e[1] * b.e[2] - a.e[2] * b.e[1],
                 a.e[2] * b.e[0] - a.e[0] * b.e[2],
                 a.e[0] * b.e[1] - a.e[1] * b.e[0]
    );
}

inline Vec3 Normalize(Vec3 v){
    return v / v.Length();
}