#include "PassButton.hpp"
#include "GameScene.hpp"

PassButton::PassButton(GameScene& parentScene, const sf::Vector2f& size) : 
    Button(size), parent(parentScene) {
    setFillColor(sf::Color::Black);
}

void PassButton::draw() {
    parent.window->draw(*this);

    sf::Text text("PASS", parent.font, getSize().y / 2);
    text.setPosition({getPosition().x + 0.5 * (getSize().x - text.getLocalBounds().width), 
                      getPosition().y + 0.5 * (getSize().y - text.getLocalBounds().height * 1.5)});
    text.setFillColor(sf::Color::White);
    parent.window->draw(text);
}

void PassButton::onClick() {
    parent.blackturn = !parent.blackturn;
    parent.consecutivePasses++;
}