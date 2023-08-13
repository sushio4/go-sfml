#include "SceneManager.hpp"
#include <algorithm>

auto SceneManager::addScene(Scene* newScene) -> bool {
    auto name = newScene->getName();

    if(std::find_if(scenes.begin(), scenes.end(), 
        [&name](const Scene* s) { return s->getName() == name; }) != scenes.end())
        return false;

    newScene->init(this, window);
    scenes.push_back(newScene);
    return true;
}

auto SceneManager::changeScene(std::string sceneName) -> bool {
    auto it = std::find_if(scenes.begin(), scenes.end(),
            [&sceneName](const Scene* s){ return s->getName() == sceneName; });
    
    if(it == scenes.end()) return false;

    currentScene = *it;
    return true;
}

auto SceneManager::removeScene(std::string sceneName) -> bool {
    auto it = std::find_if(scenes.begin(), scenes.end(),
            [&sceneName](const Scene* s){ return s->getName() == sceneName; });
    
    if(it == scenes.end()) return false;

    scenes.erase(it);
    return true;
}

SceneManager::SceneManager(sf::RenderWindow* renderWindow) {
    window = renderWindow;
}

SceneManager::~SceneManager() {
    for(auto s : scenes)
        delete s;
}