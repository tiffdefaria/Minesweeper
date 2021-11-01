#pragma once
#include "Tile.h"
#include "Random.h"

struct Board{
    int columns;
    int rows;
    int mines;
    int score;
    vector<Tile> tiles;
    Board();
    Board(int columns, int rows, int mines);
    void createTiles();
    void createMines();
    void Display(RenderWindow& window);
    void DebugMode();
    void EndGame();
    int getScore();
};