#pragma once
#include "Constants.h"

class GameText {
private:
    sf::Text text;

public:
    GameText(sf::Font& font, const string& content, int size, sf::Vector2f position, sf::Color color)
        : text(font)
    {
        text.setFont(font);
        text.setString(content);
        text.setCharacterSize(size);
        text.setPosition(position);
        text.setFillColor(color);
    }

    void setString(const string& content) {
        text.setString(content);
    }

    void draw(sf::RenderTarget& target) const {
        target.draw(text);
    }
};