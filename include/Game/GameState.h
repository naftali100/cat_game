#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState : public State {
public:
    using State::State;
    virtual void handleEvent(const sf::Event&){
        // if()
    };
    virtual void update(const sf::Time&) {
        if (catTurn) {
            cat.move();
        }
        else {
        }
    };
    virtual void draw(sf::RenderTarget&) const {

    };
};

#endif
