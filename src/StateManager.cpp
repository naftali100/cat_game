#include "StateManager.h"

#include <plog/Log.h>

StateManager::StateManager(sf::RenderWindow& win) : m_win(win) {
    LOGV << "state manager constructor - start";
    LOGV << "state manager constructor - finish";
}

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
    else {
        LOGI << "empty states stack";
    }
}

void StateManager::update(const sf::Time& td) {
    if (m_paused)
        return;

    if (!m_states.empty()) {
        m_states.top()->update(td);
    }
    else {
        LOGD << "empty states stack";
    }
}

void StateManager::draw(sf::RenderTarget& win) {
    if (m_paused)
        return;

    if (!m_states.empty()) {
        m_states.top()->draw(win);
    }
    else {
        LOGD << "empty states stack";
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