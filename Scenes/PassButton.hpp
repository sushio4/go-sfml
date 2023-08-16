#pragma once
#include "../Button.hpp"

class GameScene;

class PassButton : public Button {
    public:
        PassButton(GameScene& parentScene, const sf::Vector2f& size);
        void draw() override;
        void onClick() override;

    private:
        GameScene& parent;
};