#include "GameScene.hpp"
#include "../Scene.hpp"

GameScene::GameScene(std::string name, sf::RenderWindow* window, int bsize) : Scene(name, window) {
    boardsize = bsize;
    updateSizes();
}

auto GameScene::updateSizes() -> void {
    wsize = window->getSize();
    squaresize = (wsize.x > wsize.y ? wsize.y : wsize.x) / (boardsize + 2);
    offsetx = 0.5 * (wsize.x - (boardsize - 1) * squaresize);
    offsety = 0.5 * (wsize.y - (boardsize - 1) * squaresize);
}

auto GameScene::drawScene() -> void {
    //background
    sf::RectangleShape rect({wsize.x, wsize.y});
    rect.setPosition(0,0);
    rect.setFillColor({120, 70, 40});
    window->draw(rect);

    //lines
    //horizontal
    rect.setSize({(boardsize - 1) * squaresize, 4});
    rect.setPosition(offsetx, offsety);
    rect.setFillColor({0, 0, 0});

    for(int x = 0; x < boardsize; x++) {
        window->draw(rect);
        rect.move({0, squaresize});
    } 

    //vertical
    rect.setSize({4, (boardsize - 1) * squaresize});
    rect.setPosition(offsetx, offsety);

    for(int y = 0; y < boardsize; y++) {
        window->draw(rect);
        rect.move({squaresize, 0});
    }
}

auto GameScene::updateScene(double deltaTime) -> void {}

auto GameScene::processEvent(sf::Event& ev) -> void {
    Scene::processEvent(ev);
}