#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Cat.h"
#include "State.h"
#include "Board.h"
#include "Log.h"

class GameState : public State {
public:
    using State::State;
    
    virtual void handleEvent(const sf::Event&){

    };
    virtual void update(const sf::Time&){

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
