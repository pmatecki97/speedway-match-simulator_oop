//
// Created by maja on 16.05.2026.
//

#ifndef SPEEDWAY_MW_11_292745_HEAT_H
#define SPEEDWAY_MW_11_292745_HEAT_H
#include"Rider.h"

class Heat {
    Rider* red;
    Rider* blue;
    Rider* white;
    Rider* yellow;
    int home_points;
    int away_points;
    int calculate_rider_score(Rider* rider);
public:
    Heat(Rider* red, Rider* blue, Rider* white, Rider* yellow);
    void simulate_race();
    int get_home_points() const;
    int get_away_points() const;

};


#endif //SPEEDWAY_MW_11_292745_HEAT_H
