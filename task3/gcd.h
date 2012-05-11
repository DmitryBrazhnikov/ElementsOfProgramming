#pragma once
#include "nullobject.h"
#include <algorithm>

template<class T>
T gcd(T dividend, T divisor) {
    while(!(T(0) == divisor)){
        dividend = dividend % divisor;
        std::swap(dividend, divisor);
    }
    return dividend;
} 
