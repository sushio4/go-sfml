#pragma once
#include "../Scene.hpp"
#include "PassButton.hpp"

class PassButton;

class GameScene : public Scene {
    public:
        GameScene(std::string name, sf::RenderWindow* window, int boardsize);

        void drawScene() override;
        void updateScene(double deltaTime) override;
        void processEvent(sf::Event& e) override;

        auto updateSizes() -> void;

    private:
        enum Field : char {
            null, black, white
        };

        auto pixelToFieldCoordinates(int& x, int& y) -> void;
        //returns false if there's no empty tile adjacent to the group
        auto hasLiberties(int x, int y, Field checkedColor) -> bool;
        auto clearVisited(bool capture = false) -> void;
        auto checkForCapture(int x, int y, Field target) -> void;

        int boardsize;
        int squaresize;
        int offsetx, offsety;
        sf::Vector2u wsize;
        sf::Font font;

        Field* board = nullptr;
        bool* visited = nullptr;

        friend class PassButton;
        PassButton passbtn;

        bool blackturn = true;
        int consecutivePasses = 0;
        int highlightedx = -1;
        int highlightedy = -1;
};