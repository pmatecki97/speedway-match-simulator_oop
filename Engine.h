//
// Created by maja on 23.05.2026.
//

#ifndef SPEEDWAY_MW_11_292745_ENGINE_H
#define SPEEDWAY_MW_11_292745_ENGINE_H
#include "Match.h"
#include <SFML/Graphics.hpp>
#include"Button.h"

class Engine {
    sf::RenderWindow window;
    Match& match;
    sf::Font font;
    int current_heat =1;
    Button* sim_button;
    void handle_events();
    void render();

public:
    Engine(Match &match);
    ~Engine(); //destruktor
    void run();
};


#endif //SPEEDWAY_MW_11_292745_ENGINE_H
