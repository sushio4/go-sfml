#include "GameScene.hpp"
#include "../Scene.hpp"

GameScene::GameScene(std::string name, sf::RenderWindow* window, int bsize) : Scene(name, window) {
    boardsize = bsize;
    board = new Field[boardsize * boardsize];
    for(int i = 0; i < boardsize * boardsize; i++)
        board[i] = null;

    board[50] = white;

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
    sf::RectangleShape rect({float(wsize.x), float(wsize.y)});
    rect.setPosition(0,0);
    rect.setFillColor({120, 70, 40});
    window->draw(rect);

    //lines
    //horizontal
    rect.setSize({float((boardsize - 1) * squaresize), 4.0f});
    rect.setPosition(offsetx, offsety);
    rect.setFillColor({0, 0, 0});

    for(int x = 0; x < boardsize; x++) {
        window->draw(rect);
        rect.move({0.0f, float(squaresize)});
    } 

    //vertical
    rect.setSize({4.0f, float((boardsize - 1) * squaresize)});
    rect.setPosition(offsetx, offsety);

    for(int y = 0; y < boardsize; y++) {
        window->draw(rect);
        rect.move({float(squaresize), 0.0f});
    }

    //highlighted field
    sf::CircleShape circle(squaresize * 0.4);
    int pieceoffsetx = offsetx - squaresize * 0.4 + 2;
    int pieceoffsety = offsety - squaresize * 0.4 + 2;

    if(highlightedx >= 0) {
        if(blackturn) circle.setFillColor({0, 0, 0, 127});
        else circle.setFillColor({255, 255, 255, 127});

        circle.setPosition(pieceoffsetx + highlightedx * squaresize, pieceoffsety + highlightedy * squaresize);
        window->draw(circle);
    }

    //pieces
    for(int x = 0; x < boardsize; x++)
        for(int y = 0; y < boardsize; y++) {
            if(board[x + y * boardsize] == black)
                circle.setFillColor(sf::Color::Black);
            else if(board[x + y * boardsize] == white)
                circle.setFillColor(sf::Color::White);
            else continue;

            circle.setPosition(pieceoffsetx + x * squaresize, pieceoffsety + y * squaresize);
            window->draw(circle);
        }
}

auto GameScene::updateScene(double deltaTime) -> void {}

auto GameScene::processEvent(sf::Event& ev) -> void {
    if(ev.type == sf::Event::Closed) {
        window->close();
        return;
    }
    if(ev.type == sf::Event::MouseMoved) {
        int mousex = ev.mouseMove.x;
        int mousey = ev.mouseMove.y;

        pixelToFieldCoordinates(mousex, mousey);
        
        if(mousex < 0 || mousey < 0 || mousex >= boardsize || mousey >= boardsize) {
            highlightedx = highlightedy = -1;
            return;
        }

        highlightedx = mousex, highlightedy = mousey;
        return;
    }
    if(ev.type == sf::Event::MouseButtonReleased) {
        int mousex = ev.mouseButton.x;
        int mousey = ev.mouseButton.y;
        pixelToFieldCoordinates(mousex, mousey);

        if(mousex < 0 || mousex >= boardsize ||
            mousey < 0 || mousey >= boardsize ||
            board[mousex + mousey * boardsize] != null) return;

        if(blackturn){
            board[mousex + mousey * boardsize] = black;
            blackturn = false;
        }
        else {
            board[mousex + mousey * boardsize] = white;
            blackturn = true;
        }
    }
}

auto GameScene::pixelToFieldCoordinates(int& x, int& y) -> void {
    x -= offsetx - squaresize / 2 + 2;
    y -= offsety - squaresize / 2 + 2;

    if(x < 0 || y < 0) {
        x = y = -1;
        return;
    }

    x /= squaresize;
    y /= squaresize;
}