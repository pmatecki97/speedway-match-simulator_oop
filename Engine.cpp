//
// Created by maja on 23.05.2026.
//

#include "Engine.h"
#include<iostream>

Engine::Engine(Match &match):match(match),window({800,600},"Symulator Żużlowy") {
    if (!font.loadFromFile("arial.ttf")) {
        std::cout<<"Nie wczytano czcionki";
    }
    sim_button = new Button(300,500,200,50,font,"Symuluj Bieg");
}

Engine::~Engine() {
    delete sim_button;
}

void Engine::run() {
    while (window.isOpen()) {
        handle_events();
        render();
    }
}

void Engine::handle_events() {
    sf::Event event;
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (sim_button->is_clicked(window)) {
                match.play_heat(current_heat); //startujemy wyścig
                current_heat++; //kolejny bieg
            }
        }
    }
}

void Engine::render() {
    window.clear(sf::Color(50, 50, 50));
    sim_button->render(window);
    window.display();
}
