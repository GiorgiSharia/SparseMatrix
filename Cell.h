#pragma once
//#include "SparseMatrix.h"
class Cell {
public:
	Cell();
private:
	
	Cell* nextCellRow;
	Cell* nextCellCol;
	//Cell* prevCellRow;
	//Cell* prevCellCol;
	int value;
	int rowId;
	int colId;
	void setRowId(const int row);
	void setColId(const int col);
	void setValue(const double& val);
	friend class SparseMatrix;
};