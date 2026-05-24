//
// Created by maja on 16.05.2026.
//

#include "Heat.h"
#include<vector>
#include<algorithm>
#include<cstdlib>
Heat::Heat(Rider *red, Rider *blue, Rider *white, Rider *yellow):red(red),blue(blue),white(white),yellow(yellow) {
    home_points =0;
    away_points =0;
}

int Heat::get_away_points() const {
    return away_points;
}

int Heat::get_home_points() const {
    return home_points;
}

int Heat::calculate_rider_score(Rider* rider) {
    int misfortune = rand() %100;
    if (misfortune<5) {
        return  -999;
    }
    else {
        int performance_on_track = rand() % 11 - 5;
        return  rider->get_strength() + performance_on_track;
    }
}

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
