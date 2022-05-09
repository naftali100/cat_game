#pragma once
#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include "Hex.h"

class Cat {
public:
    void draw(sf::RenderTarget& win) const;
    void setHex(Hex* h){
        m_pos = h;
    };

    Hex* getHex(){
        return m_pos;
    }
private:
    Hex* m_pos;
    sf::Sprite m_cat;
};

#endif