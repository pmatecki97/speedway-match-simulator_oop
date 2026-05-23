//
// Created by maja on 23.05.2026.
//

#include "Engine.h"
#include <functional>
#include<iostream>

Engine::Engine(Match &match):match(match),window({800,600},"Symulator Żużlowy") {
    if (!font.loadFromFile("arial.ttf")) {
        std::cout<<"Nie wczytano czcionki";
    }
    sim_button = new Button(300,500,200,50,font,"Symuluj Bieg");
    score_text.setFont(font);
    heat_text.setFont(font);
    score_text.setCharacterSize(40);
    heat_text.setCharacterSize(24);
    score_text.setFillColor(sf::Color::White);
    heat_text.setFillColor(sf::Color::White);
    score_text.setPosition(sf::Vector2f(340,30));
    heat_text.setPosition(sf::Vector2f(355,85));
    home_roster_text.setFont(font);
    away_roster_text.setFont(font);
    home_roster_text.setCharacterSize(20);
    away_roster_text.setCharacterSize(20);
    home_roster_text.setFillColor(sf::Color::White);
    away_roster_text.setFillColor(sf::Color::White);
    home_roster_text.setPosition(sf::Vector2f(100, 150));
    away_roster_text.setPosition(sf::Vector2f(500, 150));
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
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (sim_button->is_clicked(window)) {
                if (current_heat<=15) {
                    match.play_heat(current_heat); //startujemy wyścig
                    current_heat++; //kolejny bieg
                }
            }
        }
    }
}

void Engine::render() {
    std::string home_str = "";
    std::string away_str = "";
    for (int rider_idx=0;rider_idx<7;rider_idx++) {
        Rider* home_rider  = match.get_home_team().get_rider_ptr(rider_idx);
        Rider* away_rider  = match.get_away_team().get_rider_ptr(rider_idx);
        home_str += home_rider->get_name() + " - " + std::to_string(home_rider->get_match_points()) + "\n";
        away_str += away_rider->get_name() + " - " + std::to_string(away_rider->get_match_points()) + "\n";
    }
    home_roster_text.setString(home_str);
    away_roster_text.setString(away_str);
    score_text.setString(std::to_string(match.get_home_match_points()) + " : " + std::to_string(match.get_away_match_points())); //aktualizujemy wynik
    window.clear(sf::Color(50, 50, 50)); //czyscimy starą klatkę
    if (current_heat<=15) {
        heat_text.setString("Bieg: " + std::to_string(current_heat));
        sim_button->render(window);
    }
    else {
        heat_text.setString("Koniec Meczu");
    }
    window.draw(score_text);
    window.draw(heat_text);
    window.draw(home_roster_text);
    window.draw(away_roster_text);
    window.display();
}
