#pragma once

enum Type { I, J, L, O, S, T, Z };

struct Block {
	int x;
	int y;
};

class Piece{
private:
	Type type;
	
	int x; 
	int y;

	int rotation;
	
public:
	Piece(Type type);

	Type getType() const;

	int getX() const;
	int getY() const;

	int getRotation() const;
	void rotate();

	Block getBlock(int index) const;
};

