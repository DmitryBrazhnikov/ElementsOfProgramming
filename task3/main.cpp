#include <iostream>
#include <vector>
#include "fraction.h"
#include "polynom.h"
#include "gcd.h"
#include <cstdlib>

using std::cout;
using std::endl;

void testInt() { 
    srand(1000);
    for(int i = 0; i < 500; i++){
        int lhs = rand() % 1000 + 1;  
        int rhs = rand() % 1000 + 1; 
        int greatCommonDivisor = gcd(lhs,rhs);
        cout << "(" << lhs << "," << rhs << ") = " << greatCommonDivisor << endl;
    }
}

void testPolynom() {
    srand(1000);
    for(int i = 0; i < 100; i++){
        int lhsDegree = rand() % 4 + 1;
        int rhsDegree = rand() % 2 + 1;
        
        Polynom lhs(lhsDegree);
        for(int i = 0; i <= lhsDegree; i++){
            lhs[i] = rand() % 4 + 1;
        }

        Polynom rhs(rhsDegree);
        for(int i = 0; i <= rhsDegree; i++){
            rhs[i] = rand() % 2 + 1;
        }

        lhs.print();
        rhs.print();

        Polynom greatCommonDivisor = gcd(lhs,rhs);
        cout << "gcd: "; 
        greatCommonDivisor.print();
    }
}

int main() {
    testInt();
    testPolynom();
    return 0;
}

