#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <stack>
#include "Board.h"
#include "Cat.h"
#include "Gui/button.h"
#include "State.h"
#include "Random.h"
#include "Config.h"

struct BoardState {
    Hex* hex;
    Hex* catHex;
};
class GameState : public State {
public:
    using State::State;
    void init();

    virtual void handleEvent(const sf::Event& e);
    virtual void update(const sf::Time&){
        m_resetBtn.update();
        m_undoBtn.update();
    };
    virtual void draw(sf::RenderTarget& win) const override;

    // invoke algorithem and find cat's next position
    void catMove();

private:
    void resetGame(const std::string& message, bool fromOriginal);

private:
    Cat m_cat;
    Board m_originalBoard;  // for reset level option
    Board m_board {BOARD_SIZE, Random::rnd(LEVEL_MIN, LEVEL_MAX)};
    bool m_PlayerTurn = true;
    int m_clickCount = 0;

    gui::Button m_resetBtn{"reset"};
    gui::Button m_undoBtn {"undo"};

    std::stack<BoardState> m_steps;
};

#endif
