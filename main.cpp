#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Board.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
using namespace sf;

void Read(string directory, Board& board){
    ifstream myFile;
    myFile.open(directory);
    if (myFile.is_open()){
        string line;
        getline(myFile, line); //Columns
        int columns = stoi(line);
        getline(myFile, line); //Rows
        int rows = stoi(line);
        getline(myFile, line); //Mines
        int mines = stoi(line);
        Board gameboard(columns, rows, mines);
        board = gameboard;
    }else{
        cout << "Couldn't open the file." << endl;
    }
}

void ReadTestBoard(string directory, Board& board) {
    ifstream myFile;
    myFile.open(directory);
    if (myFile.is_open()) {
        string line;
        int index = 0;
        board.mines = 0;
        while (getline(myFile, line)) {
            istringstream stream(line);
            string token;
            getline(stream, token);
            char* array = new char[line.length() + 1];
            strcpy (array, line.c_str());
            for(int i = 0; i < line.length(); i++){
                if(array[i] == '1'){
                    board.mines++;
                    board.tiles[index].isMine = true;
                }
                index++;
            }
        }
    }
}

int main()
{
    Board gameboard;

    Read("./boards/config.cfg", gameboard);
    int width = (gameboard.columns) * 32;
    int height = ((gameboard.rows) * 32) + 88;
    RenderWindow window(VideoMode(width, height), "Minesweeper");

    Sprite smile(TextureManager::GetTexture("face_happy"));
    Sprite test1(TextureManager::GetTexture("test_1"));
    Sprite test2(TextureManager::GetTexture("test_2"));
    Sprite test3(TextureManager::GetTexture("test_3"));
    Sprite debug(TextureManager::GetTexture("debug"));
    Sprite scoreboard1(TextureManager::GetTexture("digits"));
    Sprite scoreboard10(TextureManager::GetTexture("digits"));
    Sprite scoreboard100(TextureManager::GetTexture("digits"));
    Sprite scoreboardNeg(TextureManager::GetTexture("digits"));

    bool gameOver = false;

    gameboard.createTiles();
    gameboard.createMines();

    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
            else if(event.type == Event::MouseButtonPressed){
                //Left click
                if(event.mouseButton.button == Mouse::Left){
                    Vector2i position = Mouse::getPosition(window);
                    if(!gameOver) {
                        for (int i = 0; i < gameboard.tiles.size(); i++) {
                            if (gameboard.tiles[i].GetSpriteRect().contains(position.x, position.y)) {
                                gameboard.tiles[i].RevealTile();
                                if (gameboard.tiles[i].isMine && !gameboard.tiles[i].isFlagged) {
                                    gameOver = true;
                                    gameboard.EndGame();
                                    smile.setTexture(TextureManager::GetTexture("face_lose"));
                                }
                                else {
                                    int totalRevealed = 0;
                                    for(int i = 0; i < gameboard.tiles.size(); i++) {
                                        if(gameboard.tiles[i].isRevealed){
                                            totalRevealed++;
                                        }
                                    }
                                    if(totalRevealed == gameboard.columns * gameboard.rows - gameboard.mines){
                                        gameOver = true;
                                        for(int i = 0; i < gameboard.tiles.size(); i++){
                                            if(gameboard.tiles[i].isMine){
                                                gameboard.tiles[i].isFlagged = true;
                                            }
                                        }
                                        smile.setTexture(TextureManager::GetTexture("face_win"));
                                    }
                                }
                            }
                        }
                    }
                    if(debug.getGlobalBounds().contains(position.x, position.y) && !gameOver){
                        gameboard.DebugMode();
                    }
                    if(smile.getGlobalBounds().contains(position.x, position.y)){
                        gameOver = false;
                        Read("./boards/config.cfg", gameboard);
                        gameboard.tiles.clear();
                        gameboard.createTiles();
                        gameboard.createMines();
                        smile.setTexture(TextureManager::GetTexture("face_happy"));
                    }
                    if(test1.getGlobalBounds().contains(position.x, position.y)){
                        gameOver = false;
                        gameboard.tiles.clear();
                        gameboard.createTiles();
                        ReadTestBoard("./boards/testboard1.brd", gameboard);
                        smile.setTexture(TextureManager::GetTexture("face_happy"));
                    }
                    if(test2.getGlobalBounds().contains(position.x, position.y)){
                        gameOver = false;
                        gameboard.tiles.clear();
                        gameboard.createTiles();
                        ReadTestBoard("./boards/testboard2.brd", gameboard);
                        smile.setTexture(TextureManager::GetTexture("face_happy"));
                    }
                    if(test3.getGlobalBounds().contains(position.x, position.y)){
                        gameOver = false;
                        gameboard.tiles.clear();
                        gameboard.createTiles();
                        ReadTestBoard("./boards/testboard3.brd", gameboard);
                        smile.setTexture(TextureManager::GetTexture("face_happy"));
                    }
                }
                //Right click
                if(event.mouseButton.button == Mouse::Right){
                    if(!gameOver) {
                        Vector2i position = Mouse::getPosition(window);
                        for (int i = 0; i < gameboard.tiles.size(); i++) {
                            if (gameboard.tiles[i].GetSpriteRect().contains(position.x, position.y)) {
                                gameboard.tiles[i].isFlagged = !gameboard.tiles[i].isFlagged;
                            }
                        }
                    }
                }
            }
        }
        window.clear();
        gameboard.Display(window);

        //smiley face
        smile.setPosition((gameboard.columns / 2) * 32, gameboard.rows * 32);
        window.draw(smile);
        //testing buttons
        test1.setPosition((gameboard.columns * 32) - (test3.getGlobalBounds().width + test2.getGlobalBounds().width + test1.getGlobalBounds().width),gameboard.rows * 32);
        window.draw(test1);
        test2.setPosition((gameboard.columns * 32) - (test3.getGlobalBounds().width + test2.getGlobalBounds().width),gameboard.rows * 32);
        window.draw(test2);
        test3.setPosition((gameboard.columns * 32) - test3.getGlobalBounds().width,gameboard.rows * 32);
        window.draw(test3);
        //mine toggle
        debug.setPosition((gameboard.columns * 32) - (test3.getGlobalBounds().width + test2.getGlobalBounds().width + test1.getGlobalBounds().width + debug.getGlobalBounds().width),gameboard.rows * 32);
        window.draw(debug);
        //scoreboard
        int scoreNum = gameboard.getScore();
        bool isNeg = false;
        if(scoreNum < 0) {
            isNeg = true;
            scoreNum *= -1;
        }
        int onesDigit = scoreNum % 10;
        int tensDigit = (scoreNum / 10) % 10;
        int hundsDigit = (scoreNum / 100) % 10;

        scoreboard1.setTextureRect(IntRect(onesDigit*21, 0, 21, 32));
        scoreboard10.setTextureRect(IntRect(tensDigit*21, 0, 21, 32));
        scoreboard100.setTextureRect(IntRect(hundsDigit*21, 0, 21, 32));
        scoreboard1.setPosition(63, gameboard.rows*32);
        scoreboard10.setPosition(42, gameboard.rows*32);
        scoreboard100.setPosition(21, gameboard.rows*32);
        if(isNeg){
            scoreboardNeg.setTextureRect(IntRect(10*21, 0, 21, 32));
            scoreboardNeg.setPosition(0, gameboard.rows*32);
            window.draw(scoreboardNeg);
        }
        window.draw(scoreboard1);
        window.draw(scoreboard10);
        window.draw(scoreboard100);

        window.display();
    }

    return 0;
}
