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
    
     Hex* mousePositionToHex(const sf::Vector2f& pos) {
        for (auto& vec : m_board) {
            for (auto& hex : vec) {
                auto v = sf::util::getGlobalCenter(hex) - pos;
                if (std::abs(v.x) < 30 && std::abs(v.y) < 30) {
                    return &hex;
                }
            }
        }
        return nullptr;
    }

    Hex m_dest;
private:
    void init();
    std::vector<std::vector<Hex>> m_board;
};

#endif