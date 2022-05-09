#include "Game/GameState.h"

#include "Colors.h"
#include "Game/BFS.h"
#include "Log.h"
#include "StateManager.h"
#include "Game/Message.h"


void GameState::init() {
    m_originalBoard = m_board;
    m_cat.setHex(m_board.getMiddle());
    m_resetBtn.setPosition({20, 50});
    m_resetBtn.setFunction([&]() { 
        m_board.reset(); 
        m_cat.setHex(m_board.getMiddle());
    });

    m_undoBtn.setPosition(sf::util::getGlobalTopRight(m_resetBtn) + sf::Vector2f(20, 0));
    m_undoBtn.setFunction([&]() {
        if (!m_steps.empty()) {
            auto step = m_steps.top();
            m_steps.pop();
            m_cat.setHex(step.catHex);
            step.hex->unBlock();
            m_clickCount--;
        }
        else {
            LOGE << "can't undo. step stack empty";
        }
    });
}

void GameState::handleEvent(const sf::Event& e) {
    m_resetBtn.handleEvent(e);
    m_undoBtn.handleEvent(e);

    if (e.type == sf::Event::MouseButtonReleased) {
        if (m_PlayerTurn) {
            auto res = m_board.positionToHex({(float)e.mouseButton.x, (float)e.mouseButton.y});
            if (res != nullptr && !res->isBlocked()) {
                m_clickCount++;
                res->block();
                m_PlayerTurn = false;
                m_steps.emplace(res, m_cat.getHex());
                catMove();
            }
        }
    }
};

void GameState::draw(sf::RenderTarget& win) const {
    m_board.draw(win);
    m_cat.draw(win);

    sf::Text clicksText("number of clicks: " + std::to_string(m_clickCount), Resources::getFont(Fonts::Main));
    clicksText.setFillColor(Colors::Black);
    clicksText.move(10, 0);
    win.draw(clicksText);

    m_resetBtn.draw(win);
    m_undoBtn.draw(win);
};

void GameState::catMove() {
    auto catHex = m_cat.getHex();
    for (auto n : catHex->getNeighbors()) {
        if (m_board.isOutside(n)) {
            resetGame("ha ha. loser! :D", true);
            return;
        }
    }

    // TODO: replace with score==0
    bool isWon = true;
    for (auto n : catHex->getNeighbors()) {
        if (!n->isBlocked()) {
            isWon = false;
            break;
        }
    }

    if (isWon) {
        resetGame("you won!!!", false);
        return;
    }

    auto newCatPos = m_board.implementUCS(catHex);
    if (newCatPos == nullptr) {
        // random
        do {
            int n = Random::rnd(0, catHex->getNeighbors().size() - 1);
            newCatPos = catHex->getNeighbors().at(n);
        } while (newCatPos->isBlocked());
    }
    m_cat.setHex(newCatPos);
    m_PlayerTurn = true;
}

void GameState::resetGame(const std::string& message, bool fromOriginal) {
    m_stateManager.pushState(std::make_unique<Message>(m_stateManager, message));
    if (fromOriginal)
        m_board = m_originalBoard;
    else {
        m_board.reset();
        m_originalBoard = m_board;
    }
    m_PlayerTurn = true;
    m_cat.setHex(m_board.getMiddle());
    m_clickCount = 0;
    while (!m_steps.empty()) m_steps.pop();
}