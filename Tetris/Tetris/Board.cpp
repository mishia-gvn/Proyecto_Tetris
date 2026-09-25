#include "Board.h"

Board::Board(){}

void Board::reset(){
	for (int row = 0; row < BOARD_ROWS; row++)
	{
		for (int column = 0; column < BOARD_CELLS; column++)
		{
			rows.setCell(row, column, 0);
		}
	}
}

bool Board::canPlacePiece(const Piece& piece) const{
	for (int i = 0; i < PIECE_BLOCKS;i++) {
		Block block = piece.getBlock(i);
		
		int boardX = piece.getX() + block.x;
		int boardY = piece.getY() + block.y;

		if (boardX < 0 || boardX >= BOARD_CELLS)
			return false;

		if (boardY < 0 || boardY >= BOARD_ROWS)
			return false;

		if (rows.getCell(boardY, boardX) != 0)
			return false;
	}
	
	return true;
}

void Board::placePiece(const Piece& piece){
	int color = piece.getColor() + 1;

	for (int i = 0; i < PIECE_BLOCKS;i++) {
		Block block = piece.getBlock(i);

		int boardX = piece.getX() + block.x;
		int boardY = piece.getY() + block.y;

		rows.setCell(boardY, boardX, color);
	}
}

bool Board::isFull(int row) const{
	for (int column = 0; column < BOARD_CELLS; column++) {
		if (rows.getCell(row, column) == 0) {
			return false;
		}
	}
	return true;
}

void Board::removeRow(int row){
	rows.removeRow(row);
}

int Board::clear(){
	int clearRow = 0;
	int row = BOARD_ROWS - 1;

	while(row >= 0) {
		if (isFull(row)) {
			removeRow(row);
			clearRow++;
		}
		else {
			row--;
		}
	}
	return clearRow;
}

int Board::getCell(int row, int col) const{
	return rows.getCell(row, col);
}

void Board::setCell(int row, int col, int value){
	rows.setCell(row, col, value);
}

bool Board::gameOver(const Piece& piece) const{
	return !canPlacePiece(piece);
}

