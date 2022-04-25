#pragma once
#ifndef Hex_H
#define Hex_H

#include <SFML/Graphics.hpp>
#include <vector>

class Hex : public sf::Transformable {
public:
    int score() {
        return m_neighbors.size();
    };

    void setParent(Hex* parent) {
        m_BFSparent = parent;
    }

    void setVisited(bool visited) {
        m_BFSVisited = visited;
    }

    void draw(sf::RenderTarget& win) {
        win.draw(m_shape, getTransform());
    }

private:
    std::vector<Hex*> m_neighbors;
    Hex* m_BFSparent = nullptr;
    bool m_BFSVisited = false;
    bool m_blocked = false;

    sf::CircleShape m_shape{60, 6};
};

#endif