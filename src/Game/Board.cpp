#include "Game/Board.h"

#include "Log.h"
#include <array>
#include "Random.h"

std::array<std::array<std::pair<int, int>, 6>, 2> arr{
    // odd
    std::array<std::pair<int, int>, 6>{std::pair{+1, 0}, {+1, -1}, {0, -1}, {-1, 0}, {0, +1}, {+1, +1}},
    // even
    std::array<std::pair<int, int>, 6>{std::pair{+1, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-1, +1}, {0, +1}} };

sf::Vector2i oddr_offset_neighbor(int col, int row, int dir, int isEventRow) {
    auto diff = arr[isEventRow][dir];
    sf::Vector2i res{ row + diff.second, col + diff.first };
    return res;
}

sf::Vector2i Board::getHexIndex(Hex* h) {
    int counterX = 0, counterY = 0;
    for (auto vec : m_board) {
        for (auto hex : vec) {
            if (h == &hex) {
                return { counterX, counterY };
            }
            counterY++;
        }
        counterX++;
    }
    return {};
}

std::vector<Hex*> Board::getNeighbors(int row, int col) {
    std::vector<Hex*> res;
    for (int i = 0; i < 6; i++) {
        auto ni = oddr_offset_neighbor(col, row, i, row % 2 == 0);
        // if (ni.x > 0 && ni.y > 0 && ni.x < m_board.size() && ni.y < m_board.at(ni.x).size())
        try {
            res.push_back(&m_board.at(ni.x).at(ni.y));
        }
        catch (...) {}
    }
    return res;
}

void Board::initForBFS()
{
    for (auto& row : m_board)
        for (auto& hex : row)
        {
            hex.initVisitedState();
            hex.setParent(nullptr);
        }
    m_dest.initVisitedState();
    m_dest.setParent(nullptr);
}

void Board::init(const int size, const int difficultLevel) {
    sf::Vector2f hexSize{ Hex().getGlobalBounds().width, Hex().getGlobalBounds().height };
    hexSize += {5, 5};

    sf::Vector2f Startpos{ 100, 100 };
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
Randomizer rnd;
    for (int i = 0; i < difficultLevel; i++) {
        auto& vec = m_board.at(rnd.rnd(0, m_board.size() -1));
        vec.at(rnd.rnd(0, vec.size() -1 )).block();
    }
}

void Board::draw(sf::RenderTarget& win) const {
    for (auto& vec : m_board) {
        for (auto& hex : vec) { hex.draw(win); }
    }
    m_dest.draw(win);
}