#include "fraction.h"
#include "gcd.h"

Fraction::Fraction(int numerator, int denominator) : num(numerator), denom(denominator) { }
Fraction::Fraction(int numerator) : num(numerator), denom(1) { }

Fraction Fraction::operator - () const {
    return Fraction(-num, denom);
}

Fraction& Fraction::reduce() {
     int divisor = gcd(num, denom);
     num /= divisor;
     denom /= divisor;
     return *this;
}

int Fraction::getNum() const {
    return num;
}

int Fraction::getDenom() const {
    return denom;
}

bool Fraction::operator == (const Fraction &comparable) const {
    bool isEqual;
    Fraction lhs = *this;
    Fraction rhs = comparable;
    lhs.reduce();
    rhs.reduce();
    if(lhs.num == rhs.num && lhs.denom == rhs.denom){
        isEqual = true;
    }
    else {
        isEqual = false;
    }
    return isEqual;
}

bool Fraction::operator < (const Fraction &comparable) const {
    bool isLess;
    Fraction result = *this - comparable;
    if(result.num < 0){
        isLess = true;
    }
    else {
        isLess = false;
    }
    return isLess;
}

bool Fraction::isNull() const {
    return (num == 0)? true : false;
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
    Fraction result = *this;
    result.num *= divisor.denom;
    result.denom *= divisor.num;
    result.reduce();
    return result;
}

