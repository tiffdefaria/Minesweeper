#include "Board.h"
#include <SFML/Graphics.hpp>
#include "TextureManager.h"


Board::Board(){
    columns = 0;
    rows = 0;
    mines = 0;
    score = 0;
}

Board::Board(int columns, int rows, int mines) {
    this->columns = columns;
    this->rows = rows;
    this->mines = mines;
}

void Board::createTiles() {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            Tile newTile;
            newTile.positionx = j * 32;
            newTile.positiony = i * 32;
            tiles.push_back(newTile);
        }
    }

    for(int i = 0; i < columns; i++) {
        for(int j = 0; j < rows; j++) {
            if(j == 0 && i == columns-1){ //top right
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[((columns*j) + i) - 1]); //left
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j+1)) + (i - 1)]); //bottom left
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j+1)) + i]); //below
            }
            else if(j == 0 && i == 0){ //top left
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[((columns*j) + i) + 1]); //right
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j+1)) + (i + 1)]); //bottom right
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j+1)) + i]); //below
            }
            else if(j == rows-1 && i == 0){ //bottom left
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j-1)) + i]); //above
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[((columns*j) + i) + 1]); //right
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j-1)) + (i + 1)]); //top right
            }
            else if(j == rows-1 && i == columns-1){
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j-1)) + i]); //above
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[((columns*j) + i) - 1]); //left
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j-1)) + (i - 1)]); //top left
            }
            else if(j == 0){ //top row
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[((columns*j) + i) + 1]); //right
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[((columns*j) + i) - 1]); //left
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j+1)) + i]); //below
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j+1)) + (i - 1)]); //bottom left
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j+1)) + (i + 1)]); //bottom right
            }
            else if(j == rows -1){ //bottom row
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j-1)) + i]); //above
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[((columns*j) + i) + 1]); //right
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[((columns*j) + i) - 1]); //left
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j-1)) + (i - 1)]); //top left
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j-1)) + (i + 1)]); //top right
            }
            else if(i == 0){ //left column
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[((columns*j) + i) + 1]); //right
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j+1)) + i]); //below
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j-1)) + i]); //above
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j-1)) + (i + 1)]); //top right
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j+1)) + (i + 1)]); //bottom right
            }
            else if(i == columns -1){ //right column
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[((columns*j) + i) - 1]); //left
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j+1)) + i]); //below
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j-1)) + i]); //above
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j-1)) + (i - 1)]); //top left
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[(columns*(j+1)) + (i - 1)]); //bottom left
            }else {
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[((columns*j) + i) + 1]); //right
                tiles[(columns*j) + i].adjacentTiles.push_back(&tiles[((columns*j) + i) - 1]); //left
                tiles[(columns * j) + i].adjacentTiles.push_back(&tiles[(columns * (j + 1)) + i]); //below
                tiles[(columns * j) + i].adjacentTiles.push_back(&tiles[(columns * (j - 1)) + i]); //above
                tiles[(columns * j) + i].adjacentTiles.push_back(&tiles[(columns * (j - 1)) + (i - 1)]); //top left
                tiles[(columns * j) + i].adjacentTiles.push_back(&tiles[(columns * (j - 1)) + (i + 1)]); //top right
                tiles[(columns * j) + i].adjacentTiles.push_back(&tiles[(columns * (j + 1)) + (i - 1)]); //bottom left
                tiles[(columns * j) + i].adjacentTiles.push_back(&tiles[(columns * (j + 1)) + (i + 1)]); //bottom right
            }
        }
    }
}

void Board::Display(RenderWindow& window) {
    for(int i = 0; i < tiles.size(); i++){
        tiles[i].Render(window);
    }
}

void Board::createMines() {
    for(int i = 0; i < mines; i++){
        int num = Random::Int(0, tiles.size());
        if(!tiles[num].isMine){
            tiles[num].isMine = true;
        }else{
            i--;
        }
    }
}


void Board::DebugMode() {
    for(int i = 0; i < tiles.size(); i++) {
        tiles[i].debugMode = !tiles[i].debugMode;
    }
}

void Board::EndGame() {
    for(int i = 0; i < tiles.size(); i++) {
        tiles[i].debugMode = true;
    }
}

int Board::getScore() {
    int numFlagged = 0;
    for(int i = 0; i < tiles.size(); i++){
        if(tiles[i].isFlagged){
            numFlagged++;
        }
        score = mines - numFlagged;
    }
    return score;
}




