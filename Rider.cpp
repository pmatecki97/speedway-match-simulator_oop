//
// Created by maja on 14.05.2026.
//

#include "Rider.h"
#include<ctime>
#include <cstdlib>

/* konstruktor zawodnika*/
Rider::Rider(std::string name, std::string surname, int strength):name(name),surname(surname),strength(strength) {
    disposition_of_the_day = 0;
    is_injured = false;
    match_points =0;
}
/*getter imienia i nazwiska zawodnika*/
std::string Rider::get_name() const {
    std::string fullname = name + " " + surname;
    return  fullname;
}
/* czy kontuzjowany*/
bool Rider::get_info_if_injured() const {
    return is_injured;
}
/* getter mocy zawodnika*/
int Rider::get_strength() const {
    int total_strength = strength + disposition_of_the_day;
    return total_strength;
}
/* generator dyspozycji dnia*/
void Rider::disposition_of_the_day_generator() {
    int current_disposition = (rand() % 31) - 15;
    disposition_of_the_day = current_disposition;
}
/* dodaje punkty danemu zawodnikowi */
int Rider::add_match_points(int points) {
    match_points += points;
    return match_points;
}
/* getter sumy punktów*/
int Rider::get_match_points() const {
    return match_points;
}
