#pragma once

#include <cmath>
#include <iostream>

using std::sqrt;
double RandomDouble01();
double RandomDouble(double min, double max);

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

    static Vec3 Random(){
        return Vec3(RandomDouble01(), RandomDouble01(), RandomDouble01());
    }

    static Vec3 Random(double min, double max){
        return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
    }

    bool NearZero() const{
        //Return true is the vec3 is close to zero in all dimensions
        auto s = 1e-8;
        return (fabs(e[0] < s) && fabs(e[1] < s) && fabs(e[2] < s));
    }




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

//In the book : unit_vector()
inline Vec3 Normalize(Vec3 v){
    return v / v.Length();
}

inline Vec3 RandomInUnitSphere(){
    while(true){//Rejection method
        auto p = Vec3::Random();
        if (p.LengthSquared() < 1){
            return p;
        }
    };
}

//In the book : random_unit_vector()
inline Vec3 RandomOnUnitSphere(){
    return Normalize(RandomInUnitSphere());
}

inline Vec3 RandomOnHemisphere(const Vec3& normal){
    Vec3 point = RandomOnUnitSphere();

    if (Dot(point,normal) > 0.0){
        return point;
    } else{
        return -point;
    }
}


inline Vec3 Reflect(const Vec3& vec, const Vec3 normal){
    return vec - 2 * Dot(vec, normal) * normal; //Metal reflection : v + 2b (Figure 15)
}

inline Vec3 Refract(const Vec3& uv, const Vec3& n, double EtaiOverEtat){
    auto cosTheta = fmin(Dot(-uv, n), 1.0);
    Vec3 rOutPerp = EtaiOverEtat * (uv + cosTheta * n);
    Vec3 rOutParallel = -sqrt (fabs(1.0 - rOutPerp.LengthSquared())) * n;
    return rOutPerp + rOutParallel;
}