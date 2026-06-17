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
 * -kliknięcie w przycisk uruchamiający kolejny bieg (w tym zmienia current heat o 1),
 * -maszyna stanów (bieg przesymulowany czy nie),
 * -klikanie w zawodnika w celu rezerwy,
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
        if (event.type == sf::Event::KeyPressed) {
            if (active_substitution_helmet != -1) {
                int selected_rider_idx = -1;

                if (event.key.code == sf::Keyboard::Num1) selected_rider_idx = 0;
                else if (event.key.code == sf::Keyboard::Num2) selected_rider_idx = 1;
                else if (event.key.code == sf::Keyboard::Num3) selected_rider_idx = 2;
                else if (event.key.code == sf::Keyboard::Num4) selected_rider_idx = 3;
                else if (event.key.code == sf::Keyboard::Num5) selected_rider_idx = 4;
                else if (event.key.code == sf::Keyboard::Num6) selected_rider_idx = 5;
                else if (event.key.code == sf::Keyboard::Num7) selected_rider_idx = 6;

                if (selected_rider_idx != -1) {
                    bool is_tactical = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

                    if (match.is_substitution_valid(current_heat, active_substitution_helmet, selected_rider_idx, is_tactical)) {
                        match.make_substitution(current_heat, active_substitution_helmet, selected_rider_idx, is_tactical);
                        active_substitution_helmet = -1;
                    } else {
                        std::cout << "Zmiana niezgodna z regulaminem!\n";
                    }
                }
            }
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                sf::Vector2f world_pos = window.mapPixelToCoords(mouse_pos);
            if (current_heat<=15 && !is_heat_simulated) {
                if (red_helmet_text.getGlobalBounds().contains(world_pos)) {
                    active_substitution_helmet = 0;
                    std::cout << "Kliknięto czerwony kask\n";
                }
                else if(blue_helmet_text.getGlobalBounds().contains(world_pos)) {
                    active_substitution_helmet = 1;
                    std::cout << "Kliknięto niebieski kask\n";
                }
                else if(white_helmet_text.getGlobalBounds().contains(world_pos)) {
                    active_substitution_helmet = 2;
                    std::cout << "Kliknięto biały kask\n";
                }
                else if(yellow_helmet_text.getGlobalBounds().contains(world_pos)) {
                    active_substitution_helmet = 3;
                    std::cout << "Kliknięto żółty kask\n";
                }
                else if (!sim_button->is_clicked(window)) {
                    active_substitution_helmet = -1;
                }
            }
            if (sim_button->is_clicked(window)) {
                if (current_heat<=15) {
                   /*MASZYNA STANÓW !!!*/
                    if (!is_heat_simulated) {
                        std::vector<Rider*> starters = match.get_riders_for_heat(current_heat);
                        std::vector<int> pts_before_heat{
                            starters[0]->get_match_points(), starters[1]->get_match_points(),
                            starters[2]->get_match_points(), starters[3]->get_match_points(),
                        };
                        match.play_heat(current_heat);
                        last_heat_points = {
                            starters[0]->get_match_points() - pts_before_heat[0],
                            starters[1]->get_match_points() - pts_before_heat[1],
                            starters[2]->get_match_points() - pts_before_heat[2],
                            starters[3]->get_match_points() - pts_before_heat[3],
                        };
                        is_heat_simulated = true;
                    }
                    else {
                        current_heat++;
                        is_heat_simulated = false;
                        last_heat_points.clear();
                    }
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

    for (int rider_idx = 0; rider_idx < 7; rider_idx++) {
        Rider* home_rider  = match.get_home_team().get_rider_ptr(rider_idx);
        Rider* away_rider  = match.get_away_team().get_rider_ptr(rider_idx);

        int home_bonus = home_rider->get_match_bonus_points();
        int away_bonus = away_rider->get_match_bonus_points();

        std::string h_b_str = (home_bonus > 0) ? "+" + std::to_string(home_bonus) : "";
        std::string a_b_str = (away_bonus > 0) ? "+" + std::to_string(away_bonus) : "";

        home_str += home_rider->get_name() + " - " + std::to_string(home_rider->get_match_points()) + h_b_str + "\n";
        away_str += away_rider->get_name() + " - " + std::to_string(away_rider->get_match_points()) + a_b_str + "\n";
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

            if (is_heat_simulated && last_heat_points.size() == 4) {
                red_helmet_text.setString(starters[0]->get_name() + " (" + std::to_string(last_heat_points[0]) + ")");
                blue_helmet_text.setString(starters[1]->get_name() + " (" + std::to_string(last_heat_points[1]) + ")");
                white_helmet_text.setString(starters[2]->get_name() + " (" + std::to_string(last_heat_points[2]) + ")");
                yellow_helmet_text.setString(starters[3]->get_name() + " (" + std::to_string(last_heat_points[3]) + ")");

                sim_button->set_text("Nastepny Bieg");

                int home_heat_pts = last_heat_points[0] + last_heat_points[1];
                int away_heat_pts = last_heat_points[2] + last_heat_points[3];

                sf::Text heat_result_text;
                heat_result_text.setFont(font);
                heat_result_text.setCharacterSize(50);
                heat_result_text.setFillColor(sf::Color::Yellow);
                heat_result_text.setString("Wynik biegu: " + std::to_string(home_heat_pts) + " : " + std::to_string(away_heat_pts));

                sf::FloatRect hrRect = heat_result_text.getLocalBounds();
                heat_result_text.setOrigin(hrRect.left + hrRect.width / 2.0f, hrRect.top + hrRect.height / 2.0f);
                heat_result_text.setPosition(sf::Vector2f(960, 240));
                window.draw(heat_result_text);

            } else {
                red_helmet_text.setString(starters[0]->get_name());
                blue_helmet_text.setString(starters[1]->get_name());
                white_helmet_text.setString(starters[2]->get_name());
                yellow_helmet_text.setString(starters[3]->get_name());

                sim_button->set_text("Symuluj Bieg");

                sf::Text instruction_text;
                instruction_text.setFont(font);
                instruction_text.setCharacterSize(25);
                instruction_text.setFillColor(sf::Color(200, 200, 200));
                instruction_text.setString("Kliknij w kask zawodnika, aby dokonac zmiany. Przytrzymaj SHIFT dla Rezerwy Taktycznej.");

                sf::FloatRect instrRect = instruction_text.getLocalBounds();
                instruction_text.setOrigin(instrRect.left + instrRect.width / 2.0f, instrRect.top + instrRect.height / 2.0f);
                instruction_text.setPosition(sf::Vector2f(960, 1020));
                window.draw(instruction_text);
            }

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
    /* KONO DO DOKONYWANIA REZERW TAKTYCZNYCH I ZWYKŁYCH*/
    if (active_substitution_helmet != -1) {
        sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
        overlay.setFillColor(sf::Color(0, 0, 0, 200));
        window.draw(overlay);

        sf::Text menu_title;
        menu_title.setFont(font);
        menu_title.setCharacterSize(50);
        menu_title.setFillColor(sf::Color::White);
        menu_title.setString("Wybierz rezerwowego (wcisnij cyfre na klawiaturze):");
        menu_title.setPosition(sf::Vector2f(200, 150));
        window.draw(menu_title);

        Team* current_team;
        if (active_substitution_helmet == 0 || active_substitution_helmet == 1) {
            current_team = &match.get_home_team();
        } else {
            current_team = &match.get_away_team();
        }

        for (int i = 0; i < 7; i++) {
            sf::Text rider_text;
            rider_text.setFont(font);
            rider_text.setCharacterSize(40);
            rider_text.setFillColor(sf::Color::Yellow);
            rider_text.setString(std::to_string(i + 1) + ". " + current_team->get_rider_ptr(i)->get_name());
            rider_text.setPosition(sf::Vector2f(200, 250 + (i * 60)));
            window.draw(rider_text);
        }

        sf::Text tactical_info;
        tactical_info.setFont(font);
        tactical_info.setCharacterSize(30);
        tactical_info.setFillColor(sf::Color::Red);
        tactical_info.setString("Trzymaj wcisniety lewy SHIFT podczas wyboru, aby uzyc Rezerwy Taktycznej");
        tactical_info.setPosition(sf::Vector2f(200, 750));
        window.draw(tactical_info);
    }

    window.display();
}
