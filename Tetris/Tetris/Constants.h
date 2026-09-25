#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

// INTERFAZ
constexpr int WINDOW_WIDTH = 1000;
constexpr int WINDOW_HEIGHT = 960;

constexpr float FALL_INTERVAL = 0.8f;
const float SPEED_UP_INTERVAL = 1000.0f;
const float MIN_FALL_INTERVAL = 0.10f;

const string TITLE = "Tetris";

// TABLERO
constexpr int BOARD_ROWS = 20;
constexpr int BOARD_CELLS = 10;

constexpr int BLOCK_SIDE_SIZE = 46;
constexpr int CELL_SIDE_SIZE = 46;
constexpr int BOARD_X_START = 40;
constexpr int BOARD_Y_START = 30;

// TABLEROS SECUNDARIOS
constexpr int SECONDARY_BLOCK_SIZE = 30;
constexpr int SECONDARY_CELL_SIZE = 30;

// TABLERO HOLD
constexpr int HOLD_CELLS = 4;
constexpr int HOLD_ROWS = 4;

constexpr int HOLD_X_START = 550;
constexpr int HOLD_Y_START = 100;

// TABLERO NEXT
constexpr int NEXT_CELLS = 4;
constexpr int NEXT_ROWS = 14;

constexpr int NEXT_X_START = 550;
constexpr int NEXT_Y_START = 304;

// PUNTAJES
constexpr int SCORE = 100;
constexpr int MULTI_ROW_BONUS = 200;
constexpr int SCORE_Y_START = 250;

constexpr int MAX_SCORES = 10;
const string SCORE_FILE = "scores.txt";

// BOTONES
constexpr int BUTTON_WIDTH = 150;
constexpr int BUTTON_HEIGHT = 50;

// TEXTO
constexpr int TEXT_NORMAL_SIZE = 24;
constexpr int TEXT_BIG_SIZE = 51;
const sf::Color FONT_COLOR = sf::Color::White;
const sf::Color FONT_COLOR2 = sf::Color::Blue;

// INFORMACION DE JUGADOR
constexpr int PLAYER_NAME_BOX_WIDTH = 300;
constexpr int PLAYER_NAME_BOX_HEIGHT = 45;
constexpr int PLAYER_NAME_BOX_Y = 210;
constexpr int PLAYER_NAME_BOX_X = 650;

constexpr int PLAYER_NAME_TEXT_X_OFFSET = 10;
constexpr int PLAYER_NAME_TEXT_Y_OFFSET = 5;

constexpr int PLAYER_NAME_LABEL_Y = 150;

constexpr int MAX_PLAYER_NAME = 15;

constexpr int PLAYER_INFO_X_START = 760;
constexpr int PLAYER_INFO_Y_START = 140;

constexpr int PAUSE_BUTTON_X = 760;
constexpr int PAUSE_BUTTON_Y = 330;

constexpr int MENU_BUTTON_X = 760;
constexpr int MENU_BUTTON_Y = 400;

// PIEZAS
constexpr int PIECE_TYPES = 7;
constexpr int PIECE_ROTATIONS = 4;
constexpr int PIECE_BLOCKS = 4;

// TIPOS DE PIEZAS
const int PIECE_I = 0;
const int PIECE_O = 1;
const int PIECE_T = 2;
const int PIECE_J = 3;
const int PIECE_L = 4;
const int PIECE_S = 5;
const int PIECE_Z = 6;

// ROTACIONES DE PIEZAS
const int PIECE_SHAPES[PIECE_TYPES][PIECE_ROTATIONS][PIECE_BLOCKS][2] = {
    // --------------------------
    // I
    {
        {
            {1, 0},
            {1, 1},
            {1, 2},
            {1, 3}
        },
        {
            {0, 1},
            {1, 1},
            {2, 1},
            {3, 1}
        },
        {
            {1, 0},
            {1, 1},
            {1, 2},
            {1, 3}
        },
        {
            {0, 1},
            {1, 1},
            {2, 1},
            {3, 1}
        }
    },
    
    // --------------------------
    // O
    {
        {
            {1, 0},
            {2, 0},
            {1, 1},
            {2, 1}
        },
        {
            {1, 0},
            {2, 0},
            {1, 1},
            {2, 1}
        },
        {
            {1, 0},
            {2, 0},
            {1, 1},
            {2, 1}
        },
        {
            {1, 0},
            {2, 0},
            {1, 1},
            {2, 1}
        }
    },

    // --------------------------
    // T
    {
        {
            {1, 0},
            {0, 1},
            {1, 1},
            {2, 1}
        },
        {
            {1, 0},
            {1, 1},
            {2, 1},
            {1, 2}
        },
        {
            {0, 1},
            {1, 1},
            {2, 1},
            {1, 2}
        },
        {
            {1, 0},
            {0, 1},
            {1, 1},
            {1, 2}
        }
    },    
    
    // --------------------------
    // J
    {
        {
            {0, 0},
            {0, 1},
            {1, 1},
            {2, 1}
        },
        {
            {1, 0},
            {2, 0},
            {1, 1},
            {1, 2}
        },
        {
            {0, 1},
            {1, 1},
            {2, 1},
            {2, 2}
        },
        {
            {1, 0},
            {1, 1},
            {0, 2},
            {1, 2}
        }
    },

    // --------------------------
    // L
    {
        {
            {2, 0},
            {0, 1},
            {1, 1},
            {2, 1}
        },
        {
            {1, 0},
            {1, 1},
            {1, 2},
            {2, 2}
        },
        {
            {0, 1},
            {1, 1},
            {2, 1},
            {0, 2}
        },
        {
            {0, 0},
            {1, 0},
            {1, 1},
            {1, 2}
        }
    },

    // --------------------------
 // S
    {
        {
            {1, 0},
            {2, 0},
            {0, 1},
            {1, 1}
        },
        {
            {0, 0},
            {0, 1},
            {1, 1},
            {1, 2}
        },
        {
            {1, 0},
            {2, 0},
            {0, 1},
            {1, 1}
        },
        {
            {0, 0},
            {0, 1},
            {1, 1},
            {1, 2}
        }
    },

    // --------------------------
    // Z
    {
        {
            {0, 0},
            {1, 0},
            {1, 1},
            {2, 1}
        },
        {
            {1, 0},
            {0, 1},
            {1, 1},
            {0, 2}
        },
        {
            {0, 0},
            {1, 0},
            {1, 1},
            {2, 1}
        },
        {
            {1, 0},
            {0, 1},
            {1, 1},
            {0, 2}
        }
    }
};

