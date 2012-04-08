#include "nullobject.h"
#include "polynom.h"

bool NullObject::operator == (int comparable) const {
    bool isEqual;
    if(comparable == 0){
        isEqual = true;
    } 
    else {
        isEqual = false;
    }
    return isEqual;
}

bool NullObject::operator == (const Polynom &comparable) const {
    Polynom NullPolynom(0);
    bool isEqual;
    if(comparable == NullPolynom){
        isEqual = true;
    } 
    else {
        isEqual = false;
    }
    return isEqual;
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

