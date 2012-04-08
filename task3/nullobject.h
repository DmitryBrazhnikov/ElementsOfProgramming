#pragma once
#include "polynom.h" 

class NullObject {
    public: 
        bool operator == (int comparable) const;
        bool operator == (const Fraction &comparable) const;
        bool operator == (const Polynom &comparable) const;
};
