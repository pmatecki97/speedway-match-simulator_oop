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
void Engine::handle_match_events() {
    sf::Event event;
    while (window.pollEvent(event)) {
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
                if (current_heat <= 15) {
                    if (!is_heat_simulated) { /* maszyna stanów (przed biegiem / po biegu) */
                        std::vector<Rider*> starters = match.get_riders_for_heat(current_heat);
                        if (starters[0] != nullptr && starters[1] != nullptr && starters[2] != nullptr && starters[3] != nullptr) {
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
                        } else {
                            std::cout << "Uzupelnij sklad biegow nominowanych!\n";
                        }
                    } else {
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
void Engine::render_match() {
    std::string home_str = "";
    std::string away_str = "";

    for (int rider_idx = 0; rider_idx < 8; rider_idx++) {
        Rider* home_rider  = match.get_home_team().get_rider_ptr(rider_idx);
        Rider* away_rider  = match.get_away_team().get_rider_ptr(rider_idx);

        int home_bonus = home_rider->get_match_bonus_points();
        int away_bonus = away_rider->get_match_bonus_points();

        std::string h_b_str = "";
        if (home_bonus > 0) {
            h_b_str = "+" + std::to_string(home_bonus);
        }

        std::string a_b_str = "";
        if (away_bonus > 0) {
            a_b_str = "+" + std::to_string(away_bonus);
        }

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
                if (starters[0] != nullptr) {
                    red_helmet_text.setString(starters[0]->get_name());
                } else {
                    red_helmet_text.setString("Wybierz");
                }

                if (starters[1] != nullptr) {
                    blue_helmet_text.setString(starters[1]->get_name());
                } else {
                    blue_helmet_text.setString("Wybierz");
                }

                if (starters[2] != nullptr) {
                    white_helmet_text.setString(starters[2]->get_name());
                } else {
                    white_helmet_text.setString("Wybierz");
                }

                if (starters[3] != nullptr) {
                    yellow_helmet_text.setString(starters[3]->get_name());
                } else {
                    yellow_helmet_text.setString("Wybierz");
                }

                bool ready_to_ride = (starters[0] != nullptr && starters[1] != nullptr && starters[2] != nullptr && starters[3] != nullptr);

                if (ready_to_ride == true) {
                    sim_button->set_text("Symuluj Bieg");
                } else {
                    sim_button->set_text("Uzupelnij Sklad");
                }

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
    /* OKNO RENDEROWANE GDY DOKONUJEMY REZERWY*/
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

        for (int i = 0; i < 8; i++) {
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
/* BARDZO WAŻNE - JEST TO FUNKCJA KTÓRA DECYDUJE KTÓRY HANDLER BEDZIE WYWOŁANY ZALEŻNIE OD STANU*/
void Engine::handle_events() {
    if (current_state == GameState::MATCH) {
        handle_match_events();
    }
    else if (current_state == GameState::MAIN_MENU) {
        handle_menu_events();
    }
    else if (current_state == GameState::LINE_UP_SETUP) {
        handle_line_up_events();
    }
}
/* BARDZO WAŻNE - JEST TO FUNKCJA KTÓRA DECYDUJE CO BEDZIE WYRENDEROWANE NA MONITORZE ZALEŻNIE OD STANU*/
void Engine::render() {
    if (current_state == GameState::MATCH) {
        render_match();
    }
    else if (current_state == GameState::MAIN_MENU) {
        render_menu();
    }
    else if (current_state == GameState::LINE_UP_SETUP) {
        render_line_up();
    }
}
/* funkcja odpowiada za wyśwsietalanie menu głównego*/
void Engine::render_menu() {
    window.clear(sf::Color(30,30,30));
    /* TYTUŁ */
    sf::Text title_text;
    title_text.setFont(font);
    title_text.setCharacterSize(90);
    title_text.setFillColor(sf::Color::White);
    title_text.setString("SYMULATOR ZUZLOWY");
    sf::FloatRect titleRect = title_text.getLocalBounds();
    title_text.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
    title_text.setPosition(sf::Vector2f(960, 150));
    window.draw(title_text);
    /* TRYB GRY*/
    sf::Text mode_text;
    mode_text.setFont(font);
    mode_text.setCharacterSize(45);
    mode_text.setFillColor(sf::Color(200, 200, 200));
    mode_text.setString("Tryb: Gracz vs Komputer");
    sf::FloatRect modeRect = mode_text.getLocalBounds();
    mode_text.setOrigin(modeRect.left + modeRect.width / 2.0f, modeRect.top + modeRect.height / 2.0f);
    mode_text.setPosition(sf::Vector2f(960, 300));
    window.draw(mode_text);
    /* TEKST PODPOWIADAJĄCY JAK USTAWIĆ DRUŻYNY*/
    sf::Text inst_text;
    inst_text.setFont(font);
    inst_text.setCharacterSize(30);
    inst_text.setFillColor(sf::Color::Cyan);
    inst_text.setString("Wcisnij [1] aby edytowac Gospodarza | Wcisnij [2] aby edytowac Goscia | (Nawigacja strzalkami <- ->)");
    sf::FloatRect instRect = inst_text.getLocalBounds();
    inst_text.setOrigin(instRect.left + instRect.width / 2.0f, instRect.top + instRect.height / 2.0f);
    inst_text.setPosition(sf::Vector2f(960, 380));
    window.draw(inst_text);
    /* DRUŻYNY */
    sf::Text home_header;
    home_header.setFont(font);
    home_header.setCharacterSize(35);
    home_header.setFillColor(sf::Color(150, 150, 150));
    home_header.setString("HOME TEAM");
    sf::FloatRect hhRect = home_header.getLocalBounds();
    home_header.setOrigin(hhRect.left + hhRect.width / 2.0f, hhRect.top + hhRect.height / 2.0f);
    home_header.setPosition(sf::Vector2f(400, 450));
    window.draw(home_header);
    /* GOSPODARZE */
    sf::Text home_team;
    home_team.setFont(font);
    home_team.setCharacterSize(55);
    if (active_team_selection == 1) {
        home_team.setString("<  " + available_teams[selected_home_idx] + "  >");
        home_team.setFillColor(sf::Color(50, 205, 50));
    } else {
        home_team.setString(available_teams[selected_home_idx]);
        home_team.setFillColor(sf::Color(255, 215, 0));
    }
    sf::FloatRect home_team_rectangle = home_team.getLocalBounds();
    home_team.setOrigin(home_team_rectangle.left + home_team_rectangle.width / 2.0f, home_team_rectangle.top + home_team_rectangle.height / 2.0f);
    home_team.setPosition(sf::Vector2f(400, 580));
    window.draw(home_team);

    sf::Text away_header;
    away_header.setFont(font);
    away_header.setCharacterSize(35);
    away_header.setFillColor(sf::Color(150, 150, 150));
    away_header.setString("AWAY TEAM");
    sf::FloatRect ahRect = away_header.getLocalBounds();
    away_header.setOrigin(ahRect.left + ahRect.width / 2.0f, ahRect.top + ahRect.height / 2.0f);
    away_header.setPosition(sf::Vector2f(1520, 450));
    window.draw(away_header);
    /* GOŚCIE */
    sf::Text away_team;
    away_team.setFont(font);
    away_team.setCharacterSize(55);
    if (active_team_selection == 2) {
        away_team.setString("<  " + available_teams[selected_away_idx] + "  >");
        away_team.setFillColor(sf::Color(50, 205, 50));
    } else {
        away_team.setString(available_teams[selected_away_idx]);
        away_team.setFillColor(sf::Color(255, 215, 0));
    }
    sf::FloatRect away_team_rectangle = away_team.getLocalBounds();
    away_team.setOrigin(away_team_rectangle.left + away_team_rectangle.width / 2.0f, away_team_rectangle.top + away_team_rectangle.height / 2.0f);
    away_team.setPosition(sf::Vector2f(1520, 580));
    window.draw(away_team);
    /* PRZYCISK STARTU*/
    sf::RectangleShape start_button(sf::Vector2f(450, 100));
    start_button.setFillColor(sf::Color(34, 139, 34));
    start_button.setOutlineThickness(4);
    start_button.setOutlineColor(sf::Color(50, 205, 50));
    start_button.setOrigin(225, 50);
    start_button.setPosition(960, 850);
    window.draw(start_button);
    /* TEKST NA PRZYCISKU*/
    sf::Text start_text;
    start_text.setFont(font);
    start_text.setCharacterSize(50);
    start_text.setFillColor(sf::Color::White);
    start_text.setString("START MECZU");
    sf::FloatRect sRect = start_text.getLocalBounds();
    start_text.setOrigin(sRect.left + sRect.width / 2.0f, sRect.top + sRect.height / 2.0f);
    start_text.setPosition(sf::Vector2f(960, 835));
    window.draw(start_text);

    window.display();
}

/* funkcja obsługuje zdarzenia w menu głównym */
void Engine::handle_menu_events() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            int n = available_teams.size();

            if (event.key.code == sf::Keyboard::Num1) {
                active_team_selection = 1;
            }
            else if (event.key.code == sf::Keyboard::Num2) {
                active_team_selection = 2;
            }
            else if (event.key.code == sf::Keyboard::Right) {
                if (active_team_selection == 1) {
                    do {
                        selected_home_idx = (selected_home_idx + 1) % n;
                    } while (selected_home_idx == selected_away_idx);
                }
                else if (active_team_selection == 2) {
                    do {
                        selected_away_idx = (selected_away_idx + 1) % n;
                    } while (selected_away_idx == selected_home_idx);
                }
            }
            else if (event.key.code == sf::Keyboard::Left) {
                if (active_team_selection == 1) {
                    do {
                        selected_home_idx = (selected_home_idx - 1 + n) % n;
                    } while (selected_home_idx == selected_away_idx);
                }
                else if (active_team_selection == 2) {
                    do {
                        selected_away_idx = (selected_away_idx - 1 + n) % n;
                    } while (selected_away_idx == selected_home_idx);
                }
            }
            else if (event.key.code == sf::Keyboard::Enter) {
                home_team_name.setString(available_teams[selected_home_idx]);
                away_team_name.setString(available_teams[selected_away_idx]);

                match.get_home_team().load_from_file(available_files[selected_home_idx]);
                match.get_away_team().load_from_file(available_files[selected_away_idx]);

                current_state = GameState::LINE_UP_SETUP;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            sf::Vector2f world_pos = window.mapPixelToCoords(mouse_pos);

            sf::FloatRect start_btn_rect(735, 800, 450, 100);

            if (start_btn_rect.contains(world_pos)) {
                home_team_name.setString(available_teams[selected_home_idx]);
                away_team_name.setString(available_teams[selected_away_idx]);

                match.get_home_team().load_from_file(available_files[selected_home_idx]);
                match.get_away_team().load_from_file(available_files[selected_away_idx]);

                current_state = GameState::LINE_UP_SETUP;
            }
        }
    }
}
/* funkcja zajmuje się obsługą zdarzeń dla stanu zmiany numerów startowych zawodników */
void Engine::handle_line_up_events() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
        // ENTER ZATWIERDZA KONFIGURACJĘ
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                current_state = GameState::MATCH;
            } // LEWY I PRAWY PRZYCISK TO WYBÓR DRUŻYNY W KTÓREJ ZMIENIAMY NUMERY STARTOWE
            else if (event.key.code == sf::Keyboard::Left) {
                line_up_active_team = 1;
                line_up_selected_rider = -1;
            }
            else if (event.key.code == sf::Keyboard::Right) {
                line_up_active_team = 2;
                line_up_selected_rider = -1;
            }
            else {
                int pressed_idx = -1;
                if (event.key.code == sf::Keyboard::Num1) pressed_idx = 0;
                else if (event.key.code == sf::Keyboard::Num2) pressed_idx = 1;
                else if (event.key.code == sf::Keyboard::Num3) pressed_idx = 2;
                else if (event.key.code == sf::Keyboard::Num4) pressed_idx = 3;
                else if (event.key.code == sf::Keyboard::Num5) pressed_idx = 4;
                else if (event.key.code == sf::Keyboard::Num6) pressed_idx = 5;
                else if (event.key.code == sf::Keyboard::Num7) pressed_idx = 6;

                if (pressed_idx != -1) {
                    if (line_up_selected_rider == -1) {
                        line_up_selected_rider = pressed_idx; // WYBIERAMY ZAWODNIKA PIERWSZEGO
                    } else {
                        if (line_up_active_team == 1) { // WYBIERAMY ZAWODNIKA DRUGIEGA
                            match.get_home_team().swap_riders(line_up_selected_rider, pressed_idx);
                        } else {
                            match.get_away_team().swap_riders(line_up_selected_rider, pressed_idx);
                        }

                        line_up_selected_rider = -1;
                    }
                }
            }
        }
    }
}
/* funkcja odpowiada za wyświetalnie okna ustawiania numerów startowych */
void Engine::render_line_up() {
    window.clear(sf::Color(20, 20, 20));
    /* TYTUŁ SCENY*/
    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::White);
    title.setString("USTALANIE SKLADOW");
    sf::FloatRect tRect = title.getLocalBounds();
    title.setOrigin(tRect.left + tRect.width / 2.0f, tRect.top + tRect.height / 2.0f);
    title.setPosition(sf::Vector2f(960, 80));
    window.draw(title);
    /* TEKST PODPOWIADAJĄCY JAK DOKONAĆ USTAWIENIA SKŁADU */
    sf::Text inst;
    inst.setFont(font);
    inst.setCharacterSize(25);
    inst.setFillColor(sf::Color::Cyan);
    inst.setString("<- -> Wybierz druzyne | Klawisze [1-7] wybieraja zawodnika. Wcisnij dwa numery aby zamienic ich miejscami.");
    sf::FloatRect iRect = inst.getLocalBounds();
    inst.setOrigin(iRect.left + iRect.width / 2.0f, iRect.top + iRect.height / 2.0f);
    inst.setPosition(sf::Vector2f(960, 150));
    window.draw(inst);
    /* RYSOWANIE ZESPOŁU GOSPODARZY */
    sf::Text h_title;
    h_title.setFont(font);
    h_title.setCharacterSize(40);
    h_title.setString(match.get_home_team().get_team_name());
    h_title.setFillColor(line_up_active_team == 1 ? sf::Color::White : sf::Color(100, 100, 100)); // jesli aktywowana jest zmiana na danym zespole to swieci sie na biało
    h_title.setPosition(300, 250);
    window.draw(h_title);

    for (int i = 0; i < 8; i++) {
        sf::Text r_text;
        r_text.setFont(font);
        r_text.setCharacterSize(35);
        r_text.setString(std::to_string(i + 1) + ". " + match.get_home_team().get_rider_ptr(i)->get_name());

        if (line_up_active_team == 1) {
            if (line_up_selected_rider == i) r_text.setFillColor(sf::Color::Green);
            else r_text.setFillColor(sf::Color::Yellow);
        } else {
            r_text.setFillColor(sf::Color(100, 100, 100));
        }

        r_text.setPosition(300, 350 + i * 60);
        window.draw(r_text);
    }
    /* RYSOWANIE ZESPOŁU GOŚCI */
    sf::Text a_title;
    a_title.setFont(font);
    a_title.setCharacterSize(40);
    a_title.setString(match.get_away_team().get_team_name());
    a_title.setFillColor(line_up_active_team == 2 ? sf::Color::White : sf::Color(100, 100, 100));
    a_title.setPosition(1200, 250);
    window.draw(a_title);

    for (int i = 0; i < 8; i++) {
        sf::Text r_text;
        r_text.setFont(font);
        r_text.setCharacterSize(35);
        r_text.setString(std::to_string(i + 9) + ". " + match.get_away_team().get_rider_ptr(i)->get_name());

        if (line_up_active_team == 2) {
            if (line_up_selected_rider == i) r_text.setFillColor(sf::Color::Green);
            else r_text.setFillColor(sf::Color::Yellow);
        } else {
            r_text.setFillColor(sf::Color(100, 100, 100));
        }

        r_text.setPosition(1200, 350 + i * 60);
        window.draw(r_text);
    }
    /* TEKST INFORMACYJNY */
    sf::Text start_msg;
    start_msg.setFont(font);
    start_msg.setCharacterSize(40);
    start_msg.setFillColor(sf::Color(50, 205, 50));
    start_msg.setString("Nacisnij ENTER aby przejsc do 1. biegu!");
    sf::FloatRect smRect = start_msg.getLocalBounds();
    start_msg.setOrigin(smRect.left + smRect.width / 2.0f, smRect.top + smRect.height / 2.0f);
    start_msg.setPosition(sf::Vector2f(960, 950));
    window.draw(start_msg);

    window.display();
}