#pragma once
#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Node : public sf::Transformable {
public:
    int score() {
        return m_neighbors.size();
    };

    void setParent(Node* parent) {
        m_BFSparent = parent;
    }

    void setVisited(bool visited) {
        m_visited = visited;
    }

    void draw(sf::RenderTarget& win) {
        win.draw(m_shape, getTransform());
    }

private:
    std::vector<Node*> m_neighbors;
    Node* m_BFSparent = nullptr;
    bool m_visited = false;
    bool m_blocked = false;

    sf::CircleShape m_shape{60, 6};
};

#endif