#include "Game.h"

Game::Game() {
	window = new sf::RenderWindow(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), TITLE);


	currentPiece = nullptr;
	state = GameState::MENU;
	score = 0;
	canHold = true;

	nextPieces.fillBag();

	spawnPiece();
}

Game::~Game() {
	delete currentPiece;
}

void Game::run() {
	while (window->isOpen()) {
		while (auto event = window->pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window->close();
			}
		}

		window->clear();
		renderer.drawBoard(*window, board);
		renderer.drawPiece(*window, *currentPiece);
		window->display();
		
	}
}

void Game::spawnPiece() {
	if (nextPieces.getSize() <= 3) {
		nextPieces.fillBag();
	}
	delete currentPiece;
	currentPiece = nextPieces.dequeue();

	if (currentPiece != nullptr) {
		canHold = true;
		
		if (board.gameOver(*currentPiece)) {
			state = GameState::GAME_OVER;
		}
		else {
			state = GameState::PLAYING;
		}
	}
}

void Game::lockPiece() {
	board.placePiece(*currentPiece);

	delete currentPiece;
	currentPiece = nullptr;

	clearRows();
	spawnPiece();
}

void Game::clearRows() {
	int clearedRows = board.clear();
	score += clearedRows * SCORE;
}

void Game::processEvent(){
}

void Game::handleKeyPress(const sf::Keyboard::Key key){
}

void Game::moveLeft(){
	currentPiece->moveLeft();

	if (!board.canPlacePiece(*currentPiece)) {
		currentPiece->moveRight();
	}
}

void Game::moveRight(){
	currentPiece->moveRight();

	if (!board.canPlacePiece(*currentPiece)) {
		currentPiece->moveLeft();
	}
}

void Game::moveDown(){
	currentPiece->moveDown();

	if (!board.canPlacePiece(*currentPiece)) {
		currentPiece->moveUp();
		lockPiece();
	}
}

void Game::hardDrop(){
	while (true) {
		currentPiece->moveDown();
		if (!board.canPlacePiece(*currentPiece)) {
			currentPiece->moveUp();
			break;
		}
	}
	lockPiece();
}

void Game::rotate(){
	int oldRotation = currentPiece->getRotation();

	currentPiece->rotate();

	if (!board.canPlacePiece(*currentPiece)) {
		currentPiece->setRotation(oldRotation);
	}
}

void Game::hold(){
	if (currentPiece == nullptr || !canHold) {
		return;
	}

	if (holdPiece.isEmpty()) {
		holdPiece.push(currentPiece);
		currentPiece = nextPieces.dequeue();
	}
	else {
		Piece* temp = holdPiece.pop();
		holdPiece.push(currentPiece);
		currentPiece = temp;
	}
	canHold = false;
}


