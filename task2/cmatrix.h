#pragma once

#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;

//class

template <class Type>
class CMatrix {
    public:
        CMatrix();
        CMatrix(int, int);
        CMatrix(const CMatrix<Type>&);
        
        ~CMatrix();

		CMatrix<Type>& resize(int, int);

        void print();
        void fill();
        void fill_nulls();
       
		Type trace(); //trace
		CMatrix<Type> transp(); //Transponition
		CMatrix<Type> minor(int, int);
		CMatrix<Type> inverse();
	    static CMatrix<Type> identity(int size);	
        Type det();

        const vector<Type>& operator [] (int) const; 
        vector<Type>& operator [] (int); 
        CMatrix<Type>& operator += (const CMatrix<Type>&);
        CMatrix<Type>& operator -= (const CMatrix<Type>&);
        CMatrix<Type>& operator = (CMatrix<Type>);               
        CMatrix<Type> operator + (const CMatrix<Type>&);       
        CMatrix<Type> operator - (const CMatrix<Type>&); 
        CMatrix<Type> operator * (const CMatrix<Type>&);		

    private:
        //Count of strings
        int m;
        //Count of columns
        int n;
        //Array of elements
        vector<vector<Type> > elems;
};

//methods

template <class Type>
CMatrix<Type>::CMatrix(){
	m = 0;
	n = 0;
}

template <class Type>
CMatrix<Type>::CMatrix(int _m, int _n){
	m = 0;
	n = 0;
	this->resize(_m,_n);
}

template <class Type>
CMatrix<Type> CMatrix<Type>::identity(int size){
    CMatrix<Type> identity(size, size);
    identity.fill_nulls();
    for(int i = 0; i < size; i++){
        identity[i][i] = 1;
    }
    return identity;
}

template <class Type>
CMatrix<Type>::CMatrix(const CMatrix<Type> &to_copy){
	m = 0;
	n = 0;
	this->resize(to_copy.m, to_copy.n);

	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			elems[i][j] = to_copy.elems[i][j];
		}
	}
}

template <class Type>
CMatrix<Type>& CMatrix<Type>::resize(int _m, int _n){
	if(m != _m && n != _n){
		m = _m;
		n = _n;
		elems.resize(m);
		for(int i = 0; i < m; i++){
			elems[i].resize(n);
		}
	}
	return *this;
}

template <class Type>
CMatrix<Type>::~CMatrix(){}

template <class Type>
void CMatrix<Type>::print(){ 
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
		cout << elems[i][j] << " ";
		}
		cout << endl;
	}
}

template <class Type>
void CMatrix<Type>::fill(){
	cout << "input an arbitrary matrix " << m << "x" << n << endl;
    for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			cin >> elems[i][j];
		}
	}
}

template <class Type>
void CMatrix<Type>::fill_nulls(){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			elems[i][j] = 0;
		}
	}
}

template <class Type>
Type CMatrix<Type>::trace(){
	assert(m == n);
	Type sum = 0;
	for(int i = 0; i < m; i++){
		sum += elems[i][i];
	}
	return sum;
}

template <class Type>
const vector<Type>& CMatrix<Type>::operator [] (int i) const{
	assert(i >= 0 && i < m);
	return elems[i];
}


template <class Type>
vector<Type>& CMatrix<Type>::operator [] (int i){
	assert(i >= 0 && i < m);
	return elems[i];
}

template <class Type>
CMatrix<Type>& CMatrix<Type>::operator += (const CMatrix<Type> &matrix2){
	assert(m == matrix2.m && n == matrix2.n);
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			elems[i][j] += matrix2.elems[i][j];
		}
	}
	return *this;
}

template <class Type>
CMatrix<Type>& CMatrix<Type>::operator -= (const CMatrix<Type> &matrix2){
	assert(m == matrix2.m && n == matrix2.n);
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			elems[i][j] -= matrix2.elems[i][j];
		}
	}
	return *this;
}

template <class Type>
CMatrix<Type>& CMatrix<Type>::operator = (const CMatrix<Type> matrix2){
	if(m != 0 && n != 0){
		for(int i = 0; i < m; i++){
			elems[i].clear();
		}
		elems.clear();
		m = 0;
		n = 0;
	}

	this->resize(matrix2.m, matrix2.n);
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			elems[i][j] = matrix2.elems[i][j];
		}
	}
	return *this;
} 

template <class Type>
CMatrix<Type> CMatrix<Type>::operator + (const CMatrix<Type>& matrix2){
	assert(n == matrix2.n && m == matrix2.m);
	CMatrix<Type> result (*this);
	result += matrix2;
	return result;
}

template <class Type>
CMatrix<Type> CMatrix<Type>::operator - (const CMatrix<Type>& matrix2){
	assert(n == matrix2.n && m == matrix2.m);
	CMatrix<Type> result (*this);
	result -= matrix2;
	return result;
}

template <class Type>
CMatrix<Type> CMatrix<Type>::operator * (const CMatrix<Type>& matrix2){
	assert(n == matrix2.m);
	CMatrix<Type> result (m, matrix2.n);
	for(int i = 0; i < m; i++){
		for(int j = 0; j < matrix2.n; j++){
			int sum = 0;
			for(int k = 0; k < n; k++){
				sum += elems[i][k] * matrix2.elems[k][j];
			}
			result[i][j] = sum;
		}          
	}

	return result;
}

template <class Type>
CMatrix<Type> CMatrix<Type>::transp(){
	CMatrix<Type> tmatrix(n, m);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			tmatrix.elems[i][j] = elems[j][i];
		}
	}
	return tmatrix;
}


template <class Type>
CMatrix<Type> CMatrix<Type>::minor(int _i, int _j){
	assert(m == n);
	CMatrix<Type> new_matrix(n-1, m-1);
	int cur_i = 0;
	int cur_j = 0;

	for(int i = 0; i < m; i++){
		if(i == _i) continue;
		for(int j = 0; j < n; j++){
			if(j == _j) continue;
			new_matrix.elems[cur_i][cur_j] = elems[i][j];
			cur_j++;
		}
		cur_j = 0;
		cur_i++;
	}
	return new_matrix;
}

template <class Type>
Type CMatrix<Type>::det(){
	assert(m == n);
	if(m == 1){
		return elems[0][0];
	}

	Type number = 0;
	
	for(int i = 0; i < n; i++){
		CMatrix<Type> tmatrix;
		tmatrix = this->minor(0,i);
		if(i % 2 == 0){
			number += this->elems[0][i]*tmatrix.det();
		}
		else{
			number -= this->elems[0][i]*tmatrix.det();
		}
 	}
	return number;
}

template <class Type>
CMatrix<Type> CMatrix<Type>::inverse(){
	assert(m == n);
	Type det = this->det();
	assert(det != 0);

	CMatrix<Type> inmatrix (m,n);
	char mult;
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			((i + j) % 2 == 0)? mult = 1 : mult = -1; 
			inmatrix.elems[i][j] = mult*(this->minor(j,i)).det()/det;
		}
	}
	return inmatrix;
}

