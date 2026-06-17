//
// Created by maja on 16.05.2026.
//

#include "Heat.h"
#include<vector>
#include<algorithm>
#include<cstdlib>
/* konstruktor wyscigu przyjmujący wskaznik na zawodnika*/
Heat::Heat(Rider *red, Rider *blue, Rider *white, Rider *yellow):red(red),blue(blue),white(white),yellow(yellow) {
    home_points =0;
    away_points =0;
}
/* getter punktów druzyny gości W DANYM WYSCIGU*/
int Heat::get_away_points() const {
    return away_points;
}
/* getter punktów drużyny gospodarzy W DANYM WYŚIGU*/
int Heat::get_home_points() const {
    return home_points;
}
/* BARDZO WAŻNA FUNKCJA !!!!!!*/
/* WYZNACZA MOC ZAWODNKIA W DANYM BIEGU UWZGLEDNIAJĄC ZDARZENIA LOSOWE = 2% I JEGO JAZDĘ NA TORZE*/
int Heat::calculate_rider_score(Rider* rider) {
    int misfortune = rand() %100;
    if (misfortune<2) {
        return  -999;
    }
    else {
        int performance_on_track = rand() % 11 - 5;
        return  rider->get_strength() + performance_on_track;
    }
}
/* BARDZO WAŻNA FUNKCJA !!!*/
/* FUNKCJA SYMULUJE WYŚCIG POBIERAJĄC PUNKTOWY WSPÓŁCZYNNIK MOCY ZAWODNIKÓW I SORTUJĄC PARY (PUNKTY MOCY ZAWODNIKA,WSKAZNIK NA ZAWODNIKA)
 * OD NAJMNIEJSZEGO DO NAJWIĘKSZEGO ZALEZNIE OD PUNKTÓW MOCY*/
void Heat::simulate_race() {
    int score_red = calculate_rider_score(red);
    int score_blue = calculate_rider_score(blue);
    int score_yellow =  calculate_rider_score(yellow);
    int score_white = calculate_rider_score(white);

    std::vector< std::pair<int, Rider*> > results;
    results.push_back(std::make_pair(score_red,red));
    results.push_back((std::make_pair(score_blue,blue)));
    results.push_back(std::make_pair(score_white,white));
    results.push_back((std::make_pair(score_yellow,yellow)));

    std::sort(results.begin(),results.end());

    int points_award[] = {0, 1, 2, 3};
    for (int rider_idx = 0; rider_idx < 4; rider_idx++) {
        if (results[rider_idx].first == -999) {
            continue;
        }

        Rider* current_rider = results[rider_idx].second;
        int earned_points = points_award[rider_idx];


        current_rider->add_match_points(earned_points);


        if (current_rider == red || current_rider == blue) {
            home_points += earned_points;
        } else {
            away_points += earned_points;
        }
    }
}
