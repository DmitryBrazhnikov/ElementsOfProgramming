#include "fraction.h"
#include "gcd.h"
#include <cassert>

Fraction::Fraction(int numerator, int denominator) : num(numerator), denom(denominator) { }

Fraction Fraction::operator - () const {
    return Fraction(-num, denom);
}

Fraction& Fraction::reduce() {
     int divisor = gcd(num, denom);
     num /= divisor;
     denom /= divisor;
     if(denom < 0){
         denom *= -1;
         num *= -1;
     }
     return *this;
}

int Fraction::getNum() const {
    return num;
}

int Fraction::getDenom() const {
    return denom;
}

bool Fraction::operator == (const Fraction &comparable) const {
    Fraction lhs = *this;
    Fraction rhs = comparable;
    lhs.reduce();
    rhs.reduce();
    return (lhs.num == rhs.num && lhs.denom == rhs.denom);
}

bool Fraction::operator != (const Fraction &comparable) const {
    return !(*this == comparable);
}

bool Fraction::operator < (const Fraction &comparable) const {
    Fraction result = *this - comparable;
    return (result.num < 0);
}

bool Fraction::isNull() const {
    return (num == 0);
}

Fraction Fraction::operator + (const Fraction &addend) const {
    Fraction result = *this;
    if(result.denom == addend.denom){
        result.num += addend.num;
    }
    else{
        result.num = result.num * addend.denom + addend.num * result.denom;
        result.denom *= addend.denom;
    }
    result.reduce();
    
    return result;
}

Fraction Fraction::operator - (const Fraction &subtrahend) const {
    Fraction result = *this + (-subtrahend);
    result.reduce();
    return result;
}

Fraction Fraction::operator * (const Fraction &multiplier) const {
    Fraction result = *this;
    result.num *= multiplier.num;
    result.denom *= multiplier.denom;
    result.reduce();
    return result;
}

Fraction Fraction::operator / (const Fraction &divisor) const {
    assert(divisor != Fraction(0));
    Fraction result = *this;
    result.num *= divisor.denom;
    result.denom *= divisor.num;
    result.reduce();
    return result;
}

