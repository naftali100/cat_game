#include "Game/Board.h"

#include <array>
#include <utility>

#include "Random.h"
#include "SfmlUtil.h"

std::array<std::array<std::pair<int, int>, 6>, 2> arr{
    // odd
    std::array<std::pair<int, int>, 6>{std::pair<int, int>{+1, 0}, {+1, -1}, {0, -1}, {-1, 0}, {0, +1}, {+1, +1}},
    // even
    std::array<std::pair<int, int>, 6>{std::pair<int, int>{+1, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-1, +1}, {0, +1}}};

sf::Vector2i oddr_offset_neighbor(int col, int row, int dir, int isEventRow) {
    auto diff = arr[isEventRow][dir];
    sf::Vector2i res{row + diff.second, col + diff.first};
    return res;
}

std::vector<Hex*> Board::getNeighbors(int row, int col) {
    std::vector<Hex*> res;
    for (int i = 0; i < 6; i++) {
        auto ni = oddr_offset_neighbor(col, row, i, row % 2 == 0);
        // if (ni.x > 0 && ni.y > 0 && ni.x < m_board.size() && ni.y < m_board.at(ni.x).size())
        try {
            res.push_back(&m_board.at(ni.x).at(ni.y));
        } catch (...) {}
    }
    return res;
}

void Board::initForUCS() {
    for (auto& row : m_board)
        for (auto& hex : row) {
            hex.setCostSoFar(0);
            hex.setParent(nullptr);
        }
    m_dest.setParent(nullptr);
}

void Board::init(const int size, const int difficultLevel) {
    sf::Vector2f hexSize{Hex().getGlobalBounds().width, Hex().getGlobalBounds().height};
    hexSize += {5, 5};

    sf::Vector2f Startpos{100, 100};
    sf::Vector2f pos = Startpos;

    for (int i = 0; i < size; i++) {
        m_board.emplace_back();
        if (i % 2 != 0) {
            pos.x += hexSize.x / 2;
        }
        for (int j = 0; j < size; j++) {
            m_board.at(i).emplace_back();
            m_board.at(i).back().setPosition(pos);
            pos.x += hexSize.x;
        }
        pos.x = Startpos.x;
        pos.y += (hexSize.y / 4) * 3;
    }

    // add dest as neighbor to all edge tile
    int row = 0, col = 0;
    for (auto& vec : m_board) {
        for (auto& h : vec) {
            h.setNeighbors(getNeighbors(row, col));
            if (row == 0 || row + 1 == size || col == 0 || col + 1 == size) {
                h.addNeighnor(&m_dest);
            }
            col++;
        }
        col = 0;
        row++;
    }

    for (int i = 0; i < difficultLevel; i++) {
        auto& vec = m_board.at(Random::rnd(0, m_board.size() - 1));
        auto& toBlock = vec.at(Random::rnd(0, vec.size() - 1));
        if (&toBlock != getMiddle())
            toBlock.block();
        else
            i--;
    }
}

void Board::draw(sf::RenderTarget& win) const {
    for (auto& vec : m_board) {
        for (auto& hex : vec) { hex.draw(win); }
    }
}

Hex* Board::implementUCS(Hex* root) {
    initForUCS();
    UniformCostSearch::UCS(root, &m_dest);
    return findNextInPathToDest(root);
}

// return nullptr if there is no path
Hex* Board::findNextInPathToDest(const Hex* root) {
    Hex* temp = &m_dest;
    while (temp != nullptr && temp->getParent() != root) temp = temp->getParent();

    return temp;
}

Hex* Board::getMiddle() {
    auto& vec = m_board.at(m_board.size() / 2);
    return &vec.at(vec.size() / 2);
}

bool Board::isOutside(Hex* h) {
    return h == &m_dest;
}

Hex* Board::positionToHex(const sf::Vector2f& pos) {
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
