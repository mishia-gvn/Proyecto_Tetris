#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text label;

public:
    Button(const sf::Font& font, const string& text, sf::Vector2f size,
        sf::Vector2f position, sf::Color color, int charSize)
        : label(font)
    {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(color);

        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(charSize);
        label.setFillColor(FONT_COLOR);

        sf::FloatRect bounds = label.getLocalBounds();
        label.setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));
        label.setPosition(position + size / 2.f);
    }

    void draw(sf::RenderTarget& target) const {
        target.draw(shape);
        target.draw(label);
    }

    bool isClicked(const sf::Vector2f& mousePos) const {
        return shape.getGlobalBounds().contains(mousePos);
    }
};
