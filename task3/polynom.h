#pragma once
#include <vector>
#include "fraction.h"
 
using std::vector;

class Polynom {
    public:
        Polynom(int degree);
        
        int getDegree() const;
        const Fraction& leadCoef() const;
        int notNullCount() const;
        int resize(int newDegree);
      
        bool operator == (const Polynom &comparable) const; 
        bool operator < (const Polynom &comparable) const; 
        bool operator > (const Polynom &comparable) const; 

        Polynom operator - () const;
        Polynom operator + (const Polynom &addend) const;
        Polynom operator - (const Polynom &subtrahend) const;
        Polynom operator * (const Fraction &factor) const;
        Polynom operator * (const Polynom &factor) const;
        Polynom operator / (const Polynom &divisor) const;
        Polynom operator / (const Fraction &divisor) const;
        Polynom operator % (const Polynom &divisor) const;
        
        void print() const;
        
        Fraction& operator [] (int degree);
        const Fraction& operator [] (int degree) const;

    private:
        void updateDegree();

        int degree;
        vector<Fraction> coefficients;
};

