#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Hex.h"

// TODO:
//
//  : class drewable

class Board : public sf::Drawable {
public:
    Board(const int size, const int difficultLevel);
    void initLevel();
    void drew();

    sf::Vector2f getHexIndex(Hex* h);

    std::vector<Hex*> getNeighbors(int col, int row) {}

private:
    void init();
    std::vector<std::vector<Hex>> m_board;
    Hex m_dest;
};

#endif