#include "Grid.h"
#include "Random.h"
#include <fstream>
#include <iostream>

using namespace std;

Grid::Grid(int x, int y, int m) {

    // Storing array size
    height = y;
    width = x;
    mines = m;
    originalMines = m;

    // Array construction
    tiles = new Tile *[y];

    for (unsigned int i = 0; i < y; ++i) {
        tiles[i] = new Tile[x];

        for (unsigned int j = 0; j < x; ++j)
            tiles[i][j].SetPosition(j * 32, i * 32);
    }

}


void Grid::Draw(sf::RenderWindow &window) {
    int count = 0;

    for (unsigned int i = 0; i < height; ++i) {

        // Draws every tile
        for (unsigned int j = 0; j < width; ++j) {

            tiles[i][j].AdjacentTiles(tiles, j, i, height, width); // Loop storing adjacent Tiles info

            window.draw(tiles[i][j].GetSprite()); // Loop drawing tiles

            // Checks to see if flagged, then draws sprite from that tile.
            if (tiles[i][j].getFStatus())
                window.draw(tiles[i][j].FlagSprite());

            // Drawing adjacent mines numbers
            if (tiles[i][j].GetNumStatus())
                window.draw(tiles[i][j].NumSprite());

            // Displays the debugging mode and game over screen
            if (tiles[i][j].MineCheat())
                window.draw(tiles[i][j].GetMineSprite());

            if (tiles[i][j].isMined())
                count++;

            WinCheck();
        }
    }

    //cout << "mines: " << count << endl;
}

void Grid::DrawButtons(sf::RenderWindow &window, Buttons &Debug, Buttons &Smiley, Buttons &T1, Buttons &T2, Buttons T3) {
    if (Tile::GetGameStatus()) {
        window.draw(Smiley.GetSprite());
    }
    else if (Tile::WinCheck()) {
        Smiley.ChangeTexture("face_win");
        window.draw(Smiley.GetSprite());
    }

    else {
        Smiley.ChangeTexture("face_lose");
        window.draw(Smiley.GetSprite());
    }

    window.draw(Debug.GetSprite());
    window.draw(T1.GetSprite());
    window.draw(T2.GetSprite());
    window.draw(T3.GetSprite());
}

void Grid::ClickHandler(sf::Vector2i mP, sf::Mouse::Button button) {
    if (button == sf::Mouse::Left) {
        for (unsigned int i = 0; i < height; ++i) {
            for (unsigned int j = 0; j < width; ++j) {
                tiles[i][j].Reveal(mP);
            }
        }
    }

    else if (button == sf::Mouse::Right) {
        for (unsigned int i = 0; i < height; ++i) {
            for (unsigned int j = 0; j < width; ++j) {
                tiles[i][j].Flag(mP);
            }
        }
    }
}

Grid::~Grid() {

    // TODO: Check with memory leaker program

    for (unsigned int i = 0; i < height; ++i) {
        delete[] tiles[i];
    }
    delete[] tiles;
}

bool Grid::WinCheck() {
    int check = height * width;

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            if (tiles[i][j].WinCondition())
                check--;
        }
    }

    if (check == mines) {
        for (unsigned int i = 0; i < height; ++i) {
            for (unsigned int j = 0; j < width; ++j) {
                if (!tiles[i][j].WinCondition())
                    tiles[i][j].Win();
            }
        }
    }

}

void Grid::Randomize() {
    mines = originalMines;

    for (unsigned int i = 0; i < height; ++i)
        for (unsigned int j = 0; j < width; ++j)
            tiles[i][j].Reset();

    for (unsigned int i = 0; i < mines; ++i) {
        int randomX = Random::Int(0, width - 1);
        int randomY = Random::Int(0, height - 1);

        if (!tiles[randomY][randomX].isMined())
            tiles[randomY][randomX].Mine(true);
        else i -= 1;
    }




}

void Grid::LoadFile(int option) {
    string path;
    ifstream inFS;
    string line;

    int newMines = 0;


    switch (option) {
        case 1: path = "boards/testboard1.brd";
        break;

        case 2: path = "boards/testboard2.brd";
        break;

        case 3: path = "boards/testboard3.brd";
        break;
    }




    inFS.open(path);
    if (!inFS.is_open()) {
        cout << "file couldn't open" << endl;
    }
    else {
        for (unsigned int i = 0; i < height; ++i) {
            getline(inFS, line);

            for (unsigned int j = 0; j < width; ++j) {
                if (line[0] == '1') {
                    tiles[i][j].Mine(true);
                    newMines++;
                }

                else tiles[i][j].Mine(false);
                line.erase(0,1);
            }
        }
    }
    inFS.close();

    mines = newMines;



}

void Grid::Counter(sf::RenderWindow &window) {
    sf::Sprite counter1, counter2, counter3, negative;
    int temp = 0;
    string display = "";

    counter1.setTexture(TextureManager::GetTexture("digits"));
    counter2.setTexture(TextureManager::GetTexture("digits"));
    counter3.setTexture(TextureManager::GetTexture("digits"));
    negative.setTexture(TextureManager::GetTexture("digits"));

    sf::IntRect area1, area2, area3, negativeArea;

    area1.width = 21;
    area1.height = 32;

    area2.width = 21;
    area2.height = 32;

    area3.width = 21;
    area3.height = 32;
    area3.left = 21 * 1;

    negativeArea.width = 21;
    negativeArea.height = 32;
    negativeArea.left = 21 * 10;

    counter1.setPosition((width * 32) / 2 - 328, (height * 32));
    counter2.setPosition((width * 32) / 2 - 349, (height * 32));
    counter3.setPosition((width * 32) / 2 - 370, (height * 32));
    negative.setPosition((width * 32) / 2 - 391, (height * 32));



    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            if (tiles[i][j].getFStatus())
                ++temp;
        }
    }


    display = to_string(mines - temp);


    area1.left = 21 * (((int)(display[1]) - 48));
    area2.left = 21 * (((int)(display[0]) - 48));
    area3.left = 21 * 0;

    counter1.setTextureRect(area1);
    counter2.setTextureRect(area2);
    counter3.setTextureRect(area3);
    negative.setTextureRect(negativeArea);


    window.draw(counter1);
    window.draw(counter2);
    window.draw(counter3);

    if (stoi(display) < 0)
        window.draw(negative);

}


