#include "Game/Cat.h"

#include "Game/Hex.h"
#include "Resources.h"

void Cat::draw(sf::RenderTarget& win) const {
    sf::Sprite cat{Resources::getTexture(Textures::Cat)};
    cat.scale(sf::Vector2f(0.09, 0.09));
    // cat.setOrigin(sf::util::getGlobalCenter(cat));
    cat.setPosition(m_pos->getPosition() + sf::Vector2f(10, 0));
    win.draw(cat);
}