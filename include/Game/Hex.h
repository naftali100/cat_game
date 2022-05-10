#pragma once
#ifndef Hex_H
#define Hex_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#include "Colors.h"

class Hex : public sf::Transformable {
public:
    enum class VisitedState
    {
        NOT_VISITED,
        IN_PROGRESS,
        DONE
    };

    /// both algorithms

    void setParent(Hex* parent);
    Hex* getParent();

    /// bfs

    void setInProgress();
    void setDone();
    void initVisitedState();
    bool isVisited() const;

    /// ucs
    
    void setCostSoFar(const unsigned int cost);
    unsigned int cost();
    unsigned int costSoFar();
    int getHeuristicCost(Hex* dest);

    /// sfml

    void setColor(const sf::Color c);
    sf::FloatRect getGlobalBounds() const;
    void draw(sf::RenderTarget& win) const;

    /// game

    void setNeighbors(const std::vector<Hex*>& neighbors);
    void addNeighnor(Hex* h);
    std::vector<Hex*> getNeighbors() const;

    void block();
    void unBlock();
    bool isBlocked();

private:
    std::vector<Hex*> m_neighbors;
    Hex* m_BFSparent = nullptr;
    unsigned int m_costSoFar = 0;
    VisitedState m_BFSVisitedState = VisitedState::NOT_VISITED;
    bool m_blocked = false;
    sf::Color m_color = Colors::LightGreen;

    sf::CircleShape m_shape{30, 6};
};

#endif