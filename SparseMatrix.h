#pragma once
#include "Cell.h"
#include <iostream>

using namespace std;

class SparseMatrix {
public:
	SparseMatrix(const int rowSize, const int colSize);
	SparseMatrix(const SparseMatrix& base);
	~SparseMatrix();
	void print();
	void printByRows();
	void printByGet();
	void addValue(const int value, const int row, const int col);
	double getElement(const int row, const int col) const;
	int getSizeRows();
	int getSizeCols();
	void setElement(int value,int row, int col);
	SparseMatrix& operator=(const SparseMatrix& spMtrx);
	SparseMatrix& operator+=(const SparseMatrix& spMtrx);
	SparseMatrix& operator-=(const SparseMatrix& spMtrx);
	SparseMatrix& operator*=(const SparseMatrix& spMtrx);
	void operator^(const int num);
	SparseMatrix operator!();
	friend bool operator==(SparseMatrix& mtrx1, SparseMatrix& mtrx2);
	friend SparseMatrix operator+(SparseMatrix& mtrx1, SparseMatrix& mtrx2);
	friend SparseMatrix operator-(SparseMatrix& mtrx1, SparseMatrix& mtrx2);
	friend SparseMatrix operator*(SparseMatrix& mtrx1, SparseMatrix& mtrx2);
	friend ostream& operator<<(ostream& os,const SparseMatrix& mtrx1);
	friend istream& operator>>(istream& is,SparseMatrix& mtrx1);
	


private:
	int rowSize;
	int colSize;
	Cell* cellPtr;
	int elemNumb;
	void wrapper(int colSize, int rowSize);
	Cell* getPrevCol(int row, int col);
	Cell* getPrevRow(int row, int col);
	void removeElement(int row, int col);
};
