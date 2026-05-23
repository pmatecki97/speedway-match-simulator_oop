//
// Created by maja on 23.05.2026.
//

#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font &font, std::string btn_text){
    shape.setPosition(sf::Vector2f(x,y));
    shape.setSize(sf::Vector2f(width,height));
    shape.setFillColor(sf::Color(70, 70, 70));
    text.setFont(font);
    text.setString(btn_text);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(x+10,y+10));
}

bool Button::is_clicked(sf::RenderWindow &window) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos.x),static_cast<float>(mouse_pos.y));
    if (shape.getGlobalBounds().contains(mouse_pos_f) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return true;
    }
    return false;
}

void Button::render(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(text);
}
