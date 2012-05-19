#include <iostream>
#include <vector>
#include "fraction.h"
#include "polynom.h"
#include "gcd.h"
#include <cstdlib>
#include <set>
#include <cassert>
#include "primenumbers.h"

void testInt() { 
    srand(1000);
    
    PrimeNumbers prime(100);
    std::vector<int> primeNumbers = prime.getPrimeNumbers();
    
    for(int i = 0; i < 100; i++){
        int primeCount = primeNumbers.size();
        
        int initGcd = rand() % 100  + 1;
        
        int lhs = primeNumbers[rand() % (primeCount / 2)];
        int rhs = primeNumbers[rand() % (primeCount / 2) + primeCount/2 - 1];    
        
        int resultGcd = gcd(initGcd * lhs, initGcd * rhs); 
        
        assert(initGcd == resultGcd);
    }
}

Polynom getMonom(const Fraction& leadCoefficient, const Fraction& absoluteTerm){
    Polynom monom(1);
    monom[1] = leadCoefficient;
    monom[0] = absoluteTerm;
    return monom;
}

Polynom buildPolynom(const std::vector<int>& roots){
    Polynom result(0);
    result[0] = 1;
    
    for(int i = 0; i < roots.size(); i++){
        Polynom factor = getMonom(1, -roots[i]);
        result = result * factor;
    }

    return result;
}

std::vector<int> intersect(std::vector<int> leftSet, std::vector<int> rightSet){
    std::vector<int> commonSet(leftSet.size());
    std::vector<int>::iterator intersectIt;

    sort(leftSet.begin(), leftSet.end());
    sort(rightSet.begin(), rightSet.end());
    
    if(leftSet.size() > rightSet.size()){ 
        intersectIt = set_intersection(leftSet.begin(), leftSet.end(), rightSet.begin(), rightSet.end(), commonSet.begin());
    }
    else {
        intersectIt = set_intersection(rightSet.begin(), rightSet.end(), leftSet.begin(), leftSet.end(), commonSet.begin());
    }
    return std::vector<int>(commonSet.begin(), intersectIt);
}
     


void testPolynom() {
    srand(1000);
    for(int n = 0; n < 100; n++){ 
        const int NUM_ROOTS = 10; 
        
        std::vector<int> leftRoots(NUM_ROOTS);
        std::vector<int> rightRoots(NUM_ROOTS);

        for(int i = 0; i < NUM_ROOTS; i++){
            leftRoots[i] = rand() % 2 + 1; 
            rightRoots[i] = rand() % 2 + 1;
        }
        
        std::vector<int> commonRoots = intersect(leftRoots, rightRoots);
        
        Polynom initGcd = buildPolynom(commonRoots);  
        
        Polynom leftPolynom = buildPolynom(leftRoots);
        Polynom rightPolynom = buildPolynom(rightRoots); 
        Polynom resultGcd  = gcd(leftPolynom, rightPolynom);
        
        resultGcd.normalize(); 
        
        assert(initGcd == resultGcd);
    }
}

int main() {
    testInt();
    testPolynom();
    
    return 0;
}

