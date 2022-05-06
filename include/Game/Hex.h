#pragma once
#ifndef Hex_H
#define Hex_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Colors.h"
#include "Log.h"



// TODO: move SFML stuff away?
class Hex : public sf::Transformable {
public:

    enum class VisitedState
    {
        NOT_VISITED,
        IN_PROGRESS,
        DONE
    };

    void setCostSoFar(const unsigned int cost) {
        m_costSoFar = cost;
    }

    void setNeighbors(const std::vector<Hex*>& neighbors) {
        m_neighbors = neighbors;
    }

    void addNeighnor(Hex* h) {
        m_neighbors.push_back(h);
    }

    int score() {
        int res = 0;
        for(auto n: m_neighbors){
            res += !n->isBlocked();
        }
        return res;

        // after we implement remove blocked neighbors from neighbors list
        // return m_neighbors.size();
    };

    void setParent(Hex* parent) {
        m_BFSparent = parent;
    }

    Hex* getParent() {
        return m_BFSparent;
    }

    // void setBFSState(VisitedState state) {
    //     m_BFSVisitedState = color;
    // }
    void setInProgress() {
        m_BFSVisitedState = VisitedState::IN_PROGRESS;
    }

    void setDone() {
        m_BFSVisitedState = VisitedState::DONE;
    }

    void initVisitedState() {
        m_BFSVisitedState = VisitedState::NOT_VISITED;
    }

    // void initParentForBFS() {
    //     m_BFSparent = nullptr;
    // }

    bool isVisited() const {
        return m_BFSVisitedState != VisitedState::NOT_VISITED;
    }

    unsigned int costSoFar() {
        return m_costSoFar;
    }

    void block() {
        m_blocked = true;
        // TODO: remove me from my neighbors (idk how)...
    }

    bool isBlocked() {
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

        if (m_BFSparent != nullptr) {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::util::getGlobalCenter(*this);
            line[1].position = sf::util::getGlobalCenter(*m_BFSparent);

            line[0].color = Colors::Black;
            line[1].color = Colors::LightOrange;

            win.draw(line);
        }
    }

    std::vector<Hex*> getNeighbors() const {
        return m_neighbors;
    }

    sf::FloatRect getGlobalBounds() const {
        sf::CircleShape c = m_shape;
        c.setPosition(getPosition());
        return c.getGlobalBounds();
    }

    unsigned int cost() {
        unsigned int counter = 1;
        for (auto next : getNeighbors())
            if (next->isBlocked())
                counter++;
        //TODO: check what is whith m_dest
        return counter;
    }

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