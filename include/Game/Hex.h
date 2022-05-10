#pragma once
#ifndef Hex_H
#define Hex_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#include "Colors.h"

class Hex : public sf::Transformable {
public:
    /// algorithms

    void setParent(Hex* parent);
    Hex* getParent();

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
    bool m_blocked = false;
    sf::Color m_color = Colors::LightGreen;

    sf::CircleShape m_shape{30, 6};
};

#endif