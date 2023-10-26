#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"
#include "Tile.h"
#include "Grid.h"
#include "Buttons.h"
#include <fstream>
using namespace std;

int w, h, m;

void GetConfig() {
    string path = "boards/config.cfg";
    ifstream inFS;
    string width, height, mines;


    inFS.open(path);
    if (!inFS.is_open()) {
        cout << "file couldn't open" << endl;
    }
    else {
        getline(inFS, width);
        getline(inFS, height);
        getline(inFS, mines);
    }
    inFS.close();

    w = stoi(width);
    h = stoi(height);
    m = stoi(mines);

    cout << w << " " << h << " " << m << endl;
}

void ButtonClick(sf::Vector2i clickArea, Buttons &smiley, Buttons &debug, Grid &grid, Buttons &T1, Buttons &T2, Buttons &T3) {
    Tile tile;

    if (debug.ClickHandler(clickArea) && Tile::GetGameStatus()) {
        Tile::ShowMines();
    }
    else if (smiley.ClickHandler(clickArea)) {
        grid.Randomize();
        smiley.ChangeTexture("face_happy");
    }
    else if (T1.ClickHandler(clickArea)) {
        grid.LoadFile(1);
    }
    else if (T2.ClickHandler(clickArea)) {
        grid.LoadFile(2);
    }
    else if (T3.ClickHandler(clickArea)) {
        grid.LoadFile(3);
    }

}

int main()
{
    GetConfig();


    sf::RenderWindow window(sf::VideoMode(w * 32, (h * 32) + 100), "MINESWEEPER V2");

    Buttons smiley("face_happy", (w * 32) / 2 - 64, (h * 32));
    Buttons debug("debug", (w * 32) / 2 + 96, (h * 32));
    Buttons T1("test_1", (w * 32) / 2 + 160, (h * 32));
    Buttons T2("test_2", (w * 32) / 2 + 224, (h * 32));
    Buttons T3("test_3", (w * 32) / 2 + 288, (h * 32));

    Grid grid(w, h, m);
    grid.Randomize();


    while (window.isOpen())
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Event event;

        while (window.pollEvent(event))
        {

            // Close the window?
            if (event.type == sf::Event::Closed)
                window.close();

            // Press a mouse button: reveal, flag, or press a button?
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    grid.ClickHandler(mousePosition, sf::Mouse::Left);
                    ButtonClick(mousePosition, smiley, debug, grid, T1, T2, T3);
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    grid.ClickHandler(mousePosition, sf::Mouse::Right);
                }

            }
        }

        grid.Draw(window);
        grid.DrawButtons(window, debug, smiley, T1, T2, T3);
        grid.Counter(window);

        window.display();

    }

    return 0;
}

