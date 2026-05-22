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
    int match_schedule[15][4] = {
        {0, 2, 2, 0}, // Bieg 1:  9(C), 11(N) | 3(B), 1(Ż)
        {6, 5, 5, 6}, // Bieg 2: 15(C), 14(N) | 6(B), 7(Ż)
        {4, 3, 1, 4}, // Bieg 3: 13(C), 12(N) | 2(B), 5(Ż)
        {1, 5, 5, 3}, // Bieg 4: 10(C), 14(N) | 6(B), 4(Ż)
        {2, 3, 2, 3}, // Bieg 5: 11(C), 12(N) | 3(B), 4(Ż)
        {4, 6, 1, 0}, // Bieg 6: 13(C), 15(N) | 2(B), 1(Ż)
        {0, 1, 6, 4}, // Bieg 7:  9(C), 10(N) | 7(B), 5(Ż)
        {4, 5, 2, 3}, // Bieg 8: 13(C), 14(N) | 3(B), 4(Ż)
        {0, 1, 1, 0}, // Bieg 9:  9(C), 10(N) | 2(B), 1(Ż)
        {2, 3, 5, 4}, // Bieg 10: 11(C), 12(N) | 6(B), 5(Ż)
        {0, 3, 3, 0}, // Bieg 11:  9(C), 12(N) | 4(B), 1(Ż)
        {2, 6, 6, 1}, // Bieg 12: 11(C), 15(N) | 7(B), 2(Ż)
        {4, 1, 2, 4}, // Bieg 13: 13(C), 10(N) | 3(B), 5(Ż)
        {1, 2, 1, 2}, // Bieg 14: Nominowany (Tymczasowe indeksy)
        {0, 4, 0, 4}  // Bieg 15: Nominowany (Tymczasowe indeksy)
    };
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
