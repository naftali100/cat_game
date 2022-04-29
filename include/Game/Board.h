#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Hex.h"

// logic - data structure
class Board {
public:
    Board() {
        init(11, 10);
    }
    Board(const int size, const int difficultLevel) {
        init(size, difficultLevel);
    }
    void init(const int size, const int difficultLevel);
    void draw(sf::RenderTarget& target) const;

    sf::Vector2i getHexIndex(Hex* h) const;


    // is this encapsulation violation?
    // can we do better?
    std::vector<Hex*> getNeighbors(int col, int row);

    Hex* positionToHex(const sf::Vector2f& pos) {
        for (auto& vec : m_board) {
            for (auto& hex : vec) {
                auto v = sf::util::getGlobalCenter(hex) - pos;
                if (std::abs(v.x) < 25 && std::abs(v.y) < 25) {
                    return &hex;
                }
            }
        }
        return nullptr;
    }

    Hex* getMiddle() {
        auto& vec = m_board.at(m_board.size() / 2);
        return &vec.at(vec.size() / 2);
    }

private:
    Hex m_dest;
    void init();
    std::vector<std::vector<Hex>> m_board;
};

#endif