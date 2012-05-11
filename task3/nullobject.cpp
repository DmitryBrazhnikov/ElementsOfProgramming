#include "nullobject.h"
#include "polynom.h"

bool NullObject::operator == (int comparable) const {
    return comparable == 0;
}

bool NullObject::operator == (const Polynom &comparable) const {
    return Polynom(0) == comparable;
}

bool NullObject::operator == (const Fraction &comparable) const {
    Fraction nullFraction =  0;
    bool isEqual;
    if(comparable == nullFraction){
        isEqual = true;
    } 
    else {
        isEqual = false;
    }
    return isEqual;
}

