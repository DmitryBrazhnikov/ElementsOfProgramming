#include <iostream>
#include "cmatrix.h"

using std::cout;

template<class T>
class CMultiply{
    public:
        T operator() (const T &a, const T &b){
            return a * b;
        }
        T operator() (const T &a){
            return a * a;
        }

        T identity()
};


template<class T, template<class> class BinFunc >
T pow(const T &a, const size_t &n, BinFunc<T> &function){
    T powA = a;
    T position = 0;
    T result = function.idenity();
    while((1 << position) <= n){
        if(n & (1 << position)){
            result = function(result, powA);
        }
        position++;
        powA = function(powA);
    }
    return result;
}

int main(){
    multiply<CMatrix<int> > func;

    CMatrix<int> matrix(3,3);
    matrix.fill_nulls();
    matrix[1][2] = 2;
    matrix[0][1] = 3;
    pow<CMatrix<int>, multiply >(matrix, 3, func);
    matrix.print();
    return 0;
}


