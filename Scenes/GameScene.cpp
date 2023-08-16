#include "GameScene.hpp"
#include "../Scene.hpp"

GameScene::GameScene(std::string name, sf::RenderWindow* window, int bsize) : Scene(name, window) {
    boardsize = bsize;
    board = new Field[boardsize * boardsize];
    visited = new bool[boardsize * boardsize];

    for(int i = 0; i < boardsize * boardsize; i++)
        board[i] = null, visited[i] = false;

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

        Field placed = blackturn ? black : white;
        board[mousex + mousey * boardsize] = placed;
        blackturn = !blackturn;

        //(3 - color) changes black to white and vice versa
        Field enemy = Field(3 - placed);
        checkForCapture(mousex + 1, mousey, enemy);
        checkForCapture(mousex - 1, mousey, enemy);
        checkForCapture(mousex, mousey + 1, enemy);
        checkForCapture(mousex, mousey - 1, enemy);

        //auto-capture
        checkForCapture(mousex, mousey, placed);
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

auto GameScene::hasLiberties(int x, int y, Field checkedColor) -> bool {
        //outside the board
    if(x >= boardsize || y >= boardsize || x < 0 || y < 0 ||
        //enemy's stone => dead end
        //(3 - color) changes black to white and vice versa efficiently
        board[x + boardsize * y] == Field(3 - checkedColor) || 
        //already visited field
        visited[x + boardsize * y])
        return false;

    //finally empty intersection!
    else if(board[x + boardsize * y] == null) 
        return true;

    visited[x + y * boardsize] = true;
    //recursion alert
    //if it's neither dead end nor liberty, let's check adjacent intersections
    return (hasLiberties(x + 1, y, checkedColor) ||
            hasLiberties(x - 1, y, checkedColor) ||
            hasLiberties(x, y + 1, checkedColor) ||
            hasLiberties(x, y - 1, checkedColor));
}

auto GameScene::clearVisited(bool capture) -> void {
    if(!capture) {
        for(int i = 0; i < boardsize * boardsize; i++) 
            visited[i] = false;
        
        return;
    }

    for (int i = 0; i < boardsize * boardsize; i++) {
        if (visited[i])
            board[i] = null;

        visited[i] = false;
    }
}

auto GameScene::checkForCapture(int x, int y, Field target) -> void {
    //check if it's a valid field and if there's target here
    if(x < 0 || y < 0 || x >= boardsize || y >= boardsize ||
        board[x + y * boardsize] != target) 
            return;

    clearVisited(!hasLiberties(x, y, target));
}