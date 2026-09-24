#include "Game.h"

Game::Game() {
	window = new sf::RenderWindow(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), TITLE);


	currentPiece = nullptr;
	state = GameState::MENU;
	score = 0;
	canHold = true;
	useHoldNext = false;
	fallInterval = 0.8f;

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
			if (event->is<sf::Event::KeyPressed>()) {
				auto keyPressed = event->getIf<sf::Event::KeyPressed>();

				if (keyPressed != nullptr) {
					handleKeyPress(keyPressed->code);
				}
			}
		}

		if (state == GameState::PLAYING && fallClock.getElapsedTime().asSeconds() >= fallInterval) {
				moveDown();
				fallClock.restart();
		}

		window->clear();

		renderer.drawBoard(*window, board);
		renderer.drawPiece(*window, *currentPiece);

		window->display();
		
	}
}

void Game::spawnPiece() {
	if (useHoldNext && !holdPiece.isEmpty()) {
		currentPiece = holdPiece.pop();
		currentPiece->resetPosition();
		useHoldNext = false;
	}
	else {
		if (nextPieces.getSize() <= 3) {
			nextPieces.fillBag();
		}
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
	if (state != GameState::PLAYING) {
		return;
	}
	switch (key) {
	case sf::Keyboard::Key::Left:
		moveLeft();
		break;

	case sf::Keyboard::Key::Right:
		moveRight();
		break;

	case sf::Keyboard::Key::Down:
		moveDown();
		break;
	
	case sf::Keyboard::Key::Up:	
		rotate();
		break;

	case sf::Keyboard::Key::Space:
		hardDrop();
		break;

	case sf::Keyboard::Key::H:
		hold();
		break;

	default:
		break;
	}
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

		if (nextPieces.getSize() <= 3) {
			nextPieces.fillBag();
		}
	}

	else {
		useHoldNext = true;
	}

	canHold = false;
}


