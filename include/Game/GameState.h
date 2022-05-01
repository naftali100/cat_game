#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "BFS.h"
#include "Board.h"
#include "Cat.h"
#include "Colors.h"
#include "Log.h"
#include "State.h"

class GameState : public State {
public:
    using State::State;
    void init() {
        m_cat.setPosition(m_board.getMiddle()->getPosition());
        srand(time(NULL));
    }

    virtual void handleEvent(const sf::Event& e) {
        if (e.type == sf::Event::MouseButtonReleased) {
            if (m_PlayerTurn) {
                auto res = m_board.positionToHex({(float)e.mouseButton.x, (float)e.mouseButton.y});
                if (res != nullptr && !res->isBlocked()) {
                    res->block();
                    m_PlayerTurn = false;
                    catMove();
                    // TODO: push step to undo stack
                }
            }
        }
    };
    virtual void update(const sf::Time&){};
    virtual void draw(sf::RenderTarget& win) const override {
        m_board.draw(win);
        m_cat.draw(win);
        LOGI << sf::RectangleShape();
    };

    // invoke algorithem and find cat's next position
    void catMove() {
        auto catHex = m_board.positionToHex(m_cat.getPosition() + sf::Vector2f(10, 10));
        if (catHex) {
            auto n = catHex->getNeighbors();
            for (auto correntHex : n) {
                // if correntHex == board.m_dest -> gameover
            }

            bool isWon = catHex->score() == 0; // cat have no where to go
            if (isWon) {
                m_board.reset();
                m_PlayerTurn = true;
                m_cat.setPosition(m_board.getMiddle()->getPosition());
                return;
            }

            auto newCatPos = m_board.implementBFS(catHex);
            if (newCatPos == nullptr) {
                //TODO: do secondary strategy
                LOGE << "can't find path (new pos found in nullptr)";
            }
            else {
                m_cat.setPosition(newCatPos->getPosition());
            }
        }
        m_PlayerTurn = true;
    }

private:
    Cat m_cat;
    Board m_originalBoard;  // for reset level option
    Board m_board;
    bool m_PlayerTurn = true;
    int m_clickCount;
};

#endif
