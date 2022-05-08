#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "StateManager.h"

class Game {
public:
    Game();
    void run();
    void loadResources();

    void processEvents();
    void update(sf::Time elapsedTime);
    void draw();

private:
    sf::RenderWindow m_win;
    StateManager m_stateManager;
};

#endif