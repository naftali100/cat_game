#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Hex.h"
#include "BFS.h"

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

    sf::Vector2i getHexIndex(Hex* h);

    std::vector<Hex*> getNeighbors(int col, int row);

    Hex* positionToHex(const sf::Vector2f& pos) {
        for (auto& vec : m_board) {
            for (auto& hex : vec) {
                auto v = sf::util::getGlobalCenter(hex) - pos;
                // ASK: constant 25
                if (std::abs(v.x) < 25 && std::abs(v.y) < 25) {
                    return &hex;
                }
            }
        }
        return nullptr;
    }

    Hex* implementBFS(Hex* root) {
        initForBFS();
        BFS::search(root, &m_dest);
        return findNextInPathToDest(root);
    }

    Hex* findNextInPathToDest(const Hex* root) {
        //TODO: catch exceptions
        Hex* temp = &m_dest;
        while (temp->getParent() != root)
            temp = temp->getParent();
        return temp;
    }

    Hex* getMiddle() {
        auto& vec = m_board.at(m_board.size() / 2);
        return &vec.at(vec.size() / 2);
    }

private:
    Hex m_dest;
    void init();
    void initForBFS();          //init the state of the Hexes
    std::vector<std::vector<Hex>> m_board;
};

#endif