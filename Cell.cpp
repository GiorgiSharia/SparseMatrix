#include "Cell.h"
#include <iostream>
Cell::Cell() {
	nextCellCol = nullptr;
	nextCellRow = nullptr;
	rowId = NULL;
	colId = NULL;
	value = NULL;
	
}

void Cell::setRowId(const int row) {
	rowId = row;
}
void Cell::setColId(const int col) {
	colId = col;
}
void Cell::setValue(const double& val) {
	value = val;
}