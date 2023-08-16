#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button : public sf::RectangleShape {
    public:
        Button(const sf::Vector2f& size) : sf::RectangleShape(size) {}

        virtual auto onClick() -> void = 0;
        virtual auto draw() -> void = 0;

        inline auto isInside(int mousex, int mousey) -> bool {
            return (mousex > getPosition().x && mousey > getPosition().y &&
                mousex < getPosition().x + getSize().x &&
                mousey < getPosition().y + getSize().y);
        }

        auto tryClick(int mousex, int mousey) -> bool {
            if (isInside(mousex, mousey)) {
                onClick();
                return true;
            }

            return false;
        }        
};