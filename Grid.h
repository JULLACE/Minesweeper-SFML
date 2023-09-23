#include "Tile.h"
#include "Buttons.h"


using namespace std;

class Grid {
    int height;
    int width;
    int mines;
    int originalMines; // backup
    Tile **tiles;

public:
    Grid(int h, int w, int m); // Grid construction with specific values using a 2D Array

    void Draw(sf::RenderWindow &window); // Draws Grid & other game handling
    void DrawButtons(sf::RenderWindow &window, Buttons &Debug, Buttons &Smiley, Buttons &T1, Buttons &T2, Buttons T3); // Draw buttons and functionality

    void ClickHandler(sf::Vector2i mP, sf::Mouse::Button button); // Handles clicks

    bool WinCheck();

    void Randomize();

    void LoadFile(int option);

    void Counter(sf::RenderWindow &window);


    ~Grid(); // Cleanup

};