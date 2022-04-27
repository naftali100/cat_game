#pragma once
#ifndef LOGIC_H
#define LOGIC_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Hex.h"

class HexBoardLogic {
public:
   

    void draw(sf::RenderTarget& win) {
        
    }

private:
    std::vector<std::vector<Hex>> m_board;
};

#endif