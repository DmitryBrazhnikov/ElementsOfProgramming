#include "polynom.h"
#include <iostream>
#include "gcd.h"
#include <algorithm>

using std::abs;

using std::cout;
using std::endl;
      
Polynom::Polynom(int degree_) : coefficients(degree_ + 1, 0), degree(degree_) { }

bool Polynom::operator == (const Polynom &comparable) const {
    bool isEqual = true;
    if(degree != comparable.getDegree()){
        isEqual = false;
    }
    else{
        for(int i = 0; i <= degree && isEqual == true; i++){
            if(!((*this)[i] == comparable[i])){
                isEqual = false;
            }
        }
    }
    return isEqual;
}

bool Polynom::operator < (const Polynom &comparable) const {
    bool isLess = false;
    if(degree < comparable.getDegree()){
        isLess = true;
    }
    else if(degree > comparable.getDegree()){
        isLess = false;
    }
    else{
        for(int i = degree; (i >= 0) && (isLess == false); i--){
            if((*this)[i] < comparable[i]){
                isLess = true;
            }
        }
    }
    return isLess;
}

bool Polynom::operator > (const Polynom &comparable) const {
    bool isGreater = true;
    if(!(comparable < *this)){
        isGreater = false;
    }
    return isGreater;
}
         
Polynom Polynom::operator - () const {
    Polynom result = *this;
    for(int i = 0; i <= result.getDegree(); i++){
        result[i] = -result[i];
    }
    return result;
}

int Polynom::resize(int newDegree){
    if(coefficients.size() < (newDegree + 1)){
        coefficients.resize(newDegree + 1, 0);
    }
    degree = newDegree;
    return degree;
}


Polynom Polynom::operator + (const Polynom &addend) const {
    Polynom result = *this;
    if(result.getDegree() <= addend.getDegree()){
        result.resize(addend.getDegree());
    }

    for(int i = 0; i <= addend.getDegree(); i++){
        result[i] = result[i] + addend[i];
    }
    return result;
}

Polynom Polynom::operator - (const Polynom &subtrahend) const {
    Polynom result = *this + (-subtrahend);
    result.updateDegree();
    return result;
}


Polynom Polynom::operator * (const Fraction &factor) const {
    Polynom result = *this;
    for(int i = 0; i <= result.getDegree(); i++){
        result[i] = result[i] * factor;
    }
    return result;
}

Polynom Polynom::operator * (const Polynom &factor) const {
    int leadDegree = degree + factor.getDegree();
    int polyCount = leadDegree;
    
    Polynom result(leadDegree);
    
    for(int m = 0; m <= degree; m++){
        Polynom preresult(leadDegree);
        for(int n = 0; n <= factor.getDegree(); n++){
            preresult[m+n] = (*this)[m] * factor[n];
        }
        result = result + preresult; 
    }
    return result;
}


int Polynom::notNullCount() const {
    int count = 0;
    for(int i = 0; i < degree; i++){
        if(!((*this)[i].isNull())){
            count++;
        }
    }
    return count;
}

Polynom Polynom::operator / (const Fraction &divisor) const {
    Polynom result = *this;
    for(int i = 0; i <= result.getDegree(); i++){
        result[i] = result[i] / divisor;
    }
    return result;
}

Polynom Polynom::operator / (const Polynom &polyDivisor) const {
    Polynom reminder = *this;
    Polynom divisor = polyDivisor;
    
    int degDiff = reminder.getDegree() - divisor.getDegree();
    Polynom result(degDiff);
    
    while(degDiff >= 0){
        Fraction coefficient = reminder[degDiff + divisor.getDegree()] / divisor.leadCoef();
        Polynom factor(degDiff);
        factor[degDiff] = coefficient;
        reminder = reminder - (divisor * factor);
        degDiff--;
        result = result + factor;
    }
    return result;
}

Polynom Polynom::operator % (const Polynom &divisor) const {
    Polynom reminder = (*this - divisor * (*this / divisor));
    return reminder; 
}
        
void Polynom::updateDegree(){
    while(coefficients[degree].isNull() && degree > 0){
        degree--;
    }
}

int Polynom::getDegree() const {
    return degree;
}

const Fraction& Polynom::leadCoef() const {
    return coefficients[getDegree()];
}

Fraction& Polynom::operator [] (int degree) {
    return coefficients.at(degree);
}

const Fraction& Polynom::operator [] (int degree) const{
    return coefficients.at(degree);
}

void Polynom::print() const {
    for(int i = getDegree(); i >= 0; i--){
        cout << coefficients[i].getNum() << "/" << coefficients[i].getDenom() << "x^" << i;
        if(i > 0){
            cout << " + ";
        }
    }
    cout << endl;
}
