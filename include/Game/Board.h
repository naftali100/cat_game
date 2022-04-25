#pragma once
#ifndef BOARD_H
#define BOARD_H
#include <vector>

#include "Hex.h"

//TODO:
// 
// : class drewable

class Board {
public:
    Board(const int size, const int difficultLevel);
    void drew();

private:
    void init();
    std::vector<Hex> m_board;
    Hex m_dest;
    

};

#endif