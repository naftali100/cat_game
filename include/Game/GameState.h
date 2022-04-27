#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Cat.h"
#include "State.h"
#include "Board.h"
#include "Log.h"
#include "Colors.h"

class GameState : public State {
public:
    using State::State;
    void init() {
        m_board.initLevel(11, 1);
    }
    
    virtual void handleEvent(const sf::Event& e){
        if(e.type == sf::Event::MouseButtonReleased){
            auto res = m_board.mousePositionToHex({(float)e.mouseButton.x, (float)e.mouseButton.y}); 
            if(res != nullptr){
                res->block();
                // for(auto& i: res->getNeighbors()){
                //     i->setColor(sf::Color::Green);
                // }
                // res->setColor(Colors::Danger);
            }
        }
    };
    virtual void update(const sf::Time&){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            m_board.m_dest.setColor(Colors::Gray);
        }

    };
    virtual void draw(sf::RenderTarget& win) const override {
        m_board.draw(win);
    };

    // invoke algorithem and find cat's next position
    void catMove();

private:
    Cat m_cat;
    Board m_originalBoard; // for reset level option
    Board m_board;
    bool m_PlayerTurn;
    int m_clickCount;
};

#endif
