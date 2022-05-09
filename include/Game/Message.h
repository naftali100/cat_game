#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H

#include <SFML/Graphics.hpp>
#include "State.h"

class Message : public State {
public:
    Message(StateManager& sm, const std::string& msg) : State(sm), m_msg(msg) {}

    virtual void handleEvent(const sf::Event&) override {}
    virtual void update(const sf::Time& dt) override;
    virtual void draw(sf::RenderTarget& win) const override;

private:
    std::string m_msg;
    float m_timeout = 1.5f;
};
#endif