//
// Created by maja on 22.05.2026.
//

#ifndef SPEEDWAY_MW_11_292745_MATCH_H
#define SPEEDWAY_MW_11_292745_MATCH_H
#include "Team.h"
#include "Heat.h"
#include<vector>
class Match {
    Team &home_team;
    Team &away_team;
    std::vector<Heat> heats;
    int home_score;
    int away_score;
public:
    Match(Team& home_team,Team& away_team);
    void play_heat(int heat_number);
    void play_match();
    int get_home_match_points() const;
    int get_away_match_points() const;
};


#endif //SPEEDWAY_MW_11_292745_MATCH_H
