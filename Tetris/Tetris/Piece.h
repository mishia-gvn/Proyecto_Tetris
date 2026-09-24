#pragma once
#include "Constants.h"

struct Block {
	int x;
	int y;
};

class Piece{
private:
	int type;
	int color;
	
	int x; 
	int y;

	int rotation;
	
public:
	Piece(int type);

	int getType() const;
	int getColor() const;

	int getX() const;
	int getY() const;

	void moveLeft();
	void moveRight();
	void moveDown();
	void moveUp();
	void moveTo(int y);
	void resetPosition();

	void rotate();
	void setRotation(int rotation);
	int getRotation() const;

	Block getBlock(int index) const;
};

