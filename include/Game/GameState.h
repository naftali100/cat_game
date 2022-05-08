#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "BFS.h"
#include "Board.h"
#include "Cat.h"
#include "Colors.h"
#include "Gui/button.h"
#include "Log.h"
#include "Random.h"
#include "State.h"
#include "Message.h"

struct BoardState {
    Hex* hex;
    sf::Vector2f catPos;
};
class GameState : public State {
public:
    using State::State;
    void init() {
        m_originalBoard = m_board;
        m_cat.setPosition(m_board.getMiddle()->getPosition());
        m_resetBtn.setPosition({20, 50});
        m_resetBtn.setFunction([&](){
            m_board.reset();
        });

        m_undoBtn.setPosition(sf::util::getGlobalTopRight(m_resetBtn) + sf::Vector2f(20, 0));
        m_undoBtn.setFunction([&](){
            if(!m_steps.empty()){
                auto step = m_steps.top();
                m_steps.pop();
                m_cat.setPosition(step.catPos);
                step.hex->unBlock();
                m_clickCount --;
            }else{
                LOGE << "can't undo. step stack empty";
            }
        });
    }

    virtual void handleEvent(const sf::Event& e) {
        m_resetBtn.handleEvent(e);
        m_undoBtn.handleEvent(e);

        if (e.type == sf::Event::MouseButtonReleased) {
            if (m_PlayerTurn) {
                auto res = m_board.positionToHex({(float)e.mouseButton.x, (float)e.mouseButton.y});
                if (res != nullptr && !res->isBlocked()) {
                    m_clickCount++;
                    res->block();
                    m_PlayerTurn = false;
                    m_steps.emplace(res, m_cat.getPosition());
                    catMove();
                }
            }
        }
    };
    virtual void update(const sf::Time&){
        m_resetBtn.update();
        m_undoBtn.update();
    };
    virtual void draw(sf::RenderTarget& win) const override {
        m_board.draw(win);
        m_cat.draw(win);

        sf::Text clicksText("number of clicks: " + std::to_string(m_clickCount), Resources::getFont(Fonts::Main));
        clicksText.setFillColor(Colors::Black);
        clicksText.move(10,0);
        win.draw(clicksText);
        
        m_resetBtn.draw(win);
        m_undoBtn.draw(win);
    };

    // invoke algorithem and find cat's next position
    void catMove() {
        auto catHex = m_board.positionToHex(m_cat.getPosition() + sf::Vector2f(10, 10));
        if (catHex) {
            auto n = catHex->getNeighbors();
            for (auto nn : n) {
                if (m_board.isOutside(nn)) {
                    resetGame("ha ha. loser! :D", true);
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
                resetGame("you won!!!", false);
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
    void resetGame(const std::string& message, bool fromOriginal){
        m_stateManager.pushState(std::make_unique<Message>(m_stateManager, message));
        if(fromOriginal)
            m_board = m_originalBoard;
        else{
            m_board.reset();
            m_originalBoard = m_board;
        }
        m_PlayerTurn = true;
        m_cat.setPosition(m_board.getMiddle()->getPosition());
        m_clickCount = 0;
        while(!m_steps.empty()) 
            m_steps.pop();
    }

private:
    Cat m_cat;
    Board m_originalBoard;  // for reset level option
    Board m_board {11, Random::rnd(4, 11)};
    bool m_PlayerTurn = true;
    int m_clickCount = 0;

    gui::Button m_resetBtn{"reset"};
    gui::Button m_undoBtn {"undo"};

    std::stack<BoardState> m_steps;
};

#endif
