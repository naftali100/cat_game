#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState : public State {
public:
    using State::State;
    virtual void handleEvent(const sf::Event&){
    };
    virtual void update(const sf::Time&) {
        
    };
    virtual void draw(sf::RenderTarget&) const {

    };
};

#endif
