//
// Created by maja on 23.05.2026.
//

#ifndef SPEEDWAY_MW_11_292745_ENGINE_H
#define SPEEDWAY_MW_11_292745_ENGINE_H
#include "Match.h"
#include <SFML/Graphics.hpp>
#include"Button.h"
enum class GameState {
    MAIN_MENU,
    ROSTER_SETUP,
    MATCH
};

class Engine {
    GameState current_state = GameState::MAIN_MENU; //do maszyny stanów, aby dzielić wyswietlany obraz na stany
    sf::RenderWindow window;
    Match& match;
    sf::Font font;
    int current_heat =1;
    bool is_heat_simulated=false;
    std::vector<int> last_heat_points;
    int active_substitution_helmet = -1;
    Button* sim_button;
    void handle_match_events();
    void render_match();
    void render();
    void render_menu();
    void handle_events();
    void handle_menu_events();
    sf::Text score_text;
    sf::Text heat_text;
    sf::Text home_roster_text;
    sf::Text away_roster_text;
    sf::Text home_team_name;
    sf::Text away_team_name;
    sf::Text red_helmet_text;
    sf::Text blue_helmet_text;
    sf::Text white_helmet_text;
    sf::Text yellow_helmet_text;
    std::vector<std::string> available_files = {
        "unia_leszno.txt", "sparta_wroclaw.txt", "motor_lublin.txt", "apator_torun.txt",
        "stal_gorzow.txt", "wlokniarz_czestochowa.txt", "gkm_grudziadz.txt", "falubaz_zielona_gora.txt"
    };
    std::vector<std::string> available_teams = { //wektor drużyn potrzeby do menu głównego
        "Unia Leszno", "Sparta Wroclaw", "Motor Lublin", "Apator Torun",
        "Stal Gorzow", "Wlokniarz Czestochowa", "GKM Grudziadz", "Falubaz Zielona Gora"
    };
    int selected_home_idx = 0;
    int selected_away_idx = 1;
    int active_team_selection = 0; // 0 - nic, 1- gospodarze 2- goście
public:
    Engine(Match &match);
    ~Engine(); //destruktor
    void run();
};


#endif //SPEEDWAY_MW_11_292745_ENGINE_H
