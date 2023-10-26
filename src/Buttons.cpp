#include "Buttons.h"

using namespace std;

Buttons::Buttons(string name, int x, int y) {
    sprite.setTexture(TextureManager::GetTexture(name));

    sprite.setPosition(x,y);
    area = sprite.getGlobalBounds();
}

sf::Sprite Buttons::GetSprite() {
    return sprite;
}

bool Buttons::ClickHandler(sf::Vector2i mP) {
    if (area.contains(mP.x, mP.y))
        return true;
    return false;
}

void Buttons::ChangeTexture(string name) {
    sprite.setTexture(TextureManager::GetTexture(name));
}
