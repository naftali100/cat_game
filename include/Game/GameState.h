#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "BFS.h"
#include "Board.h"
#include "Cat.h"
#include "Colors.h"
#include "Log.h"
#include "Random.h"
#include "State.h"

class GameState : public State {
public:
    using State::State;
    void init() {
        m_cat.setPosition(m_board.getMiddle()->getPosition());
    }

    virtual void handleEvent(const sf::Event& e) {
        if (e.type == sf::Event::MouseButtonReleased) {
            if (m_PlayerTurn) {
                auto res = m_board.positionToHex({(float)e.mouseButton.x, (float)e.mouseButton.y});
                if (res != nullptr && !res->isBlocked()) {
                    m_clickCount++;
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

        sf::Text clicksText("number of clicks: " + std::to_string(m_clickCount), Resources::getFont(Fonts::Main));
        clicksText.setFillColor(Colors::Black);
        win.draw(clicksText);
    };

    // invoke algorithem and find cat's next position
    void catMove() {
        auto catHex = m_board.positionToHex(m_cat.getPosition() + sf::Vector2f(10, 10));
        if (catHex) {
            auto n = catHex->getNeighbors();
            for (auto nn : n) {
                if (m_board.isOutside(nn)) {
                    m_board.reset();
                    m_PlayerTurn = true;
                    m_cat.setPosition(m_board.getMiddle()->getPosition());
                    m_clickCount = 0;
                    return;
                }
            }
            
            // TODO: replace with score==0
            bool isWon = true;
            for(auto n: catHex->getNeighbors()){
                if(!n->isBlocked()){
                    isWon = false;
                    break;
                }
            }

            if (isWon) {
                m_board.reset();
                m_PlayerTurn = true;
                m_cat.setPosition(m_board.getMiddle()->getPosition());
                m_clickCount = 0;
                return;
            }

            auto newCatPos = m_board.implementUCS(catHex);
            if (newCatPos == nullptr) {
                // random
                do {
                    int n = Random::rnd(0, catHex->getNeighbors().size() - 1);
                    newCatPos = catHex->getNeighbors().at(n);
                } while (newCatPos->isBlocked());
            }
            m_cat.setPosition(newCatPos->getPosition());
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
