#pragma once

class Fraction {
    public:
        Fraction(int numerator, int denominator = 1);
        Fraction(): num(0), denom(1) { }
        
        Fraction operator - () const;
        Fraction& reduce();
        bool isNull() const; 
        
        int getNum() const;
        int getDenom() const; 
        
        bool operator == (const Fraction &comparable) const; 
        bool operator < (const Fraction &comparable) const; 
        
        Fraction operator + (const Fraction &addend) const;
        Fraction operator * (const Fraction &multiplier) const;
        Fraction operator / (const Fraction &multiplier) const;
        Fraction operator % (const Fraction &divisor) const;
        Fraction operator - (const Fraction &subtrahend) const;
            
    private: 
        int num; 
        int denom;
};

