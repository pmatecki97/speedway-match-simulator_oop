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
public:
    Match(Team& home_team,Team& away_team);
    void play_heat(int heat_number);
    void play_match();
    int get_home_match_points() const;
    int get_away_match_points() const;
    Team& get_home_team();
    Team& get_away_team();
    std::vector<Rider*> get_riders_for_heat(int heat_number);
    void make_substitution(int heat_number, int helmet_index, int new_rider_idx, bool is_tactical);/* helmet_index (1-C 2-N 3-B 4-Z)
    new_rider_index - numer zawodnika z wektora drużyny*/
    bool is_substitution_valid(int heat_number, int helmet_index, int new_rider_idx,bool is_tactical);
};


#endif //SPEEDWAY_MW_11_292745_MATCH_H
