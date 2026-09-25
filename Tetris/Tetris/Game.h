#pragma once
#include "Board.h"
#include "Piece.h"
#include "Cola.h"
#include "ColaEvent.h"
#include "Pila.h"
#include "MovementList.h"
#include "GameRenderer.h"
#include "ScoreManager.h"

enum class GameState {
	MENU,
	PLAYING,
	PAUSED,
	GAME_OVER
};

class Game{
public:
	Game();
	~Game();

	void run();

private:

	sf::RenderWindow* window;
	sf::Clock pauseClock;
	sf::Font font1, font2;

	GameRenderer* renderer;

	Board board;

	Piece* currentPiece;

	Cola nextPieces;
	Pila holdPiece;

	MovementList movementHistory;
	ColaEvent eventHistory;

	GameState state;

	int score;
	string playerName;
	ScoreManager scoreManager;

	bool canHold;
	bool useHoldNext;

	sf::Clock fallClock;
	float fallInterval;
	int darkness;

	bool lineClearAnimating;
	sf::Clock lineClearClock;
	int pendingClearedRows;

	void processEvents();
	void handleMouseClick(const sf::Event::MouseButtonPressed& mousePressed);
	void render();

	void startGame();
	void resetGame();

	void spawnPiece();
	void lockPiece();
	
	void clearRows();

	void saveScore();

	void processEvent();
	void scheduleEvents();
	void handleKeyPress(const sf::Keyboard::Key key);

	void moveLeft();
	void moveRight();
	void moveDown();
	void hardDrop();
	void rotate();
	void hold();

	void handleTextEntered(const sf::Event::TextEntered& event);
};

