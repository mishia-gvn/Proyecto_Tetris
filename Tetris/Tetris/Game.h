#pragma once
#include "Board.h"
#include "Piece.h"
#include "Cola.h"
#include "ColaEvent.h"
#include "Pila.h"
#include "MovementList.h"
#include "GameRenderer.h"

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

	GameRenderer renderer;

	Board board;

	Piece* currentPiece;

	Cola nextPieces;
	Pila holdPiece;

	MovementList movementHistory;
	ColaEvent eventHistory;

	GameState state;

	int score;
	bool canHold;

	void spawnPiece();
	void lockPiece();
	void clearRows();

	void processEvent();
	void handleKeyPress(const sf::Keyboard::Key key);

	void moveLeft();
	void moveRight();
	void moveDown();
	void hardDrop();
	void rotate();
	void hold();

};

