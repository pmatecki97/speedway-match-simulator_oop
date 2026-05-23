//
// Created by maja on 23.05.2026.
//

#ifndef SPEEDWAY_MW_11_292745_BUTTON_H
#define SPEEDWAY_MW_11_292745_BUTTON_H
#include<string>
#include<SFML/Graphics.hpp>

class Button {
    sf::RectangleShape shape;
    sf::Text text;
public:
    Button(float x, float y, float width, float height, sf::Font& font, std::string btn_text);
    void render(sf::RenderWindow& window);
    bool is_clicked(sf::RenderWindow& window);
};


#endif //SPEEDWAY_MW_11_292745_BUTTON_H
