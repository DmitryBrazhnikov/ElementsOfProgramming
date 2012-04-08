#pragma once
#include "nullobject.h"
#include <algorithm>

using std::swap;
using std::min;
using std::max;

template<class T>
T gcd(const T &lhs, const T &rhs) {
    T dividend = max(lhs,rhs);
    T divisor = min(lhs,rhs);
    NullObject nullObj;
    while(!(nullObj == divisor)){
        dividend = dividend % divisor;
        swap(dividend, divisor);
    }

    return dividend;
} 
