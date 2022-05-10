#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Hex.h"
#include "BFS.h"
#include "UniformCostSearch.h"

class Board {
public:
    Board() {
        init(11, 10);
    }

    Board(const int size, const int difficultLevel) {
        init(size, difficultLevel);
    }

    void reset() {
        m_board.clear();
        init(11, 10);
    }
    void draw(sf::RenderTarget& target) const;
    std::vector<Hex*> getNeighbors(int col, int row);
    Hex* implementBFS(Hex* root);
    Hex* implementUCS(Hex* root);

    //return nullptr if there is no path
    Hex* findNextInPathToDest(const Hex* root) ;
    Hex* getMiddle();
    bool isOutside(Hex* h);

     Hex* positionToHex(const sf::Vector2f& pos);

private:
    Hex m_dest; //the out of the board
    void init(const int size, const int difficultLevel);
    void initForBFS();          //init the state of the Hexes
    void initForUCS();          //init the state of the Hexes
    std::vector<std::vector<Hex>> m_board;
};

#endif
