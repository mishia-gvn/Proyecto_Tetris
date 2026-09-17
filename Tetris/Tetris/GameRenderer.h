#pragma once
#include "Button.h"
#include "GameText.h"
#include "Board.h"

class GameRenderer {
private:
	sf::Texture blockTexture[4];

public:
	GameRenderer();

	void drawBoard(sf::RenderTarget& target, const Board& board) const;
	void  drawPiece(sf::RenderTarget& target, const Piece& piece) const;
};