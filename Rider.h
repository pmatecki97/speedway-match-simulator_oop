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
public:
    Rider(std::string name, std::string surname, int strength);
    std::string get_name() const;
    bool get_info_if_injured() const;
    void disposition_of_the_day_generator();
    int get_strength() const;
};

#endif //SPEEDWAY_MW_11_292745_RIDER_H
