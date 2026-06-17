//
// Created by maja on 14.05.2026.
//
#include<string>
#ifndef SPEEDWAY_MW_11_292745_RIDER_H
#define SPEEDWAY_MW_11_292745_RIDER_H


class Rider {
    std::string name;
    std::string surname;
    int strength;
    int disposition_of_the_day;
    bool is_injured;
    int match_points;
    int heat_starts_count = 0;
    bool used_as_tactical = false;
    int match_bonus_points = 0;
public:
    Rider(std::string name, std::string surname, int strength);
    std::string get_name() const;
    bool get_info_if_injured() const;
    void disposition_of_the_day_generator();
    int get_strength() const;
    int add_match_points(int points);
    int get_match_points() const;
    int get_heat_starts_count() const;
    void add_heat_start();
    bool get_used_as_tactical() const;
    void set_used_as_tactical();
    void add_match_bonus_points(int points);
    int get_match_bonus_points() const;
};

#endif //SPEEDWAY_MW_11_292745_RIDER_H
