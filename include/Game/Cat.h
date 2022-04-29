#pragma once
#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>

#include "Resources.h"

class Cat : public sf::Transformable {
public:
    void draw(sf::RenderTarget& win) const {
        sf::Sprite cat{Resources::getTexture(Textures::Cat)};
        cat.scale(sf::Vector2f(0.09,0.09));
        // cat.setOrigin(sf::util::getGlobalCenter(cat));
        cat.setPosition(getPosition() + sf::Vector2f(10,0));
        win.draw(cat);
    }
private:
    sf::Sprite m_cat;
    // sf::Vector2f m_position;

};

#endif