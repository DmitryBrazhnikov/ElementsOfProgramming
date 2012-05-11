#pragma once
#include <vector>
#include "fraction.h"
 
class Polynom {
    public:
        explicit Polynom(int degree);
        
        int getDegree() const;
        const Fraction& leadCoef() const;
        int notNullCount() const;
      
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
        int resize(int newDegree);

        int degree;
        std::vector<Fraction> coefficients;
};

