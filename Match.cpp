//
// Created by maja on 22.05.2026.
//

#include "Match.h"
Match::Match(Team &home_team, Team &away_team):home_team(home_team),away_team(away_team) {
    home_score = 0;
    away_score = 0;
}

int Match::get_away_match_points() const {
    return away_score;
}

int Match::get_home_match_points() const {
    return home_score;
}

void Match::play_match() {
    int heat_nr;
    for (heat_nr=1;heat_nr<=15;heat_nr++) {
        play_heat(heat_nr);
    }
}
void Match::play_heat(int heat_number) {
    int row = heat_number - 1;
    Rider *red = home_team.get_rider_ptr(match_schedule[row][0]);
    Rider *blue = home_team.get_rider_ptr(match_schedule[row][1]);
    Rider *white = away_team.get_rider_ptr(match_schedule[row][2]);
    Rider *yellow = away_team.get_rider_ptr(match_schedule[row][3]);
    Heat current_heat(red,blue,white,yellow);
    current_heat.simulate_race();
    away_score += current_heat.get_away_points();
    home_score += current_heat.get_home_points();
    heats.push_back(current_heat);
}

Team &Match::get_away_team() {
    return away_team;
};

Team &Match::get_home_team() {
    return home_team;
};

std::vector<Rider *> Match::get_riders_for_heat(int heat_number) {
    if (heat_number<1 || heat_number>15) {
        return {};
    }
    int h1_idx = match_schedule[heat_number - 1][0];
    int h2_idx = match_schedule[heat_number - 1][1];
    int a1_idx = match_schedule[heat_number - 1][2];
    int a2_idx = match_schedule[heat_number - 1][3];

    std::vector<Rider*> starting_lineup;

    starting_lineup.push_back(home_team.get_rider_ptr(h1_idx));
    starting_lineup.push_back(home_team.get_rider_ptr(h2_idx));
    starting_lineup.push_back(away_team.get_rider_ptr(a1_idx));
    starting_lineup.push_back(away_team.get_rider_ptr(a2_idx));

    return starting_lineup;
}
