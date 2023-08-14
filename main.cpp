#include <SFML/Graphics.hpp>

#include "SceneManager.hpp"
#include "Scenes/GameScene.hpp"

#include <iostream>


int main(int argc, char* argv[]) {

    sf::RenderWindow w(sf::VideoMode(900, 600), "Go");
    w.setFramerateLimit(30);

    SceneManager smgr(&w);

    Scene* go = new GameScene("scene::go", &w, 10);
    
    smgr.addScene(go);
    smgr.changeScene("scene::go");

    sf::Event ev;
    while(w.isOpen()) {
        while(w.pollEvent(ev))
            smgr.scene()->processEvent(ev);

        //smgr.scene()->updateScene(0);
        
        smgr.scene()->drawScene();

        w.display();
    }

    return 0;
}