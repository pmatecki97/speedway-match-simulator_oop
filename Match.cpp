//
// Created by maja on 22.05.2026.
//

#include "Match.h"
/* konstruktor*/
Match::Match(Team &home_team, Team &away_team):home_team(home_team),away_team(away_team) {
    home_score = 0;
    away_score = 0;
}
/* getter punktów druzyny gości*/
int Match::get_away_match_points() const {
    return away_score;
}
/* getter punktów drużyny gospodarzy*/
int Match::get_home_match_points() const {
    return home_score;
}
/* funkcja uruchamia petle 15 wyścigów*/
void Match::play_match() {
    int heat_nr;
    for (heat_nr=1;heat_nr<=15;heat_nr++) {
        play_heat(heat_nr);
    }
}
/* funkcja uruchamia wyścig (MACIERZ MMECZU JEST TABLICĄ DWUWYMIAROWĄ ROW - NR WYSCIGU, DRUGA WSPOLRZEDNA TO ZAWODNIK Z KONKRETNYMJ NUMEREM W DRUZYNIE)*/
void Match::play_heat(int heat_number) {
    int row = heat_number - 1;
    Rider *red = home_team.get_rider_ptr(match_schedule[row][0]);
    Rider *blue = home_team.get_rider_ptr(match_schedule[row][1]);
    Rider *white = away_team.get_rider_ptr(match_schedule[row][2]);
    Rider *yellow = away_team.get_rider_ptr(match_schedule[row][3]);
    red->add_heat_start();
    blue->add_heat_start();
    yellow->add_heat_start();
    white->add_heat_start();
    Heat current_heat(red,blue,white,yellow);//KONSTRUKTOR
    current_heat.simulate_race();
    away_score += current_heat.get_away_points();
    home_score += current_heat.get_home_points();
    heats.push_back(current_heat);
}
/* getter wskaźnika na druzyne gości*/
Team &Match::get_away_team() {
    return away_team;
};
/* getter wskaźnika na druzyne gospodarzy+ */
Team &Match::get_home_team() {
    return home_team;
};
/* pobiera zawodników (ich numery) z macierzy wyścigów dodaje ich do wektora konkretnego wyścigu (przez wskaznik) i zwraca wektor danego wyścigu*/
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
/* funkcja odpowiada za zmianę zawodnika w macierzy meczu (taktyczne i zwykłe rezerwy)*/
void Match::make_substitution(int heat_number, int helmet_index, int new_rider_idx, bool is_tactical) {
    if (heat_number >= 1 && heat_number <= 15 && helmet_index >= 0 && helmet_index <= 3) {
        match_schedule[heat_number - 1][helmet_index] = new_rider_idx;

        if (is_tactical) {
            if (helmet_index == 0 || helmet_index == 1) {
                home_team.get_rider_ptr(new_rider_idx)->set_used_as_tactical();
            } else {
                away_team.get_rider_ptr(new_rider_idx)->set_used_as_tactical();
            }
        }
    }
}
/* funkcja sprawdza czy rezerwa jest mozliwa do przeprowadzenia (zwykła i taktyczna) */
bool Match::is_substitution_valid(int heat_number, int helmet_index, int new_rider_idx, bool is_tactical) {
    if (heat_number<1 || heat_number>15 || helmet_index<0 ||helmet_index>3) {
        return false;
    }
    if (helmet_index == 0 || helmet_index == 1) {
        if (match_schedule[heat_number-1][0] == new_rider_idx || match_schedule[heat_number-1][1] == new_rider_idx) {
            return false;
        }
        int scheduled_starts = 0;
        for (int i = 0; i < 15; i++) {
            if (match_schedule[i][0] == new_rider_idx || match_schedule[i][1] == new_rider_idx) {
                scheduled_starts++;
            }
        }
        Rider* sub_rider = home_team.get_rider_ptr(new_rider_idx);
        if (!is_tactical) {
            if (scheduled_starts>=5) {
                return false;
            }
        }
        if (is_tactical) {
            if (sub_rider->get_used_as_tactical()) {
                return false;
            }
            if (scheduled_starts>=6) {
                return false;
            }
            if (away_score-home_score<6) {
                return false;
            }
        }
    }
    else if (helmet_index == 2 || helmet_index == 3) {
        if (match_schedule[heat_number-1][2] == new_rider_idx || match_schedule[heat_number-1][3] == new_rider_idx) {
            return false;
        }
        int scheduled_starts = 0;
        for (int i = 0; i < 15; i++) {
            if (match_schedule[i][2] == new_rider_idx || match_schedule[i][3] == new_rider_idx) {
                scheduled_starts++;
            }
        }
        Rider* sub_rider = away_team.get_rider_ptr(new_rider_idx);
        if (!is_tactical) {
            if (scheduled_starts>=5) {
                return false;
            }
        }
        if (is_tactical) {
            if (sub_rider->get_used_as_tactical()) {
                return false;
            }
            if (scheduled_starts>=6) {
                return false;
            }
            if (home_score-away_score<6) {
                return false;
            }
        }
    }
    return true;
}
