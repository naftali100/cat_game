#include "Game.h"


#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Game/Main.h"
#include "StateManager.h"
#include "Resources.h"

Game::Game() : m_win(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y), "World"), m_stateManager(m_win) {}

void Game::loadResources() {
    Resources::loadTexture(Textures::Cat, "textures/cat.png");
    FontHolder::Instance().load(Fonts::Main, FONT_PATH);
}

void Game::run() {
    loadResources();

    m_win.setFramerateLimit(FPS);

    // initial state
    m_stateManager.pushState(std::make_unique<Main>(m_stateManager));

    sf::Clock clock;
    while (m_stateManager.isRunning()) {
        processEvents();
        update(clock.restart());
        draw();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (m_win.pollEvent(event)) {
        m_stateManager.handleEvent(event);

        switch (event.type) {
            case sf::Event::Resized:
                {  // update the view to the new size of the window
                    sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                    m_win.setView(sf::View(visibleArea));
                    break;
                }
            case sf::Event::Closed:
                m_win.close();
                m_stateManager.stop();
                break;
            case sf::Event::LostFocus:
                m_stateManager.pause();
                break;
            case sf::Event::GainedFocus:
                m_stateManager.resume();
                break;
            default:
                break;
        }
    }
}

void Game::update(sf::Time deltaTime) {
    m_stateManager.update(deltaTime);
}

void Game::draw() {
    m_win.clear(sf::Color::White);
    m_stateManager.draw(m_win);
    m_win.display();
}
