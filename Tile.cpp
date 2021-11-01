#include "Tile.h"
#include "TextureManager.h"
#include "Random.h"

Tile::Tile() {
    hiddenTile.setTexture(TextureManager::GetTexture("tile_hidden"));
    revealedTile.setTexture(TextureManager::GetTexture("tile_revealed"));
    flag.setTexture(TextureManager::GetTexture("flag"));
    mine.setTexture(TextureManager::GetTexture("mine"));
    num1.setTexture(TextureManager::GetTexture("number_1"));
    num2.setTexture(TextureManager::GetTexture("number_2"));
    num3.setTexture(TextureManager::GetTexture("number_3"));
    num4.setTexture(TextureManager::GetTexture("number_4"));
    num5.setTexture(TextureManager::GetTexture("number_5"));
    num6.setTexture(TextureManager::GetTexture("number_6"));
    num7.setTexture(TextureManager::GetTexture("number_7"));
    num8.setTexture(TextureManager::GetTexture("number_8"));
    isRevealed = false;
    isFlagged = false;
    isMine = false;
    debugMode = false;
}

void Tile::Render(RenderWindow& window) {
    int mines = 0;
    for(int i = 0; i < adjacentTiles.size(); i++){
        if(adjacentTiles[i]->isMine){
            mines++;
        }
    }
    hiddenTile.setPosition(positionx, positiony);
    window.draw(hiddenTile);

    if(isRevealed){
        revealedTile.setPosition(positionx, positiony);
        window.draw(revealedTile);
    }
    if(isMine && isRevealed){
        mine.setPosition(positionx, positiony);
        window.draw(mine);
    }
    if(isRevealed && !isMine){
        if(mines == 0){
            revealedTile.setPosition(positionx,positiony);
            window.draw(revealedTile);
        }
        if(mines == 1){
            num1.setPosition(positionx, positiony);
            window.draw(num1);
        }
        if(mines == 2){
            num2.setPosition(positionx, positiony);
            window.draw(num2);
        }
        if(mines == 3){
            num3.setPosition(positionx, positiony);
            window.draw(num3);
        }
        if(mines == 4){
            num4.setPosition(positionx, positiony);
            window.draw(num4);
        }
        if(mines == 5){
            num5.setPosition(positionx, positiony);
            window.draw(num5);
        }
        if(mines == 6){
            num6.setPosition(positionx, positiony);
            window.draw(num6);
        }
        if(mines == 7){
            num7.setPosition(positionx, positiony);
            window.draw(num7);
        }
        if(mines == 8){
            num8.setPosition(positionx, positiony);
            window.draw(num8);
        }
    }
    if(isFlagged){
        flag.setPosition(positionx, positiony);
        window.draw(flag);
    }
    if(debugMode && isMine){
        mine.setPosition(positionx, positiony);
        window.draw(mine);
    }
}

FloatRect Tile::GetSpriteRect() {
    if(isFlagged){
        return flag.getGlobalBounds();
    }
    if(isRevealed){
        return revealedTile.getGlobalBounds();
    }else{
        return hiddenTile.getGlobalBounds();
    }
}

void Tile::RevealTile() {
    if(isRevealed)
        return;
    if(isFlagged)
        return;
    isRevealed = true;
    int mines = 0;
    for(int i = 0; i < adjacentTiles.size(); i++){
        if(adjacentTiles[i]->isMine){
            mines++;
        }
    }
    if(mines == 0) {
        for(int i = 0; i < adjacentTiles.size(); i++) {
            adjacentTiles[i]->RevealTile();
        }
    }
}




