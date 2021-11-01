#pragma once
#include <SFML/Graphics.hpp>
#include "Random.h"
#include <string>
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;


struct Tile {
    vector<Tile*> adjacentTiles;
    Sprite hiddenTile;
    Sprite revealedTile;
    Sprite flag;
    Sprite mine;
    Sprite num1;
    Sprite num2;
    Sprite num3;
    Sprite num4;
    Sprite num5;
    Sprite num6;
    Sprite num7;
    Sprite num8;
    bool isRevealed;
    bool isFlagged;
    bool isMine;
    bool debugMode;
    int positionx;
    int positiony;
    Tile();
    void Render(RenderWindow& window);
    void RevealTile();
    FloatRect GetSpriteRect();
};
