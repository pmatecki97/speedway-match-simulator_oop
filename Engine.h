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
    bool is_heat_simulated=false;
    std::vector<int> last_heat_points;
    int active_substitution_helmet = -1;
    Button* sim_button;
    void handle_events();
    void render();
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
public:
    Engine(Match &match);
    ~Engine(); //destruktor
    void run();
};


#endif //SPEEDWAY_MW_11_292745_ENGINE_H
