#pragma once

//We shouldn't be... we do. To get infinity. But sure we can export it from somewhere properly.
#include "Utility.h"

class Interval{
public:
    double min, max; 

    Interval() : min(+infinity), max(-infinity) {}
    Interval(double _min, double _max) : min(_min), max(_max){};

    bool Coutains(double x) const{
        return min <= x && x <= max;
    }

    bool Surrounds(double x) const{
        return min < x && x < max;
    }


    static const Interval Empty, Universe;
};

const static Interval Empty (+infinity, -infinity);
const static Interval Universe (-infinity, +infinity);
