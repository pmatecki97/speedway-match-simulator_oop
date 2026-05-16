//
// Created by maja on 16.05.2026.
//

#include "Team.h"

Team::Team(const std::string& team_name):team_name(team_name) {
    team_points =0;
}

int Team::get_team_points() const {
    return team_points;
}

std::string Team::get_team_name() const {
    return team_name;
}

const std::vector<Rider>& Team::get_line_up() const {
    return line_up;
}

void Team::add_rider(const Rider& rider) {
    line_up.push_back(rider);
}

void Team::add_points(int points) {
    team_points += points;
}
