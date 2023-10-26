#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "TextureManager.h"

using namespace std;

class Tile {
    bool status;        // true = hidden
    bool flagStatus;    // true = flagged
    bool mineStatus;    // true = mined


    sf::Sprite hidden, revealed, flag, num, mine;
    sf::FloatRect area;

    vector<Tile*> adjacentTiles;
    int adjacentMineCount;

public:
    Tile();

    void Reveal(sf::Vector2i clickArea);//
    void SetPosition(float x, float y); // Sets position and sprite of tile
    void RecursiveReveal();             // and recursively reveals them.
    sf::Sprite GetSprite();             // (If the game is lost, shows mines on revealed tiles)

    void Flag(sf::Vector2i clickArea);  //
    bool getFStatus();                  // Flag Functions
    sf::Sprite FlagSprite();            //


    bool WinCondition();
    void Win();
    static bool WinCheck();


    void Mine(bool tf); // sets mine
    static void ShowMines(); // shows mines
    sf::Sprite GetMineSprite();
    bool MineCheat();
    bool isMined();

    sf::Sprite NumSprite();
    bool GetNumStatus();

    void AdjacentTiles(Tile** grid, int x, int y, int h, int w);
    static bool GetGameStatus();


    void Reset();

    ~Tile();


};
