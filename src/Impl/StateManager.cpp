#include "StateManager.h"

StateManager::StateManager(sf::RenderWindow& win) : m_win(win) {}

void StateManager::pushState(StatePtr ptr) {
    m_states.push(std::move(ptr));
    m_states.top()->init();
}

void StateManager::replaceState(StatePtr ptr){
    m_states.pop();
    m_states.push(std::move(ptr));
    m_states.top()->init();
}

void StateManager::popState() {
    if (!m_states.empty())
        m_states.pop();
}

void StateManager::handleEvent(const sf::Event& e) {
    if (m_paused)
        return;

    if (!m_states.empty()) {
        m_states.top()->handleEvent(e);
    }
}

void StateManager::update(const sf::Time& td) {
    if (m_paused)
        return;

    if (!m_states.empty()) {
        m_states.top()->update(td);
    }
}

void StateManager::draw(sf::RenderTarget& win) {
    if (m_paused)
        return;

    if (!m_states.empty()) {
        m_states.top()->draw(win);
    }
}

void StateManager::pause() {
    m_paused = true;
};

void StateManager::resume() {
    m_paused = false;
};

void StateManager::stop() {
    m_states = {};
}

bool StateManager::isRunning() const {
    return !m_states.empty();
}