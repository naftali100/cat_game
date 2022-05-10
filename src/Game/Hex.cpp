#include "Game/Hex.h"

void Hex::setCostSoFar(const unsigned int cost) {
    m_costSoFar = cost;
}

void Hex::setNeighbors(const std::vector<Hex*>& neighbors) {
    m_neighbors = neighbors;
}

void Hex::addNeighnor(Hex* h) {
    m_neighbors.push_back(h);
}

void Hex::setParent(Hex* parent) {
    m_BFSparent = parent;
}

Hex* Hex::getParent() {
    return m_BFSparent;
}

void Hex::setInProgress() {
    m_BFSVisitedState = VisitedState::IN_PROGRESS;
}

void Hex::setDone() {
    m_BFSVisitedState = VisitedState::DONE;
}

void Hex::initVisitedState() {
    m_BFSVisitedState = VisitedState::NOT_VISITED;
}

bool Hex::isVisited() const {
    return m_BFSVisitedState != VisitedState::NOT_VISITED;
}

unsigned int Hex::costSoFar() {
    return m_costSoFar;
}

void Hex::block() {
    m_blocked = true;
    // TODO: remove me from my neighbors (idk how)...
}

void Hex::unBlock() {
    m_blocked = false;
}

bool Hex::isBlocked() {
    return m_blocked;
}

void Hex::setColor(const sf::Color c) {
    // if (m_color != Colors::DarkGreen)
    m_color = c;
}

void Hex::draw(sf::RenderTarget& win) const {
    auto color = m_blocked ? Colors::DarkGreen : m_color;
    sf::CircleShape s = m_shape;
    s.setFillColor(color);
    s.setOutlineColor(sf::Color::Red);
    s.setPosition(getPosition());
    win.draw(s);
}

int Hex::getHeuristicCost(Hex* dest) {
    sf::Vector2f myPos = sf::Vector2f(getPosition().x / m_shape.getGlobalBounds().width,
                                      getPosition().y / m_shape.getGlobalBounds().height),
                 destPos = sf::Vector2f(dest->getPosition().x / m_shape.getGlobalBounds().width,
                                        dest->getPosition().y / m_shape.getGlobalBounds().height);
    return (int)std::floor(std::sqrt(std::pow(myPos.x - destPos.x, 2) + std::pow(myPos.y - destPos.y, 2)));
}

std::vector<Hex*> Hex::getNeighbors() const {
    return m_neighbors;
}

sf::FloatRect Hex::getGlobalBounds() const {
    sf::CircleShape c = m_shape;
    c.setPosition(getPosition());
    return c.getGlobalBounds();
}

unsigned int Hex::cost() {
    unsigned int counter = 1;
    for (auto next : getNeighbors())
        if (next->isBlocked())
            counter++;
    return counter;
}
