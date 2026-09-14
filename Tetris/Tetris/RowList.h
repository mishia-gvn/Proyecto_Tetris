#pragma once
#include "Constants.h"

class RowList{
private:
	struct Row {
		int cells[BOARD_CELLS];
		Row* next;

		Row();
	};

	Row* head;
	int size;

public:
	RowList();
	~RowList();

	void clear();

	int getSize() const;

	int getCell(int row, int col) const;
	void setCell(int row, int col, int value);
};

