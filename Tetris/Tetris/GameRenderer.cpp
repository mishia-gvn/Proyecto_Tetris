#include "GameRenderer.h"

GameRenderer::GameRenderer(sf::RenderWindow* window, sf::Font& font1, sf::Font& font2) : window(window), font1(font1){
	for (int i = 0; i < 4; i++){
		blockTexture[i].loadFromFile(
			"assets/block/block_" + to_string(i + 1) + ".png");
	}

	// MENU PRINCIPAL
	titleText = new GameText(
		font1,
		"TETRIS",
		TEXT_BIG_SIZE,
		sf::Vector2f(BOARD_X_START + 100, 100),
		FONT_COLOR);

	sortingText = new GameText(
		font1,
		"",
		TEXT_NORMAL_SIZE,
		sf::Vector2f(600, 630),
		FONT_COLOR);

	playButton = new Button(
		font1,
		"JUGAR",
		sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Vector2f(BOARD_X_START + 125, 200),
		sf::Color(80, 80, 80),
		TEXT_NORMAL_SIZE);

	playerNameBox.setSize(sf::Vector2f(PLAYER_NAME_BOX_WIDTH, PLAYER_NAME_BOX_HEIGHT));
	playerNameBox.setPosition(sf::Vector2f(PLAYER_NAME_BOX_X, PLAYER_NAME_BOX_Y));

	playerNameBox.setFillColor(sf::Color(40, 40, 40));
	playerNameBox.setOutlineColor(sf::Color::White);
	playerNameBox.setOutlineThickness(2.f);

	insertionSortButton = new Button(
		font1, "INSERTION",
		sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Vector2f(600, 550),
		sf::Color(80, 80, 80), TEXT_NORMAL_SIZE);

	quickSortButton = new Button(
		font1, "QUICK SORT",
		sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Vector2f(770, 550),
		sf::Color(80, 80, 80), TEXT_NORMAL_SIZE);

	// PANTALLA DE JUEGO
	playerText = new GameText(
		font1,
		"Jugador: ",
		TEXT_NORMAL_SIZE,
		sf::Vector2f(PLAYER_INFO_X_START, PLAYER_INFO_Y_START),
		FONT_COLOR);

	menuButton = new Button(
		font1,
		"MENU",
		sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Vector2f(MENU_BUTTON_X, MENU_BUTTON_Y),
		sf::Color(80, 80, 80),
		TEXT_NORMAL_SIZE);

	pauseButton = new Button(
		font1,
		"PAUSA",
		sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Vector2f(PAUSE_BUTTON_X, PAUSE_BUTTON_Y),
		sf::Color(80, 80, 80),
		TEXT_NORMAL_SIZE);

	// PANTALLA DE PAUSA
	pauseText = new GameText(
		font1,
		"PAUSA",
		TEXT_BIG_SIZE,
		sf::Vector2f(BOARD_X_START + 100, 180),
		FONT_COLOR);

	resumeButton = new Button(
		font1,
		"CONTINUAR",
		sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Vector2f(BOARD_X_START + 100, 300),
		sf::Color(80, 80, 80),
		TEXT_NORMAL_SIZE);

	// PANTALLA DE GAME OVER
	gameOverText = new GameText(
		font1,
		"GAME OVER",
		TEXT_BIG_SIZE,
		sf::Vector2f(BOARD_X_START + 50, 180),
		FONT_COLOR);

	restartButton = new Button(
		font1,
		"JUGAR DE NUEVO",
		sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Vector2f(BOARD_X_START + 75, 300),
		sf::Color(80, 80, 80),
		TEXT_NORMAL_SIZE);

	gameOverMenuButton = new Button(
		font1,
		"MENU",
		sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Vector2f(BOARD_X_START + 75, 370),
		sf::Color(80, 80, 80),
		TEXT_NORMAL_SIZE);
}

GameRenderer::~GameRenderer(){
	delete titleText;
	delete sortingText;
	delete playButton;
	delete insertionSortButton;
	delete quickSortButton;

	delete playerText;
	delete menuButton;
	delete pauseButton;
	
	delete pauseText;
	delete resumeButton;

	delete gameOverText;
	delete restartButton;
	delete gameOverMenuButton;
}

void GameRenderer::drawBoard(sf::RenderTarget& target,
	const Board& board, int darkness,
	bool lineClearAnimating, float animationTime) const {

	for (int row = 0; row < BOARD_ROWS; row++) {
		for (int col = 0; col < BOARD_CELLS; col++) {

			sf::RectangleShape cell;

			cell.setSize(sf::Vector2f(
				BLOCK_SIDE_SIZE,
				BLOCK_SIDE_SIZE));

			cell.setPosition(sf::Vector2f(
				BOARD_X_START + col * CELL_SIDE_SIZE,
				BOARD_Y_START + row * CELL_SIDE_SIZE));

			cell.setFillColor(sf::Color::Black);
			cell.setOutlineColor(sf::Color(80, 80, 80));
			cell.setOutlineThickness(1.f);

			int cellValue = board.getCell(row, col);

			target.draw(cell);

			if (cellValue != 0) {

				int color = cellValue - 1;

				sf::Sprite blockSprite(blockTexture[color]);

				blockSprite.setColor(
					sf::Color(darkness, darkness, darkness));

				blockSprite.setPosition(sf::Vector2f(
					BOARD_X_START + col * CELL_SIDE_SIZE,
					BOARD_Y_START + row * CELL_SIDE_SIZE));

				blockSprite.setScale(sf::Vector2f(
					static_cast<float>(BLOCK_SIDE_SIZE) /
					blockTexture[color].getSize().x,

					static_cast<float>(BLOCK_SIDE_SIZE) /
					blockTexture[color].getSize().y));

				target.draw(blockSprite);

				// Detectar si la fila está completa
				bool fullRow = true;

				for (int c = 0; c < BOARD_CELLS; c++) {
					if (board.getCell(row, c) == 0) {
						fullRow = false;
						break;
					}
				}

				// Efecto de parpadeo
				if (lineClearAnimating && fullRow) {

					if (static_cast<int>(animationTime * 5) % 2 == 0) {

						sf::RectangleShape flash;

						flash.setSize(sf::Vector2f(
							BLOCK_SIDE_SIZE,
							BLOCK_SIDE_SIZE));

						flash.setPosition(sf::Vector2f(
							BOARD_X_START + col * CELL_SIDE_SIZE,
							BOARD_Y_START + row * CELL_SIDE_SIZE));

						flash.setFillColor(
							sf::Color(255, 255, 255, 220));

						target.draw(flash);
					}
				}
			}
		}
	}
}

void GameRenderer::drawPiece(sf::RenderTarget& target, const Piece& piece, int darkness) const {
	int color = piece.getColor();
	
	for (int i = 0; i < PIECE_BLOCKS; i++) {
		Block block = piece.getBlock(i);

		int blockX = piece.getX() + block.x;
		int blockY = piece.getY() + block.y;

		sf::Sprite blockSprite(blockTexture[color]);

		blockSprite.setColor(sf::Color(darkness, darkness, darkness));

		blockSprite.setPosition(sf::Vector2f(BOARD_X_START + blockX * CELL_SIDE_SIZE,
											 BOARD_Y_START + blockY * CELL_SIDE_SIZE));
		blockSprite.setScale(sf::Vector2f(
			static_cast<float>(BLOCK_SIDE_SIZE) / blockTexture[color].getSize().x,
			static_cast<float>(BLOCK_SIDE_SIZE) / blockTexture[color].getSize().y));
		
		target.draw(blockSprite);
	}
}

void GameRenderer::drawHold(sf::RenderTarget& target, const Pila& holdPiece, int darkness) const
{
	for (int row = 0; row < HOLD_ROWS; row++)
	{
		for (int col = 0; col < HOLD_CELLS; col++)
		{
			sf::RectangleShape cell;

			cell.setSize(sf::Vector2f(SECONDARY_BLOCK_SIZE, SECONDARY_BLOCK_SIZE));

			cell.setPosition(sf::Vector2f(
				HOLD_X_START + col * SECONDARY_CELL_SIZE,
				HOLD_Y_START + row * SECONDARY_CELL_SIZE));

			cell.setFillColor(sf::Color::Black);
			cell.setOutlineColor(sf::Color(80, 80, 80));
			cell.setOutlineThickness(1.f);

			target.draw(cell);
		}
	}

	Piece* piece = holdPiece.top();

	if (piece == nullptr)
		return;

	int color = piece->getColor();

	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		Block block = piece->getBlock(i);

		sf::Sprite blockSprite(blockTexture[color]);
		
		blockSprite.setColor(sf::Color(darkness, darkness, darkness));

		blockSprite.setPosition(sf::Vector2f(
			HOLD_X_START + block.x * SECONDARY_CELL_SIZE,
			HOLD_Y_START + block.y * SECONDARY_CELL_SIZE));

		blockSprite.setScale(sf::Vector2f(
			static_cast<float>(SECONDARY_BLOCK_SIZE) / blockTexture[color].getSize().x,
			static_cast<float>(SECONDARY_BLOCK_SIZE) /blockTexture[color].getSize().y));

		target.draw(blockSprite);
	}
}

void GameRenderer::drawNext(sf::RenderTarget& target, const Cola& nextPiece, int darkness) const{
	for (int row = 0; row < NEXT_ROWS; row++) {
		for (int col = 0; col < NEXT_CELLS; col++){
			sf::RectangleShape cell;

			cell.setSize(sf::Vector2f(SECONDARY_BLOCK_SIZE, SECONDARY_BLOCK_SIZE));

			cell.setPosition(sf::Vector2f(
				NEXT_X_START + col * SECONDARY_CELL_SIZE,
				NEXT_Y_START + row * SECONDARY_CELL_SIZE));

			cell.setFillColor(sf::Color::Black);
			cell.setOutlineColor(sf::Color(80, 80, 80));
			cell.setOutlineThickness(1.f);

			target.draw(cell);
		}
	}
	for (int i = 0; i < 3; i++) {
		Piece* piece = nextPiece.getAt(i);
		
		if (piece == nullptr)
			continue;

		int color = piece->getColor();

		for (int j = 0; j < PIECE_BLOCKS; j++) {
			Block block = piece->getBlock(j);

			sf::Sprite blockSprite(blockTexture[color]);

			blockSprite.setColor(sf::Color(darkness, darkness, darkness));

			blockSprite.setPosition(sf::Vector2f(
				NEXT_X_START + block.x * SECONDARY_CELL_SIZE,
				NEXT_Y_START + i * 5 * SECONDARY_CELL_SIZE + block.y * SECONDARY_CELL_SIZE));
			
			blockSprite.setScale(sf::Vector2f(
				static_cast<float>(SECONDARY_BLOCK_SIZE) / blockTexture[color].getSize().x,
				static_cast<float>(SECONDARY_BLOCK_SIZE) / blockTexture[color].getSize().y));
			target.draw(blockSprite);
		}
	}
}

void GameRenderer::drawPlayerInfo(
	sf::RenderTarget& target,
	const string& playerName,
	int score,
	sf::Font& font) const {

	GameText playerInfo(
		font,
		"Jugador: " + playerName,
		TEXT_NORMAL_SIZE,
		sf::Vector2f(PLAYER_INFO_X_START, PLAYER_INFO_Y_START),
		FONT_COLOR);

	playerInfo.draw(target);

	GameText scoreText(
		font,
		"Score: " + to_string(score),
		TEXT_NORMAL_SIZE,
		sf::Vector2f(PLAYER_INFO_X_START, SCORE_Y_START),
		FONT_COLOR);

	scoreText.draw(target);

	pauseButton->draw(target);
	menuButton->draw(target);
}

void GameRenderer::drawMenu(const string& playerName, const ScoreManager& scoreManager) const {
	titleText->draw(*window);

	sf::Text playerLabel(
		font1,
		"Jugador:",
		TEXT_NORMAL_SIZE);

	playerLabel.setFillColor(FONT_COLOR);

	playerLabel.setPosition(sf::Vector2f(PLAYER_NAME_BOX_X, PLAYER_NAME_LABEL_Y));

	window->draw(playerLabel);

	window->draw(playerNameBox);

	sf::Text playerNameText(
		font1,
		playerName,
	TEXT_NORMAL_SIZE);

	playerNameText.setFillColor(FONT_COLOR);

	playerNameText.setPosition(sf::Vector2f(
			PLAYER_NAME_BOX_X + PLAYER_NAME_TEXT_X_OFFSET,
			PLAYER_NAME_BOX_Y + PLAYER_NAME_TEXT_Y_OFFSET));

	window->draw(playerNameText);

	playButton->draw(*window);

	insertionSortButton->draw(*window);
	quickSortButton->draw(*window);
	sortingText->draw(*window);

	drawScores(scoreManager);
}

void GameRenderer::drawPaused() const{
	pauseText->draw(*window);
	resumeButton->draw(*window);
}

void GameRenderer::drawGameOver(int score, sf::Font& font) const{
	gameOverText->draw(*window);
	GameText scoreText(
		font, "Score: " + to_string(score), TEXT_NORMAL_SIZE,
		sf::Vector2f(BOARD_X_START + 100, 250), FONT_COLOR);
	scoreText.draw(*window);
	restartButton->draw(*window);
	gameOverMenuButton->draw(*window);
}

void GameRenderer::drawScores(const ScoreManager& scoreManager) const {
	GameText title(
		font1,
		"TOP 10",
		TEXT_NORMAL_SIZE,
		sf::Vector2f(200, 430),
		FONT_COLOR);

	title.draw(*window);
	
	for (int i = 0; i < scoreManager.getCount(); i++) {

		PlayersScore player = scoreManager.getScore(i);

		GameText scoreText(
			font1,
			to_string(i + 1) + ". " + player.name + " - " + to_string(player.score),
			TEXT_NORMAL_SIZE,
			sf::Vector2f(180, 480 + i * 40),
			FONT_COLOR);

		scoreText.draw(*window);
	}
}

void GameRenderer::setSortingText(const string& text, const ScoreManager& scoreManager){
	sortingText->setString(
		text + "\nComparaciones: " +
		to_string(scoreManager.getLastComparaciones()) +
		"\nMovimientos: " +
		to_string(scoreManager.getLastMovimientos())
	);
}
