#include "SparseMatrix.h"
#include <iostream>
#include<stdlib.h>

using namespace std;


//constructor with arguments
SparseMatrix::SparseMatrix(const int rowSize, const int colSize) {
	wrapper(rowSize, colSize);
}

//copy constructor
SparseMatrix::SparseMatrix(const SparseMatrix& base) {
	cout << "Creating matrix using copy constructor \n\n";
	rowSize = base.rowSize;
	colSize = base.colSize;
	wrapper(rowSize, colSize);
	for (int i = 0; i < colSize; i++) {
		for (int j = 0; j <rowSize; j++) {
			this->addValue(base.getElement(i, j),i, j);
		}
	}
}

//destructor
SparseMatrix::~SparseMatrix() {
	Cell* temp = cellPtr->nextCellRow;
	for (int i = 0; i < rowSize; i++) {
		Cell* printer = temp->nextCellCol;
		while (printer != temp) {
			Cell* temp2 = printer->nextCellCol;
			
			delete(printer);
			printer = temp2;
		}
		//cout<<"switching row\n\n";
		Cell* remContr = temp->nextCellRow;
		delete(temp);
		temp = remContr;
	}

	temp = temp->nextCellCol;
	while (temp != cellPtr) {
		Cell* temp2 = temp->nextCellCol;
		delete(temp);
		temp = temp2;
	}
	delete(cellPtr);
}


int SparseMatrix::getSizeCols() {
	return colSize;
}

int SparseMatrix::getSizeRows() {
	return rowSize;

}


//adding value in sparse matrix
void SparseMatrix::addValue(const int value, const int row, const int col) {
	
	if (row > colSize || col > rowSize || row < 0 || col < 0) {
		throw exception("Error, Matrix index out of bounds");
	}
	else {
		//cout << "adding cell " << value << "\n";
		if (value != 0) {
			
			Cell* toAdd = new Cell();
			toAdd->colId = col;
			toAdd->rowId = row;
			toAdd->value = value;

			
			Cell* prevCol = getPrevCol(row, col);
			toAdd->nextCellCol = prevCol->nextCellCol;
			prevCol->nextCellCol = toAdd;
			
			
			Cell* prevRow = getPrevRow(row, col);

			//cout << prevRow->value << " prevRowValues\n";
			toAdd->nextCellRow = prevRow->nextCellRow;
			prevRow->nextCellRow = toAdd;

			
		}
		
	}
}

//return previous element in row to tobe added one
Cell* SparseMatrix::getPrevRow(int row, int col) {
	Cell* tracker = cellPtr;
	Cell* temp = cellPtr->nextCellCol;
	for (int i = 0; i < row; i++) {
		if (temp->nextCellCol != tracker) {
			temp = temp->nextCellCol;
		}
		else {
			break;
		}
		
	}
	tracker = temp;
	while (temp->nextCellRow != tracker) {
		if (temp->nextCellRow->rowId == row && temp->nextCellRow->colId == col) {
			return temp;
		}
		else {
			temp = temp->nextCellRow;
		}
	}
	
}

//return previous element in col to tobe added one
Cell* SparseMatrix::getPrevCol(int row, int col) {
	Cell* tracker = cellPtr;
	Cell* temp = cellPtr->nextCellRow;
	for (int i = 0; i < col; i++) {
		if (temp->nextCellRow != tracker) {
			temp = temp->nextCellRow;
		}

	}
	tracker = temp;
	while (temp->nextCellCol != tracker) {
		if (temp->nextCellCol->rowId == row && temp->nextCellCol->colId == col) {
			return temp;
		}
		else {
			temp = temp->nextCellCol;
		}
	}
}

void SparseMatrix::print() {
	Cell* temp = cellPtr->nextCellRow;
	for (int i = 0; i < rowSize; i++) {
		Cell* printer = temp->nextCellCol;
		cout << temp->value << " is pointing to " << temp->nextCellCol->value << " \n\n";
		while (printer != temp) {
			cout << printer->value << " is pointing to " << printer->nextCellCol->value << " \n\n";
			//cout << "On location " << printer->rowId << " , " << printer->colId << " there is " << printer->value << "\n\n";
			printer = printer->nextCellCol;
		}
		//cout<<"switching row\n\n";
		temp = temp->nextCellRow;
	}
}

void SparseMatrix::printByRows() {
	Cell* temp = cellPtr->nextCellCol;
	for (int i = 0; i < colSize; i++) {
		Cell* printer = temp->nextCellRow;
		//cout << temp->value << " is pointing to " << temp->nextCellRow->value << " \n\n";
		while (printer != temp) {
			//cout << printer->value << " is pointing to " << printer->nextCellRow->value << " \n\n";
			cout << "On location " << printer->rowId << " , " << printer->colId << " there is " << printer->value << "\n\n";
			printer = printer->nextCellRow;
		}
		//cout<<"switching row\n\n";
		temp = temp->nextCellCol;
	}
}

void SparseMatrix::printByGet() {
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			cout << "On location " << j << " , " << i << " there is " << getElement(j, i) << " \n";
		}
	}
}

//retrieving specific element in sparse matrix, implements checks and uses getPrevCol function
double SparseMatrix::getElement(const int row, const int col) const{
	if (row > colSize || row < 0 || col > rowSize || col < 0) {
		throw exception("Error while getting an element, index out of bounds");
	}
	else {
		//Cell* temp = getPrevCol(0, col);
		Cell* temp = cellPtr->nextCellRow;
		for (int i = 0; i < col; i++) {
			temp = temp->nextCellRow;
		}
		Cell* iterator = temp->nextCellCol;
		while (iterator != temp) {
			if (iterator->rowId == row && iterator->colId == col) {
				return iterator->value;
				
			}
			iterator = iterator->nextCellCol;
		}
		return 0;
	}
}


//need to finnish this
void SparseMatrix::setElement(int value, int row,int col) {
	if (row > colSize || col > rowSize || row < 0 || col < 0) {
		throw exception("Error, Matrix index out of bounds\n");
	}
	else {
		Cell* prevCol = getPrevCol(row , col);
			//cout << prevCol->value << "\n\n\n";
		prevCol->nextCellCol->value = value;

	}
}

//finnish and test this
SparseMatrix& SparseMatrix::operator=(const SparseMatrix& spMtrx) {
	SparseMatrix* destruct = this;

	wrapper(spMtrx.rowSize, spMtrx.colSize);
	for (int i = 0; i < colSize; i++) {
		for (int j = 0; j < rowSize; j++) {
			this->addValue(spMtrx.getElement(i, j), i, j);
		}
	}
	return *this;
}

//if element in current martixe is 0 but not in second one new element is added
//if addition of two values yelds 0 element is removed
SparseMatrix& SparseMatrix::operator+=(const SparseMatrix& spMtrx) {
	if (rowSize != spMtrx.rowSize || colSize != spMtrx.colSize) {
		throw exception("Error during addition, matrices have different dimensions\n");
	}
	else {
		for (int i = 0; i < colSize; i++) {
			for (int j = 0; j < rowSize; j++) {
				int valueInThis = this->getElement(i, j);
				int valueInRightOperand = spMtrx.getElement(i, j);
				//cout << this->getElement(i, j) << " is value on " << i << " , " << j << "\n";
				
			
				if (valueInThis == 0) {
					this->addValue(valueInRightOperand,i,j);
				}
				else {
					int toAdd = valueInThis + valueInRightOperand;
					//cout << "for " << i << " , " << j << " pair sum is " << toAdd << "\n";
					if (toAdd == 0) {
						this->removeElement(i, j);
					}
					else {
						this->setElement(toAdd, i, j);
					}
				
				}
				
				
			}
		}
	}
	return *this;
}

SparseMatrix& SparseMatrix::operator-=(const SparseMatrix& spMtrx) {
	if (rowSize != spMtrx.rowSize || colSize != spMtrx.colSize) {
		throw exception("Error during addition, matrices have different dimensions\n");
	}
	else {
		for (int i = 0; i < colSize; i++) {
			for (int j = 0; j < rowSize; j++) {
			
				if (this->getElement(i, j) == 0) {
					//int add = spMtrx.getElement(i, j);
					this->addValue(-spMtrx.getElement(i, j), i, j);
				}
				else {
					int toAdd = this->getElement(i, j) - spMtrx.getElement(i, j);
					if (toAdd == 0) {
						this->removeElement(i, j);
					}
					else {
						this->setElement(toAdd, i, j);
					}

				}


			}
		}
	}
	return *this;
}

SparseMatrix& SparseMatrix::operator*=(const SparseMatrix& spMtrx) {
	if (rowSize != spMtrx.colSize) {
		throw exception("Error, Matrices can not be multiplied");
	}
	else {
		int counter = 0;
		SparseMatrix toReturn(colSize,spMtrx.rowSize);
			for (int i = 0; i < colSize; i++) {
				for (int j = 0; j < spMtrx.rowSize; j++) {
					for (int k = 0; k < rowSize; k++) {
						counter += getElement(i, k)*spMtrx.getElement(k, j);
					}
					toReturn.addValue(counter, j, i);
					counter = 0;
				}
			}
			*this = toReturn;
			return *this;
	}
}

void SparseMatrix::operator^(const int num) {
	for (int i = 0; i < colSize; i++) {
		for (int j = 0; j < rowSize; j++) {
			this->setElement(this->getElement(i, j)*num, i, j);
		}
	}
}

SparseMatrix SparseMatrix::operator!() {
	SparseMatrix toReturn(colSize, rowSize);
	for (int i = 0; i < colSize; i++) {
		for (int j = 0; j < rowSize; j++) {
			toReturn.addValue(this->getElement(i, j), j, i);
		}
	}
	return toReturn;
}

void SparseMatrix::removeElement(int row, int col) {
	Cell* prevCol = getPrevCol(row , col);
	Cell* prevRow = getPrevRow(row, col);
	Cell* toRemove = prevCol->nextCellCol;
	prevCol->nextCellCol = toRemove->nextCellCol;
	prevRow->nextCellRow = toRemove->nextCellRow;
	toRemove->nextCellCol = nullptr;
	toRemove->nextCellRow = nullptr;
	delete(toRemove);
}

void SparseMatrix::wrapper(int rowSize, int colSize) {
	this->rowSize = rowSize;
	this->colSize = colSize;
	cellPtr = new Cell;
	cellPtr->rowId = -1;
	cellPtr->colId = -1;
	int rowTracker = -1;
	int colTracker = -1;
	Cell* temp;
	temp = cellPtr;

	//initialize row of pointers to values
	for (int i = 0; i < rowSize; i++) {
		colTracker++;
		temp->nextCellRow = new Cell;
		temp->nextCellRow->rowId = rowTracker;
		temp->nextCellRow->colId = colTracker;
		temp->nextCellRow->nextCellCol = temp->nextCellRow;
		temp = temp->nextCellRow;

	}
	temp->nextCellRow = cellPtr;

	//moving temp pointer back to (0,0)
	temp = cellPtr;
	colTracker = -1;

	//initialize column of pointers to values
	for (int i = 0; i < colSize; i++) {
		rowTracker++;
		temp->nextCellCol = new Cell;
		temp->nextCellCol->rowId = rowTracker;
		temp->nextCellCol->colId = colTracker;
		temp->nextCellCol->nextCellRow = temp->nextCellCol;
		temp = temp->nextCellCol;
	}
	temp->nextCellCol = cellPtr;
}

bool operator==(SparseMatrix& mtrx1,SparseMatrix& mtrx2){
	
	if (mtrx1.getSizeCols() != mtrx2.getSizeCols() || mtrx1.getSizeRows() != mtrx2.getSizeRows()) {
		return false;
	}
	else {
		for (int i = 0; i < mtrx1.colSize; i++) {
			for (int j = 0; j < mtrx1.rowSize; j++) {
				if (mtrx1.getElement(i, j) != mtrx2.getElement(i, j)) {
					return false;
				}
			}
		}
		return true;
	}
}

SparseMatrix operator+(SparseMatrix & mtrx1, SparseMatrix & mtrx2) {
	if (mtrx1.colSize != mtrx2.colSize || mtrx1.rowSize != mtrx2.rowSize) {
		throw exception("Error while adding matrices, incompatible dimensions");
	}
	else {
		SparseMatrix toReturn(mtrx1.rowSize, mtrx1.colSize);
		for (int i = 0; i < mtrx1.colSize; i++) {
			for (int j = 0; j < mtrx1.rowSize; j++) {
				int toAdd = mtrx1.getElement(i, j) + mtrx2.getElement(i, j);
				toReturn.addValue(toAdd, i, j);
			}
		}
		
		return toReturn;
	}
}

SparseMatrix operator-(SparseMatrix & mtrx1, SparseMatrix & mtrx2){
	if (mtrx1.colSize != mtrx2.colSize || mtrx1.rowSize != mtrx2.rowSize) {
		throw exception("Error while adding matrices, incompatible dimensions");
	}
	else {
		SparseMatrix toReturn(mtrx1.rowSize, mtrx1.colSize);
		for (int i = 0; i < mtrx1.colSize; i++) {
			for (int j = 0; j < mtrx1.rowSize; j++) {
				int toAdd = mtrx1.getElement(i, j) - mtrx2.getElement(i, j);
				toReturn.addValue(toAdd, i, j);
			}
		}

		return toReturn;
	}
}

SparseMatrix operator*(SparseMatrix & mtrx1, SparseMatrix & mtrx2) {
	if (mtrx1.rowSize != mtrx2.colSize) {
		throw exception("Error, Matrices can not be multiplied");
	}
	else {
		int counter = 0;
		SparseMatrix toReturn(mtrx1.colSize, mtrx2.rowSize);
		for (int i = 0; i < mtrx1.colSize; i++) {
			for (int j = 0; j < mtrx2.rowSize; j++) {
				for (int k = 0; k < mtrx1.rowSize; k++) {
					counter += mtrx1.getElement(i, k)*mtrx2.getElement(k, j);
				}
				toReturn.addValue(counter, j, i);
				counter = 0;
			}
		}
		return toReturn;
	}
}

ostream & operator<<(ostream & os,const SparseMatrix & mtrx1){
	for (int i = 0; i < mtrx1.colSize; i++) {
		for (int j = 0; j < mtrx1.rowSize; j++) {
			os << mtrx1.getElement(i, j) << " is the value on position " << i << " , " << j << "\n\n";
		}
	}
	return os;
}

istream& operator>>(istream& is, SparseMatrix& mtrx1) {
	for (int i = 0; i < mtrx1.getSizeCols(); i++) {
		for (int j = 0; j < mtrx1.getSizeRows(); j++) {
			cout << "\nEnter integer value for position (" << i << " , " << j << " )\n";
			int value;
			is >> value;
			mtrx1.addValue(value, i, j);
		}
	}
	return is;
}


