#include "Game/Message.h"

#include "StateManager.h"
#include "Colors.h"
#include "Resources.h"
#include "SfmlUtil.h"

void Message::update(const sf::Time& dt) {
    if (m_timeout < 0.1) {
        m_stateManager.popState();
    }
    else {
        m_timeout -= dt.asSeconds();
    }
}

void Message::draw(sf::RenderTarget& win) const {
    sf::Text text(m_msg, Resources::getFont(Fonts::Main));
    text.setOrigin(sf::util::getGlobalCenter(text));
    text.setPosition(sf::Vector2f(win.getSize() / 2u));
    text.setFillColor(Colors::Danger);
    win.draw(text);
}