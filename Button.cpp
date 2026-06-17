//
// Created by maja on 23.05.2026.
//

#include "Button.h"
/* konstruktor przycisku prostokątnego*/
Button::Button(float x, float y, float width, float height, sf::Font &font, std::string btn_text){
    shape.setPosition(sf::Vector2f(x,y));
    shape.setSize(sf::Vector2f(width,height));
    shape.setFillColor(sf::Color(46, 204, 113));
    text.setFont(font);
    text.setString(btn_text);
    text.setCharacterSize(35);
    text.setFillColor(sf::Color::White);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x + width / 2.0f, y + height / 2.0f));
}
/* funkcja sprawdzająca czy przycisk został klikniety*/
bool Button::is_clicked(sf::RenderWindow &window) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    sf::Vector2f world_pos = window.mapPixelToCoords(mouse_pos);
    if (shape.getGlobalBounds().contains(world_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return true;
    }
    return shape.getGlobalBounds().contains(world_pos);
}
/* funkcja rysująca przycisk i jego tekst*/
void Button::render(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(text);
}
