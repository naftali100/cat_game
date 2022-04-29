#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Hex.h"

class Board {
public:
    // what is the diff betwin initLevel() and init()? this is public and the other is private
    void initLevel(const int size, const int difficultLevel);
    void draw(sf::RenderTarget& target) const;

    sf::Vector2i getHexIndex(Hex* h) const;


    // is this encapsulation violation?
    // can we do better?
    std::vector<Hex*> getNeighbors(int col, int row);

    //as above
    Hex* mousePositionToHex(const sf::Vector2f& pos);


private:
    Hex m_dest;
    void init();
    std::vector<std::vector<Hex>> m_board;
};

#endif