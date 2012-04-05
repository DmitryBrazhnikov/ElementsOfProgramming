#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::min;
using std::max;
using std::swap;

class Polynom {
    public:
        Polynom(int degree);
        Polynom(const vector<int> &polynom);
        
        int degree() const;
        int leaderCoefficient() const;
        void print() const;
        
        int& operator [] (int index);

    private:
        vector<int> coefficients;
};

Polynom::Polynom(int degree) : coefficients(degree + 1, 1) { }
Polynom::Polynom(const vector<int> &polynom) : coefficients(polynom) { }

int Polynom::degree() const {
    return coefficients.size();
}

int Polynom::leaderCoefficient() const {
    return coefficients[degree()];
}

int& Polynom::operator [] (int index) {
    return coefficients[index];
}

void Polynom::print() const {
    for(int i = 0; i < degree(); i++){
        cout << coefficients[i] << "x^" << i;
        if(i < degree() - 1){
            cout << " + ";
        }
    }
    cout << endl;
}

template<class T>
class GCD {
    public:
        T operator () (T lhs, T rhs) const {
            T dividend = max(lhs, rhs);
            T divisor = min(lhs, rhs);

            while(divisor != 0){
                dividend = dividend % divisor;
                swap(dividend, divisor);
            }

            return dividend;
        }
}; 

int main() {
    Polynom p1(3);
    p1[0] = -42;
    p1[1] = 0;
    p1[2] = -12;
    p1[3] = 1;
    p1.print();
    
    Polynom p2(1);
    p2[0] = -3;
    p2[1] = 1;
    p2.print();
   
    GCD<int> gcd;
    cout << gcd(7,12);
     
    
    return 0;
}






