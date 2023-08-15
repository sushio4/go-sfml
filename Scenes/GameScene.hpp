#pragma once
#include "../Scene.hpp"

class GameScene : public Scene {
    public:
        GameScene(std::string name, sf::RenderWindow* window, int boardsize);

        void drawScene() override;
        void updateScene(double deltaTime) override;
        void processEvent(sf::Event& e) override;

        auto updateSizes() -> void;

    private:
        auto pixelToFieldCoordinates(int& x, int& y) -> void;

        int boardsize;
        int squaresize;
        int offsetx, offsety;
        sf::Vector2u wsize;

        enum Field : char {
            null, black, white
        };

        Field* board = nullptr;
        bool blackturn = true;
        int highlightedx = -1;
        int highlightedy = -1;
};