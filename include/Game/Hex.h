#pragma once
#ifndef Hex_H
#define Hex_H

#include <SFML/Graphics.hpp>
#include <vector>

enum Color{WHITE, GRAY, BLACK};

class Hex : public sf::Transformable {
public:
    void setNeighbors(std::vector<Hex*> neighbors){
        m_neighbors = neighbors;
    }

    int score() {
        return m_neighbors.size();
    };

    void setParent(Hex* parent) {
        m_BFSparent = parent;
    }

    void setColor(Color color) {
        m_BFSColor = color;
    }

    bool isVisited() const {
        return m_BFSColor == GRAY || m_BFSColor == BLACK;
    }

    void draw(sf::RenderTarget& win) {
        win.draw(m_shape, getTransform());
    }

    std::vector<Hex*> getNeighbors() const{
        return m_neighbors;
    }
    
    sf::FloatRect getGlobalBounds(){
        return m_shape.getGlobalBounds();
    }

private:
    std::vector<Hex*> m_neighbors;
    Hex* m_BFSparent = nullptr;
    Color m_BFSColor = WHITE;
    bool m_blocked = false;

    sf::CircleShape m_shape{60, 6};
};

#endif