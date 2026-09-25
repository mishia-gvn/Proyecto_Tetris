#pragma once
#include "Button.h"
#include "GameText.h"
#include "Board.h"
#include "Pila.h"
#include "Cola.h"
#include "ScoreManager.h"

class GameRenderer {
private:
	sf::Texture blockTexture[4];
	sf::RenderWindow* window;
	sf::Font& font1;
	sf::RectangleShape playerNameBox;

public:
	GameText* titleText;
	GameText* sortingText;
	Button* playButton;
	Button* insertionSortButton;
	Button* quickSortButton;
	
	Button* pauseButton;
	Button* resumeButton;
	GameText* pauseText;

	Button* menuButton;
	GameText* playerText;

	GameText* gameOverText;
	Button* restartButton;
	Button* gameOverMenuButton;

	GameRenderer(sf::RenderWindow* window, sf::Font& font1, sf::Font& font2);

	~GameRenderer();

	void drawBoard(sf::RenderTarget& target, const Board& board, int darkness, bool lineClearAnimating, float animationTime) const;
	void drawPiece(sf::RenderTarget& target, const Piece& piece, int darkness) const;
	void drawHold(sf::RenderTarget& target, const Pila& holdPiece, int darkness) const;
	void drawNext(sf::RenderTarget& target, const Cola& nextPiece, int darkness) const;

	void drawPlayerInfo(sf::RenderTarget& target, int score, sf::Font& font) const;

	void drawMenu(const string& playerName, const ScoreManager& scoreManager) const;
	void drawPaused() const;
	void drawGameOver(int score, sf::Font& font) const;

	void drawScores(const ScoreManager& scoreManager) const;
	void setSortingText(const string& text, const ScoreManager& scoreManager);
};