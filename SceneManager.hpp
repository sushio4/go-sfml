#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Scene.hpp"

class SceneManager {
    public:
        auto addScene(Scene* newScene) -> bool;
        auto removeScene(std::string sceneName) -> bool;
        auto changeScene(std::string sceneName) -> bool;

        SceneManager(sf::RenderWindow* renderWindow);
        ~SceneManager();

    private:
        std::vector<Scene*> scenes;
        Scene* currentScene;

        sf::RenderWindow* window;

};