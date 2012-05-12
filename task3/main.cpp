#include <iostream>
#include <vector>
#include "fraction.h"
#include "polynom.h"
#include "gcd.h"
#include <cstdlib>
#include <set>
#include <cassert>

void testInt() { 
    srand(1000);
    for(int i = 0; i < 500; i++){
        int lhs = rand() % 1000 + 1;  
        int rhs = rand() % 1000 + 1; 
        int greatCommonDivisor = gcd(lhs,rhs);
        
        std::cout << "(" << lhs << "," << rhs << ") = " << greatCommonDivisor << std::endl;
    }
}

void testPolynom() {
    srand(1000);
    for(int n = 0; n < 50; n++){ 
        int RootsCount = 6; 
        std::set<int> leftRoots;
        std::set<int> rightRoots;
        std::vector<int> commonRoots(RootsCount);
        std::vector<int> differentRoots(RootsCount);

        for(int i = 0; i < RootsCount; i++){
            leftRoots.insert(rand() % 5 + 1);
            rightRoots.insert(rand() % 5 + 1);
        }
        
        std::vector<int>::iterator intersectIt;
        std::vector<int>::iterator differenceIt;

        std::vector<int>::iterator commonIt = commonRoots.begin();
        std::vector<int>::iterator differentIt = differentRoots.begin();
        Polynom factor(1); 
        factor[1] = 1;
         
        if(leftRoots.size() > rightRoots.size()){ 
            differenceIt = set_difference(leftRoots.begin(), leftRoots.end(), rightRoots.begin(), rightRoots.end(), differentRoots.begin());
            intersectIt = set_intersection(leftRoots.begin(), leftRoots.end(), rightRoots.begin(), rightRoots.end(), commonRoots.begin());
        }
        else {
            differenceIt = set_difference(rightRoots.begin(), rightRoots.end(), leftRoots.begin(), leftRoots.end(), differentRoots.begin());
            intersectIt = set_intersection(rightRoots.begin(), rightRoots.end(), leftRoots.begin(), leftRoots.end(), commonRoots.begin());
        }
        
        Polynom rightPolynom(0);
        rightPolynom[0] = 1;
        for(; differentIt != differenceIt; differentIt++){
            factor[0] = -*differentIt;
            rightPolynom = rightPolynom * factor;
        }
        
        Polynom leftPolynom(0);
        leftPolynom[0] = 1;
        for(; commonIt != intersectIt; commonIt++){
            factor[0] = -*commonIt;
            leftPolynom = leftPolynom * factor;
        }
        
        
        /*
        std::set<int>::iterator lsit = leftRoots.begin();
        for(; lsit != leftRoots.end(); lsit++){
            std::cout << *lsit << " ";
        }
        std::cout << std::endl;
        std::set<int>::iterator rsit = rightRoots.begin();
        for(; rsit != rightRoots.end(); rsit++){
            std::cout << *rsit << " ";
        }
        std::cout << std::endl;

        for(int i = 0; i < RootsCount; i++){
            std::cout << commonRoots[i] << " ";
        }
        std::cout << std::endl;
        for(int i = 0; i < RootsCount; i++){
            std::cout << differentRoots[i] << " ";
        }
        std::cout << std::endl;

        leftPolynom.print();
        rightPolynom.print();
        */

        Polynom initGcd(0);
        initGcd[0] = 1;

        factor[0] = -(rand() % 5 + 1);
        initGcd = initGcd * factor;
        factor[0] = -(rand() % 5 + 1);
        initGcd = initGcd * factor;
        
        Polynom resultGcd  = gcd(leftPolynom,rightPolynom);
        resultGcd = gcd(initGcd * leftPolynom, initGcd * rightPolynom);
        resultGcd.normalize(); 
        
        assert(initGcd == resultGcd);
    }
}

int main() {
    //testInt();
    testPolynom();

    return 0;
}

