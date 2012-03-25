#include <iostream>
#include "cmatrix.h"
#include <cstdlib>
#include <math.h>

using std::cout;

template<class T>
class CInvolution{
    public:
        T operator() (const T &a){
            return a * a;
        }
        
        T operator() (const T &a, const T &b){
            return a * b;
        }

        T virtual identity() const = 0;
};

template<class T>
class CIntInvolution : public CInvolution<T> {
    public:
        T identity() const {
            return 1;
        }
};

template<class T>
class CMatrixInvolution : public CInvolution<T> {
    public:
        CMatrixInvolution(int _rows, int _columns){
            assert(_rows == _columns);
            rows = _rows;
            columns = _columns;
        }
         
        T identity() const {
            return T::identity(rows);
        }

    private:
        int rows;
        int columns;
};

template<class T, template<class> class BinFunc >
T pow(const T &base, int exponent, BinFunc<T> &function){
    T powA = base;
    int position = 0;
    T result = function.identity();
    while((1 << position) <= exponent){
        if(exponent & (1 << position)){
            result = function(result, powA);
        }
        position++;
        powA = function(powA);
    }
    return result;
}

template<class T>
CMatrix<T> matrixInvol(const CMatrix<T> &base, int exponent){
    CMatrix<T> result = base.getIdentity();
    for(int i = 0; i < exponent; i++){
        result = result * base;
    }
    return result;
}

void testMatrixInvolution(){
    srand(1000);
    for(int i = 0; i < 100; i++){
        int exponent = rand() % 4 + 1;
        int matrixSize = rand() % 6 + 1;

        CMatrix<int> standardMatrix(matrixSize, matrixSize);
        for(int i = 0; i < matrixSize; i++){
            for(int j = 0; j < matrixSize; j++){
                standardMatrix[i][j] = rand() % 5 + 1;
            }
        }
        CMatrix<int> undertestMatrix = standardMatrix;
        standardMatrix = matrixInvol(standardMatrix, exponent);
        
        CMatrixInvolution<CMatrix<int> > multiplier(matrixSize,matrixSize);
        undertestMatrix = pow<CMatrix<int>, CMatrixInvolution>(undertestMatrix, exponent, multiplier);
        
        //undertestMatrix.print();
        //standardMatrix.print();

        assert( standardMatrix == undertestMatrix);
    }
}

void testIntInvolution(){
    srand(1000);
    for(int i = 0; i < 1000; i++){
        int exponent = rand() % 10 + 1;
        int standard = rand() % 6 + 1;
        int undertest = standard;
        
        CIntInvolution<int> multiplier;
        undertest = pow<int, CIntInvolution>(undertest, exponent, multiplier);
        
        standard = pow(standard, exponent);
        
        //cout << undertest << endl;
        //cout << standard << endl << endl;

        assert(standard == undertest);
    }
}

int main(){
    testMatrixInvolution();
    testIntInvolution();
    
    return 0;
}


