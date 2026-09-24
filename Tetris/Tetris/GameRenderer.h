#pragma once
#include "Button.h"
#include "GameText.h"
#include "Board.h"
#include "Pila.h"

class GameRenderer {
private:
	sf::Texture blockTexture[4];

public:
	GameRenderer();

	void drawBoard(sf::RenderTarget& target, const Board& board) const;
	void drawPiece(sf::RenderTarget& target, const Piece& piece) const;
	void drawHold(sf::RenderTarget& target, const Pila& holdPiece) const;
};