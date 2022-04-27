#pragma once
#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>

#include "Resources.h"

class Cat {
public:
    void setPosition(){

    }

    void draw(sf::RenderTarget& win) const {
        sf::Sprite cat{Resources::getTexture(Textures::Cat)};
        cat.scale(sf::Vector2f(0.1,0.1));
        cat.setPosition(m_position);
        win.draw(cat);
    }
private:
    sf::Sprite m_cat;
    sf::Vector2f m_position;

};

#endif