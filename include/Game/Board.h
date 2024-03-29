#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Hex.h"
#include "UniformCostSearch.h"
#include "Config.h"
#include "Random.h"

class Board {
public:
    Board() {
        init(BOARD_SIZE, Random::rnd(LEVEL_MIN, LEVEL_MAX));
    }

    Board(const int size, const int difficultLevel) {
        init(size, difficultLevel);
    }

    void reset() {
        m_board.clear();
        init(BOARD_SIZE, Random::rnd(LEVEL_MIN, LEVEL_MAX));
    }
    void draw(sf::RenderTarget& target) const;
    std::vector<Hex*> getNeighbors(int col, int row);
    Hex* implementUCS(Hex* root);

    //return nullptr if there is no path
    Hex* findNextInPathToDest(const Hex* root) ;
    Hex* getMiddle();
    bool isOutside(Hex* h);

     Hex* positionToHex(const sf::Vector2f& pos);

private:
    void init(const int size, const int difficultLevel);
    void initForUCS();          //init the state of the Hexes

private:
    Hex m_dest; //the out of the board
    std::vector<std::vector<Hex>> m_board;
};

#endif
