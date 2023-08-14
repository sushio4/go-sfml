#pragma once
#include <string>
#include <SFML/Window/Event.hpp>

#include "SceneManager.hpp"

class SceneManager;

class Scene {
    public:
        virtual auto drawScene() -> void = 0;
        virtual auto updateScene(double deltaTime) -> void = 0;

        virtual auto processEvent(sf::Event& event) -> void {
            if(event.type == sf::Event::Closed) window->close();
        }

        Scene(std::string name, sf::RenderWindow* window) {
            this->name = name;
            this->window = window;
        }

        auto init(SceneManager* newParent, sf::RenderWindow* renderWindow) -> bool {
            if(parent || window) return false;
            parent = newParent;
            window = renderWindow;
            return true;
        }

        inline auto getName() const -> std::string {
            return name;
        }

    protected:
        SceneManager* parent = nullptr;
        sf::RenderWindow* window = nullptr;
        std::string name;
};