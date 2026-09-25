#include "Game.h"

Game::Game() {
	window = new sf::RenderWindow(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), TITLE);

	if (!font1.openFromFile("assets/font/ZalandoSans.ttf"))
		throw runtime_error("Failed to load font ZalandoSans.ttf");
	if (!font2.openFromFile("assets/font/HolyGolden.ttf"))
		throw runtime_error("Failed to load font HolyGolden.ttf");

	renderer = new GameRenderer(window, font1, font2);

	currentPiece = nullptr;
	
	state = GameState::MENU;
	
	score = 0;
	playerName = "";
	
	canHold = true;
	useHoldNext = false;
	
	fallInterval = FALL_INTERVAL;

	nextPieces.fillBag();
}

Game::~Game() {
	delete currentPiece;
	delete renderer;
	delete window;	
}

void Game::run() {
	while (window->isOpen()) {
		processEvents();
		if (state == GameState::PLAYING && fallClock.getElapsedTime().asSeconds() >= fallInterval) {
			moveDown();
			fallClock.restart();
		}
		render();
	}
}

void Game::processEvents() {

	while (const std::optional event = window->pollEvent()) {

		if (event->is<sf::Event::Closed>()) {
			window->close();
		}

		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			handleKeyPress(keyPressed->code);
		}

		if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			handleMouseClick(*mouseButtonPressed);
		}

		if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {
			handleTextEntered(*textEntered);
		}
	}
}

void Game::handleMouseClick(const sf::Event::MouseButtonPressed& mousePressed){
	if (mousePressed.button != sf::Mouse::Button::Left)
		return;

	sf::Vector2f mousePos(
		static_cast<float>(mousePressed.position.x),
		static_cast<float>(mousePressed.position.y));

	if (state == GameState::MENU) {
		if (renderer->playButton->isClicked(mousePos)) {
			if (!playerName.empty()) {
				startGame();
			}
		}
		else if (renderer->insertionSortButton->isClicked(mousePos)) {
			scoreManager.sortScores(false);
			renderer->setSortingText("Ordenado con: Insertion Sort", scoreManager);
		}
		else if (renderer->quickSortButton->isClicked(mousePos)) {
			scoreManager.sortScores(true);
			renderer->setSortingText("Ordenado con: Quick Sort", scoreManager);
		}
	}
	else if (state == GameState::PLAYING){
		if (renderer->pauseButton->isClicked(mousePos)){
			state = GameState::PAUSED;
		}
		else if (renderer->menuButton->isClicked(mousePos)){
			resetGame();
			state = GameState::MENU;
		}
	}
	else if (state == GameState::PAUSED)
	{
		if (renderer->resumeButton->isClicked(mousePos))
		{
			state = GameState::PLAYING;
			fallClock.restart();
		}
	}
	else if (state == GameState::GAME_OVER)
	{
		if (renderer->restartButton->isClicked(mousePos))
		{
			resetGame();
			startGame();
		}
		else if (renderer->gameOverMenuButton->isClicked(mousePos))
		{
			resetGame();
			state = GameState::MENU;
		}
	}
}

void Game::render(){
	window->clear();

	switch (state)
	{
	case GameState::MENU:
		renderer->drawMenu(playerName, scoreManager);
		break;

	case GameState::PLAYING:
		renderer->drawBoard(*window, board);
		renderer->drawPiece(*window, *currentPiece);
		renderer->drawHold(*window, holdPiece);
		renderer->drawNext(*window, nextPieces);
		renderer->drawPlayerInfo(*window, score, font1);
		break;

	case GameState::PAUSED:
		renderer->drawPaused();
		break;

	case GameState::GAME_OVER:
		renderer->drawGameOver(score, font1);
		break;
	}

	window->display();
}

void Game::startGame(){
	score = 0;
	canHold = true;
	useHoldNext = false;

	holdPiece.clear();

	spawnPiece();

	fallClock.restart();
}

void Game::resetGame(){
	board.reset();
	holdPiece.clear();
	movementHistory.clear();

	if (currentPiece != nullptr) {
		delete currentPiece;
		currentPiece = nullptr;
	}

	score = 0;
	canHold = true;
	useHoldNext = false;

	nextPieces.clear();
	nextPieces.fillBag();
}

void Game::spawnPiece() {
	if (useHoldNext && !holdPiece.isEmpty()) {
		currentPiece = holdPiece.pop();
		currentPiece->resetPosition();
		useHoldNext = false;

		if (board.gameOver(*currentPiece)) {
			state = GameState::GAME_OVER;
			saveScore();
		}
		else {
			state = GameState::PLAYING;
		}
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
				saveScore();
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

	if (clearedRows > 0){
		score += SCORE * clearedRows + MULTI_ROW_BONUS * (clearedRows - 1);
	}
}

void Game::saveScore(){
	scoreManager.addScore(playerName, score);
	scoreManager.save();
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

		if (nextPieces.getSize() <= 3)
			nextPieces.fillBag();

		if (currentPiece != nullptr && board.gameOver(*currentPiece)) {
			state = GameState::GAME_OVER;
		}
	}

	else {
		useHoldNext = true;
	}

	canHold = false;
}

void Game::handleTextEntered(const sf::Event::TextEntered& event){
	if (state != GameState::MENU) {
		return;
	}

	if (event.unicode == 8) {
		if (!playerName.empty()) {
			playerName.pop_back();
		}
		return;
	}

	if (event.unicode >= 32 && event.unicode <= 126) {
		if (playerName.length() < MAX_PLAYER_NAME) {
			playerName += static_cast<char>(event.unicode);
		}
	}
}


