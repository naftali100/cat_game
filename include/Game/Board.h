#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Hex.h"
#include "BFS.h"
#include "UniformCostSearch.h"

// logic - data structure
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

    Hex* implementUCS(Hex* root) {
        initForUCS();
        UniformCostSearch::UCS(root, &m_dest);
        return findNextInPathToDest(root);
    }

    //return nullptr if there is no path
    Hex* findNextInPathToDest(const Hex* root) {
        Hex* temp = &m_dest;
        while (temp != nullptr && temp->getParent() != root)
            temp = temp->getParent();

        return temp;
    }

    Hex* getMiddle() {
        auto& vec = m_board.at(m_board.size() / 2);
        return &vec.at(vec.size() / 2);
    }

    bool isOutside(Hex* h){
        return h == &m_dest;
    }

private:
    Hex m_dest; //the out of the board
    void init(const int size, const int difficultLevel);
    void initForBFS();          //init the state of the Hexes
    void initForUCS();          //init the state of the Hexes
    std::vector<std::vector<Hex>> m_board;
};

#endif

//template<class T>
//class graph {
//    graph(int size) {
//        std::vector<std::vector<T>> graph;
//    }
//};