#pragma once
#ifndef state_manager_h
#define state_manager_h

#include <map>
#include <stack>

#include "State.h"

class StateManager {
public:
    StateManager(sf::RenderWindow& win);

    void pushState(StatePtr);
    void replaceState(StatePtr);
    void popState();

    void handleEvent(const sf::Event&);
    void update(const sf::Time& td);
    void draw(sf::RenderTarget&);

    void stop();
    bool isRunning() const;
    sf::RenderWindow& getWin() {
        return m_win;
    }

    void pause();
    void resume();

private:
    sf::RenderWindow& m_win;
    std::stack<StatePtr> m_states;
    bool m_paused = false;
};

#endif