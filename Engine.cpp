//
// Created by maja on 23.05.2026.
//

#include "Engine.h"
#include <functional>
#include<iostream>
/* KONSTRUKTOR CAŁEJ ROZGRYWKI*/
/*Co robi:
 * -inicjalizuje okno rozgrywki,
 * -inicjalizuje przyciskk symuluj bieg (z wszystkimi jego parametrami),
 * -inicjalizuje teksty druzyn(nazwy);
 * -inicjalizuje teksty składów;
 * -inicjalizuje teksty wyniku;
 * -inicjalizuje teksty zawodnikow z danego biegu,
 * */
Engine::Engine(Match &match):match(match),window(sf::VideoMode::getDesktopMode(),"Symulator Zuzlowy",sf::Style::Fullscreen) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cout<<"Nie wczytano czcionki";
    }
    sim_button = new Button(785, 900, 350, 80, font, "Symuluj Bieg");
    score_text.setFont(font);
    heat_text.setFont(font);
    score_text.setCharacterSize(75);
    heat_text.setCharacterSize(40);
    score_text.setFillColor(sf::Color::White);
    heat_text.setFillColor(sf::Color::White);
    score_text.setPosition(sf::Vector2f(860, 50));
    heat_text.setPosition(sf::Vector2f(890, 150));
    home_roster_text.setFont(font);
    away_roster_text.setFont(font);
    home_roster_text.setCharacterSize(35);
    away_roster_text.setCharacterSize(35);
    home_roster_text.setFillColor(sf::Color::White);
    away_roster_text.setFillColor(sf::Color::White);
    home_roster_text.setPosition(sf::Vector2f(150, 350));
    away_roster_text.setPosition(sf::Vector2f(1400, 350));
    home_team_name.setFont(font);
    away_team_name.setFont(font);
    home_team_name.setCharacterSize(50);
    away_team_name.setCharacterSize(50);
    home_team_name.setFillColor(sf::Color(255, 215, 0));
    away_team_name.setFillColor(sf::Color(255, 215, 0));
    home_team_name.setString(match.get_home_team().get_team_name());
    away_team_name.setString(match.get_away_team().get_team_name());
    home_team_name.setPosition(sf::Vector2f(150, 260));
    away_team_name.setPosition(sf::Vector2f(1400, 260));
    red_helmet_text.setFont(font);
    red_helmet_text.setCharacterSize(30);
    red_helmet_text.setFillColor(sf::Color::Red);
    blue_helmet_text.setFont(font);
    blue_helmet_text.setCharacterSize(30);
    blue_helmet_text.setFillColor(sf::Color(30, 144, 255));
    white_helmet_text.setFont(font);
    white_helmet_text.setCharacterSize(30);
    white_helmet_text.setFillColor(sf::Color::White);
    yellow_helmet_text.setFont(font);
    yellow_helmet_text.setCharacterSize(30);
    yellow_helmet_text.setFillColor(sf::Color::Yellow);
}
/*destruktor*/
Engine::~Engine() {
    delete sim_button;
}
/*funkcja tworząca okno i uruchamiająca rozgrywke */
void Engine::run() {
    while (window.isOpen()) {
        handle_events();
        render();
    }
}
/* funkcja zajmuje sie obsługa zdarzeń:
 * -zamknięcie okna escape lub kliknięcie x,
 * -kliknięcie w przycisk uruchamiający kolejny bieg (w tym zmienia current heat o 1);
 * */
void Engine::handle_events() {
    sf::Event event;
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
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
/* CO ROBI FUNKCJA:
 * -wypisuje zawodnikow i punkty,
 * -ustawia czcionki,
 * -pozycje,
 * -kolory,
 * -
 * */
void Engine::render() {
    std::string home_str = "";
    std::string away_str = "";
    /* PĘTLA WYPISUJĄCA ZAWODNIKOW I PUNKTY*/
    for (int rider_idx = 0; rider_idx < 7; rider_idx++) {
        Rider* home_rider  = match.get_home_team().get_rider_ptr(rider_idx);
        Rider* away_rider  = match.get_away_team().get_rider_ptr(rider_idx);
        home_str += home_rider->get_name() + " - " + std::to_string(home_rider->get_match_points()) + "\n";
        away_str += away_rider->get_name() + " - " + std::to_string(away_rider->get_match_points()) + "\n";
    }

    home_roster_text.setString(home_str);
    away_roster_text.setString(away_str);

    score_text.setString(std::to_string(match.get_home_match_points()) + " : " + std::to_string(match.get_away_match_points()));

    sf::FloatRect scoreRect = score_text.getLocalBounds();
    score_text.setOrigin(scoreRect.left + scoreRect.width / 2.0f, scoreRect.top + scoreRect.height / 2.0f);
    score_text.setPosition(sf::Vector2f(960, 80));

    window.clear(sf::Color(50, 50, 50));

    if (current_heat <= 15) {
        heat_text.setString("Bieg: " + std::to_string(current_heat));

        std::vector<Rider*> starters = match.get_riders_for_heat(current_heat);

        if (starters.size() == 4) {
            red_helmet_text.setString(starters[0]->get_name());
            blue_helmet_text.setString(starters[1]->get_name());
            white_helmet_text.setString(starters[2]->get_name());
            yellow_helmet_text.setString(starters[3]->get_name());

            sf::FloatRect redRect = red_helmet_text.getLocalBounds();
            red_helmet_text.setOrigin(redRect.left + redRect.width / 2.0f, redRect.top + redRect.height / 2.0f);
            red_helmet_text.setPosition(sf::Vector2f(760, 750));

            sf::FloatRect blueRect = blue_helmet_text.getLocalBounds();
            blue_helmet_text.setOrigin(blueRect.left + blueRect.width / 2.0f, blueRect.top + blueRect.height / 2.0f);
            blue_helmet_text.setPosition(sf::Vector2f(760, 810));

            sf::FloatRect whiteRect = white_helmet_text.getLocalBounds();
            white_helmet_text.setOrigin(whiteRect.left + whiteRect.width / 2.0f, whiteRect.top + whiteRect.height / 2.0f);
            white_helmet_text.setPosition(sf::Vector2f(1160, 750));

            sf::FloatRect yellowRect = yellow_helmet_text.getLocalBounds();
            yellow_helmet_text.setOrigin(yellowRect.left + yellowRect.width / 2.0f, yellowRect.top + yellowRect.height / 2.0f);
            yellow_helmet_text.setPosition(sf::Vector2f(1160, 810));

            window.draw(red_helmet_text);
            window.draw(blue_helmet_text);
            window.draw(white_helmet_text);
            window.draw(yellow_helmet_text);
        }

        sim_button->render(window);
    } else {
        heat_text.setString("Koniec Meczu");
    }

    sf::FloatRect heatRect = heat_text.getLocalBounds();
    heat_text.setOrigin(heatRect.left + heatRect.width / 2.0f, heatRect.top + heatRect.height / 2.0f);
    heat_text.setPosition(sf::Vector2f(960, 160));

    window.draw(score_text);
    window.draw(heat_text);
    window.draw(home_roster_text);
    window.draw(away_roster_text);
    window.draw(home_team_name);
    window.draw(away_team_name);

    window.display();
}
