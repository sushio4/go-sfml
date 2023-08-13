#include <SFML/Graphics.hpp>

#include "SceneManager.hpp"


int main(int argc, char* argv[]) {
    
    sf::RenderWindow w(sf::VideoMode(900, 600), "Go");
    w.setFramerateLimit(30);

    SceneManager smgr(&w);

    sf::Event ev;
    while(w.isOpen()) {
        while(w.pollEvent(ev))
            smgr.scene()->processEvent(ev);

        //smgr.scene()->updateScene(0);
        
        smgr.scene()->drawScene();
    }

    return 0;
}