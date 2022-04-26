#include "Game/Board.h"

#include "SfmlUtil.h"

std::array<std::array<std::pair<int, int>, 6>, 2> arr{
    // odd
    std::array<std::pair<int, int>, 6>{std::pair{+1, 0}, {+1, -1}, {0, -1}, {-1, 0}, {0, +1}, {+1, +1}},
    // even
    std::array<std::pair<int, int>, 6>{std::pair{+1, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-1, +1}, {0, +1}}};

sf::Vector2f oddr_offset_neighbor(int col, int row, int dir, int isEventRow) {
    auto diff = arr[isEventRow][dir];
    return {col + diff.first, row + diff.second};
}

sf::Vector2f Board::getHexIndex(Hex* h) {
    int counterX = 0, counterY = 0;
    for (auto vec : m_board) {
        for (auto hex : vec) {
            if (h == &hex) {
                return {counterX, counterY};
            }
            counterY++;
        }
        counterX++;
    }
}

std::vector<Hex*> Board::getNeighbors(int col, int row) {
    std::vector<Hex*> res;
    for (int i = 0; i < 6; i++) {
        auto ni = oddr_offset_neighbor(col, row, i, row % 2);
        res.push_back(&m_board[ni.x][ni.y]);
    }
    return res;
}

Board::Board(const int size, const int difficultLevel) {}

void Board::initLevel() {
    sf::Vector2f pos{0, 0};
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            m_board[i].emplace_back();
            m_board[i].back().setPosition(pos);
            pos.x += 10;  // TODO: get tile size
        }
        pos.y = 0;
    }

    int row = 0, col = 0;
    for (auto vec : m_board) {
        for (auto h : vec) {
            h.setNeighbors(getNeighbors(row, col));
            col++;
        }
        row++;
    }
}