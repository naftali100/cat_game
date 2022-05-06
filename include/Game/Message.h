#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H

#include <SFML/Graphics.hpp>

#include "Log.h"
#include "Resources.h"
#include "State.h"

class Message : public State {
public:
    Message(StateManager& sm, const std::string& msg) : State(sm), m_msg(msg) {}

    virtual void handleEvent(const sf::Event&) override {}
    virtual void update(const sf::Time& dt) override {
        if (m_timeout < 0.1) {
            m_stateManager.popState();
        }
        else {
            m_timeout -= dt.asSeconds();
        }
    }
    virtual void draw(sf::RenderTarget& win) const override {
        sf::Text text(m_msg, Resources::getFont(Fonts::Main));
        text.setOrigin(sf::util::getGlobalCenter(text));
        text.setPosition(sf::Vector2f(win.getSize() / 2u));
        text.setFillColor(Colors::Danger);
        win.draw(text);
    }

private:
    std::string m_msg;
    float m_timeout = 1.5f;
};
#endif