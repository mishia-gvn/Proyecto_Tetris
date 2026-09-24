#include "Piece.h"

Piece::Piece(int type){
	this->type = type;
	color = rand() % 4;
	
	x = 3;
	y = 0;

	rotation = 0;
}

int Piece::getType() const{
	return type;
}

int Piece::getColor() const {
	return color;
}

int Piece::getX() const{
	return x;
}

int Piece::getY() const{
	return y;
}

void Piece::moveLeft() {
	x--;
}

void Piece::moveRight() {
	x++;
}

void Piece::moveDown() {
	y++;
}

void Piece::moveUp() {
	y--;
}

void Piece::moveTo(int y) {
	this->y = y;
}

void Piece::resetPosition(){
	x = 3;
	y = 0;
	rotation = 0;
}

void Piece::rotate(){
	rotation++;

	if (rotation >= PIECE_ROTATIONS)
	{
		rotation = 0;
	}
}

void Piece::setRotation(int rotation) {
	this->rotation = rotation;
}

int Piece::getRotation() const{
	return rotation;
}

Block Piece::getBlock(int index) const{
	Block block;

	block.x = PIECE_SHAPES[type][rotation][index][0];
	block.y = PIECE_SHAPES[type][rotation][index][1];

	return block;
}

