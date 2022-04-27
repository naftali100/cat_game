#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Hex.h"

class Board  {
public:
    void initLevel(const int size, const int difficultLevel);
    void draw(sf::RenderTarget& target) const;
        
    sf::Vector2i getHexIndex(Hex* h);

    std::vector<Hex*> getNeighbors(int col, int row);

private:
    void init();
    std::vector<std::vector<Hex>> m_board;
    Hex m_dest;
};

#endif