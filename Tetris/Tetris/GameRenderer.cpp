#include "GameRenderer.h"

GameRenderer::GameRenderer() {
	for (int i = 0; i < PIECE_BLOCKS; i++) {
		blockTexture[i].loadFromFile("assets/block/block_" + to_string(i+1) + ".png");
	}

}

void  GameRenderer::drawBoard(sf::RenderTarget& target, const Board& board) const {
	for (int row = 0; row < BOARD_ROWS; row++) {
		for (int col = 0; col < BOARD_CELLS; col++) {
			
			sf::RectangleShape cell;

			cell.setSize(sf::Vector2f(BLOCK_SIDE_SIZE, BLOCK_SIDE_SIZE));

			cell.setPosition(sf::Vector2f(BOARD_X_START + col * CELL_SIDE_SIZE,
										  BOARD_Y_START + row * CELL_SIDE_SIZE));

			if (board.getCell(row, col) != 0) {
				cell.setFillColor(sf::Color::White);
			}
			else {
				cell.setFillColor(sf::Color::Black);
			}

			cell.setOutlineColor(sf::Color(80, 80, 80));
			cell.setOutlineThickness(1.f);

			target.draw(cell);
		}
	}
}

void GameRenderer::drawPiece(sf::RenderTarget& target, const Piece& piece) const {
	int color = piece.getColor();
	
	for (int i = 0; i < PIECE_BLOCKS; i++) {
		Block block = piece.getBlock(i);

		int blockX = piece.getX() + block.x;
		int blockY = piece.getY() + block.y;

		sf::Sprite blockSprite(blockTexture[color]);
		blockSprite.setPosition(sf::Vector2f(BOARD_X_START + blockX * CELL_SIDE_SIZE,
											 BOARD_Y_START + blockY * CELL_SIDE_SIZE));
		blockSprite.setScale(sf::Vector2f(
			static_cast<float>(BLOCK_SIDE_SIZE) / blockTexture[color].getSize().x,
			static_cast<float>(BLOCK_SIDE_SIZE) / blockTexture[color].getSize().y));
		
		target.draw(blockSprite);
	}
}