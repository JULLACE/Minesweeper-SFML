#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <vector>

class Buttons {

    sf::Sprite sprite;
    sf::FloatRect area;

public:
    Buttons(string name, int x, int y);
    sf::Sprite GetSprite();

    void ChangeTexture(string name);

    bool ClickHandler(sf::Vector2i mP);
};
