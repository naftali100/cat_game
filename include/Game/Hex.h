#pragma once
#ifndef Hex_H
#define Hex_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Colors.h"
#include "Log.h"

enum Color
{
    WHITE,
    GRAY,
    BLACK
};

// TODO: move SFML stuff away?
class Hex : public sf::Transformable {
public:
    void setNeighbors(const std::vector<Hex*>& neighbors) {
        m_neighbors = neighbors;
    }

    void addNeighnor(Hex* h) {
        m_neighbors.push_back(h);
    }

    int score() {
        return m_neighbors.size();
    };

    void setParent(Hex* parent) {
        m_BFSparent = parent;
    }

    void setBFSState(Color color) {
        m_BFSColor = color;
    }

    bool isVisited() const {
        return m_BFSColor == GRAY || m_BFSColor == BLACK;
    }

    void block() {
        m_blocked = true;
    }

    bool isBlocked(){
        return m_blocked;
    }

    void setColor(const sf::Color c) {
        // if (m_color != Colors::DarkGreen)
        m_color = c;
    }

    void draw(sf::RenderTarget& win) const {
        auto color = m_blocked ? Colors::DarkGreen : m_color;
        sf::CircleShape s = m_shape;
        s.setFillColor(color);
        // s.setOutlineThickness(1);
        s.setOutlineColor(sf::Color::Red);
        s.setPosition(getPosition());
        win.draw(s);
    }

    std::vector<Hex*> getNeighbors() const {
        return m_neighbors;
    }

    sf::FloatRect getGlobalBounds() const {
        sf::CircleShape c = m_shape;
        c.setPosition(getPosition());
        return c.getGlobalBounds();
    }

private:
    std::vector<Hex*> m_neighbors;
    Hex* m_BFSparent = nullptr;
    Color m_BFSColor = WHITE;
    bool m_blocked = false;
    sf::Color m_color = Colors::LightGreen;

    sf::CircleShape m_shape{30, 6};
};

#endif