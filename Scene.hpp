#pragma once
#include <string>
#include <SFML/Window/Event.hpp>

#include "SceneManager.hpp"


class Scene {
    public:
        virtual auto drawScene() -> void = 0;
        virtual auto updateScene(double deltaTime) -> void = 0;
        virtual auto processEvent(sf::Event& event) -> void = 0;

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