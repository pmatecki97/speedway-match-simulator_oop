//
// Created by maja on 16.05.2026.
//

#ifndef SPEEDWAY_MW_11_292745_TEAM_H
#define SPEEDWAY_MW_11_292745_TEAM_H
#include <string>
#include<vector>
#include"Rider.h"

class Team {
    std::string team_name;
    int team_points;
    std::vector<Rider> line_up;
public:
    Team(const std::string& team_name);
    void add_rider(const Rider& rider);
    void add_points(int points);
    std::string get_team_name() const;
    int get_team_points() const;
    const std::vector<Rider>& get_line_up() const;
};


#endif //SPEEDWAY_MW_11_292745_TEAM_H
