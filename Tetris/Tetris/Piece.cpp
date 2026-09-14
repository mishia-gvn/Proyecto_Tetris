#include "Piece.h"

Piece::Piece(Type type){
	this->type = type;
	
	x = 3;
	y = 0;

	rotation = 0;
}

//----------------------------------------------

Type Piece::getType() const
{
	return type;
}

//----------------------------------------------

int Piece::getX() const
{
	return x;
}

//----------------------------------------------

int Piece::getY() const
{
	return y;
}

//----------------------------------------------

int Piece::getRotation() const
{
	return rotation;
}

//----------------------------------------------

void Piece::rotate(){
	rotation++;

	if (rotation >= PIECE_ROTATIONS)
	{
		rotation = 0;
	}
}

//----------------------------------------------

Block Piece::getBlock(int index) const{
	Block block;

	block.x = PIECE_SHAPES[type][rotation][index][0];
	block.y = PIECE_SHAPES[type][rotation][index][1];

	return block;
}
