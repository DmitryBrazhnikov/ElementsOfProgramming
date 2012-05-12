#pragma once
#include <vector>
#include "fraction.h"
#include <ostream>
 
class Polynom {
    public:
        explicit Polynom(int degree);
        
        int getDegree() const;
        const Fraction& leadCoef() const;
      
        bool operator == (const Polynom &comparable) const; 
        bool operator != (const Polynom &comparable) const; 
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
        Polynom& normalize();
       
        friend std::ostream& operator << (std::ostream& out, const Polynom& polynom);
        void print() const;
        
        Fraction& operator [] (int degree);
        const Fraction& operator [] (int degree) const;

    private:
        void updateDegree(); //uodate value of the member degree
        int degree;
        
        int resize(int newDegree); //resize the array of coefficients
        std::vector<Fraction> coefficients;
};

