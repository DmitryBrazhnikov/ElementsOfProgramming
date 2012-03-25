#pragma once

#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;

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
       
        void size(int &rows, int &columns);
		Type trace(); 
		CMatrix<Type> transpose(); 
		CMatrix<Type> minor(int, int);
		CMatrix<Type> inverse();
	    static CMatrix<Type> identity(int size);	
	    CMatrix<Type> getIdentity() const;	
	    static CMatrix<Type> nullMatrix(int size);	
        Type det();

        const vector<Type>& operator [] (int) const; 
        vector<Type>& operator [] (int); 
        CMatrix<Type>& operator += (const CMatrix<Type>&);
        CMatrix<Type>& operator -= (const CMatrix<Type>&);
        CMatrix<Type>& operator = (CMatrix<Type>);               
        CMatrix<Type> operator + (const CMatrix<Type>&) const;       
        CMatrix<Type> operator - (const CMatrix<Type>&) const; 
        CMatrix<Type> operator * (const CMatrix<Type>&) const;		
        bool operator == (const CMatrix<Type>&) const;		

    private:
        int rows;
        int columns;
        vector<vector<Type> > elems;
};


template <class Type>
CMatrix<Type>::CMatrix(){
	rows = 0;
	columns = 0;
}

template <class Type>
CMatrix<Type>::CMatrix(int _rows, int _columns){
	rows = 0;
	columns = 0;
	this->resize(_rows,_columns);
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
CMatrix<Type> CMatrix<Type>::getIdentity() const{
    return CMatrix<Type>::identity(rows);
}

template <class Type>
CMatrix<Type> CMatrix<Type>::nullMatrix(int size){
    CMatrix<Type> nullMatrix(size, size);
    nullMatrix.fill_nulls();
    return nullMatrix;
}

template <class Type>
CMatrix<Type>::CMatrix(const CMatrix<Type> &to_copy){
	rows = 0;
	columns = 0;
	this->resize(to_copy.rows, to_copy.columns);

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			elems[i][j] = to_copy.elems[i][j];
		}
	}
}

template <class Type>
CMatrix<Type>& CMatrix<Type>::resize(int _rows, int _columns){
	if(rows != _rows && columns != _columns){
		rows = _rows;
		columns = _columns;
		elems.resize(rows);
		for(int i = 0; i < rows; i++){
			elems[i].resize(columns);
		}
	}
	return *this;
}

template <class Type>
CMatrix<Type>::~CMatrix(){}

template <class Type>
void CMatrix<Type>::print(){ 
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
		cout << elems[i][j] << " ";
		}
		cout << endl;
	}
}

template <class Type>
void CMatrix<Type>::fill(){
	cout << "input an arbitrary matrix " << rows << "x" << columns << endl;
    for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			cin >> elems[i][j];
		}
	}
}

template <class Type>
void CMatrix<Type>::fill_nulls(){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			elems[i][j] = 0;
		}
	}
}

template <class Type>
Type CMatrix<Type>::trace(){
	assert(rows == columns);
	Type sum = 0;
	for(int i = 0; i < rows; i++){
		sum += elems[i][i];
	}
	return sum;
}

template <class Type>
const vector<Type>& CMatrix<Type>::operator [] (int i) const{
	assert(i >= 0 && i < rows);
	return elems[i];
}


template <class Type>
vector<Type>& CMatrix<Type>::operator [] (int i){
	assert(i >= 0 && i < rows);
	return elems[i];
}

template <class Type>
CMatrix<Type>& CMatrix<Type>::operator += (const CMatrix<Type> &matrix2){
	assert(rows == matrix2.rows && columns == matrix2.columns);
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			elems[i][j] += matrix2.elems[i][j];
		}
	}
	return *this;
}

template <class Type>
CMatrix<Type>& CMatrix<Type>::operator -= (const CMatrix<Type> &matrix2){
	assert(rows == matrix2.rows && columns == matrix2.columns);
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			elems[i][j] -= matrix2.elems[i][j];
		}
	}
	return *this;
}

template <class Type>
CMatrix<Type>& CMatrix<Type>::operator = (const CMatrix<Type> matrix2){
	if(rows != 0 && columns != 0){
		for(int i = 0; i < rows; i++){
			elems[i].clear();
		}
		elems.clear();
		rows = 0;
		columns = 0;
	}

	this->resize(matrix2.rows, matrix2.columns);
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			elems[i][j] = matrix2.elems[i][j];
		}
	}
	return *this;
} 

template <class Type>
CMatrix<Type> CMatrix<Type>::operator + (const CMatrix<Type>& matrix2) const{
	assert(columns == matrix2.columns && rows == matrix2.rows);
	CMatrix<Type> result (*this);
	result += matrix2;
	return result;
}

template <class Type>
CMatrix<Type> CMatrix<Type>::operator - (const CMatrix<Type>& matrix2) const {
	assert(columns == matrix2.columns && rows == matrix2.rows);
	CMatrix<Type> result (*this);
	result -= matrix2;
	return result;
}

template <class Type>
CMatrix<Type> CMatrix<Type>::operator * (const CMatrix<Type>& matrix2) const{
	assert(columns == matrix2.rows);
	CMatrix<Type> result (rows, matrix2.columns);
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < matrix2.columns; j++){
			int sum = 0;
			for(int k = 0; k < columns; k++){
				sum += elems[i][k] * matrix2.elems[k][j];
			}
			result[i][j] = sum;
		}          
	}

	return result;
}


template <class Type>
bool CMatrix<Type>::operator == (const CMatrix<Type> &comparableMatrix) const{
	assert((columns == comparableMatrix.columns) && (rows == comparableMatrix.rows));
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
            if((*this)[i][j] != comparableMatrix[i][j]){
                return false;
            }
		}          
	}
	return true;
}

template <class Type>
CMatrix<Type> CMatrix<Type>::transpose(){
	CMatrix<Type> tmatrix(columns, rows);
	for(int i = 0; i < columns; i++){
		for(int j = 0; j < rows; j++){
			tmatrix.elems[i][j] = elems[j][i];
		}
	}
	return tmatrix;
}


template <class Type>
CMatrix<Type> CMatrix<Type>::minor(int _i, int _j){
	assert(rows == columns);
	CMatrix<Type> new_matrix(columns-1, rows-1);
	int cur_i = 0;
	int cur_j = 0;

	for(int i = 0; i < rows; i++){
		if(i == _i) continue;
		for(int j = 0; j < columns; j++){
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
	assert(rows == columns);
	if(rows == 1){
		return elems[0][0];
	}

	Type number = 0;
	
	for(int i = 0; i < columns; i++){
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
	assert(rows == columns);
	Type det = this->det();
	assert(det != 0);

	CMatrix<Type> inmatrix (rows,columns);
	char mult;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			((i + j) % 2 == 0)? mult = 1 : mult = -1; 
			inmatrix.elems[i][j] = mult*(this->minor(j,i)).det()/det;
		}
	}
	return inmatrix;
}

