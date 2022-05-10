#pragma once
#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>

#include "Colors.h"
#include "Game/GameState.h"
#include "Gui/button.h"
#include "Resources.h"
#include "State.h"

class Main : public State {
public:
    using State::State;

    void init() override {
        m_welcomeMessage.setOrigin(sf::util::getGlobalCenter(m_welcomeMessage));
        m_welcomeMessage.setPosition(sf::Vector2f(m_stateManager.getWin().getSize() / 2u));
        m_welcomeMessage.setFillColor(Colors::Green);

        m_startBtn.setPosition(m_welcomeMessage.getPosition() + sf::Vector2f(-m_startBtn.getGlobalBounds().width / 2, 50));
        m_startBtn.setFunction([&]() { m_stateManager.pushState(std::make_unique<GameState>(m_stateManager)); });
    }

    virtual void handleEvent(const sf::Event& e) override {
        m_startBtn.handleEvent(e);
    }
    virtual void update(const sf::Time&) override {
        m_startBtn.update();
    }
    virtual void draw(sf::RenderTarget& win) const override {
        win.draw(m_welcomeMessage);

        m_startBtn.draw(win);
    }

private:
    gui::Button m_startBtn{"start game"};
    sf::Text m_welcomeMessage{"welcome to circle the cat game!", Resources::getFont(Fonts::Main)};
};
#endif
