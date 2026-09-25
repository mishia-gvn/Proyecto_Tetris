#pragma once
#include "Piece.h"
#include "RowList.h"

class Board{
private:
	RowList rows;

	bool isFull(int row) const;
	void removeRow(int row);

public:

	Board();

	void reset();

	bool canPlacePiece(const Piece& piece) const;
	void placePiece(const Piece& piece);

	int clear();
	
	int getCell(int row, int col) const;
	void setCell(int row, int col, int value);	

	bool gameOver(const Piece& piece) const;
};

