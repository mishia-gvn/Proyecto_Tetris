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
constexpr int WINDOW_HEIGHT = 1100;

constexpr int FPS = 60;
constexpr float FRAME_TIME = 1.f / FPS;

constexpr float BLOCK_FALL_SPEED = 200.f;
constexpr float BLOCK_MOVE_SPEED = 300.f;

const string TITLE = "Tetris";

// BOTONES
constexpr int BUTTON_WIDTH = 150;
constexpr int BUTTON_HEIGHT = 50;

// TEXTO
constexpr int TEXT_NORMAL_SIZE = 24;
constexpr int TEXT_BIG_SIZE = 51;
const sf::Color FONT_COLOR = sf::Color::White;
const sf::Color FONT_COLOR2 = sf::Color::Blue;

// PIEZAS
constexpr int PIECE_TYPES = 7;
constexpr int PIECE_ROTATIONS = 4;
constexpr int PIECE_BLOCKS = 4;

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


// TABLERO
constexpr int BOARD_ROWS = 20;
constexpr int BOARD_CELLS = 10;

constexpr int BLOCK_SIDE_SIZE = 45;
constexpr int CELL_SIDE_SIZE = 50;
constexpr int BOARD_X_START = 350;
constexpr int BOARD_Y_START = 160;
constexpr int BOARD_X_END = BOARD_X_START + BOARD_CELLS * CELL_SIDE_SIZE;
constexpr int BOARD_Y_END = BOARD_Y_START + BOARD_ROWS * CELL_SIDE_SIZE;

// PUNTAJES
constexpr int COMBO_SCORE = 10;
