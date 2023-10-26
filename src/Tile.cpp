#include "Tile.h"
#include <iostream>

bool showMines = false;
bool game = true;
bool win = false;

Tile::Tile() {
    revealed.setTexture(TextureManager::GetTexture("tile_revealed"));
    hidden.setTexture(TextureManager::GetTexture("tile_hidden"));
    flag.setTexture(TextureManager::GetTexture("flag"));
    mine.setTexture(TextureManager::GetTexture("mine"));


    area = hidden.getGlobalBounds();

    flagStatus = false;
    status = true;
    mineStatus = false;

    adjacentMineCount = 0;

}

void Tile::Reveal(sf::Vector2i clickArea) {
    if (area.contains(clickArea.x, clickArea.y) && status && !flagStatus && !mineStatus && game) {
        status = !status;
        RecursiveReveal();
    }

    else if (area.contains(clickArea.x, clickArea.y) && mineStatus && !flagStatus) {
        game = false;
        showMines = true;
    }
}

sf::Sprite Tile::GetSprite() {
    if (!game && mineStatus && !flagStatus) {
        return revealed;
    }

    else if (status) {
        return hidden;
    }

    else if (!status) {
        return revealed;
    }
}

void Tile::SetPosition(float x, float y) {
    hidden.setPosition(x, y);
    revealed.setPosition(x, y);
    flag.setPosition(x, y);
    num.setPosition(x, y);
    mine.setPosition(x,y);

    // redo the area position, since it was changed.
    area = hidden.getGlobalBounds();
}

void Tile::Flag(sf::Vector2i clickArea) {
    if (area.contains(clickArea.x, clickArea.y) && status && game)
        flagStatus = !flagStatus;
}

bool Tile::getFStatus() {
    return flagStatus;
}

sf::Sprite Tile::FlagSprite() {
    return flag;
}

void Tile::AdjacentTiles(Tile **grid, int x, int y, int h, int w) {
    adjacentTiles.clear();

    int tempY = y - 1;

    for (unsigned int i = 0; i < 3; ++i) {
        int tempX = x - 1;

        for (unsigned int j = 0; j < 3; ++j) {
            if (tempY != y || tempX != x) {
                // Checks if we are storing the given X,Y tile and avoids it.

                if ((tempY >= 0 && tempX >= 0) && (tempY < h && tempX < w)) {
                    // Check case for corner tile, or
                    // checks for negative / outofbounds coord

                    adjacentTiles.push_back(&grid[tempY][tempX]);
                }

            }

            tempX += 1;
        }

        tempY += 1;
    }
}

void Tile::RecursiveReveal() {
    int count = 0;
    for (unsigned int i = 0; i < adjacentTiles.size(); ++i) {
        if (adjacentTiles[i]->mineStatus == true) {
            ++count;
        }
    }

    adjacentMineCount = count;
    // Above checks for adjacent mine count, stores it into the proper tile.
    // Then below checks to see if it is a mine or flagged, then recursively reveals tiles.


    for (unsigned int i = 0; i < adjacentTiles.size(); ++i) {
        if (adjacentTiles[i]->status && adjacentMineCount == 0 && !adjacentTiles[i]->flagStatus) {

            adjacentTiles[i]->status = false;

            adjacentTiles[i]->RecursiveReveal();
        }
    }
}

bool Tile::GetNumStatus() {
    if (adjacentMineCount > 0) {
        return true;
    }
    return false;
}

sf::Sprite Tile::NumSprite() {
    string temp = "number_" + to_string(adjacentMineCount);
    num.setTexture(TextureManager::GetTexture(temp));

    return num;
}

void Tile::ShowMines() {
    showMines = !showMines;
}

void Tile::Mine(bool tf) {
    mineStatus = tf;
}

sf::Sprite Tile::GetMineSprite() {
    if (showMines) return mine;
}

bool Tile::MineCheat() {
    if (showMines && mineStatus && !flagStatus) return true;
    return false;
}

bool Tile::GetGameStatus() {
    return game;
}

bool Tile::WinCondition() {
    if (!status && !mineStatus) {
        return true;
    }
}

void Tile::Win() {
    if (!flagStatus) {
        win = true;
        flagStatus = true;
        game = false;
    }
}

bool Tile::WinCheck() {
    return win;
}

void Tile::Reset() {
    flagStatus = false;
    status = true;
    mineStatus = false;
    adjacentMineCount = 0;

    if (!game) {
        showMines = false;
    }

    game = true;
    win = false;
}

bool Tile::isMined() {
    return mineStatus;
}

Tile::~Tile() {

}


