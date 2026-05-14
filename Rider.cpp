//
// Created by maja on 14.05.2026.
//

#include "Rider.h"
#include<ctime>
#include <cstdlib>


Rider::Rider(std::string name, std::string surname, int strength):name(name),surname(surname),strength(strength) {
    disposition_of_the_day = 0;
    is_injured = false;
}

std::string Rider::get_name() const {
    std::string fullname = name + " " + surname;
    return  fullname;
}

bool Rider::get_info_if_injured() const {
    return is_injured;
}

int Rider::get_strength() const {
    int total_strength = strength + disposition_of_the_day;
    return total_strength;
}

void Rider::disposition_of_the_day_generator() {
    int current_disposition = (rand() % 31) - 15;
    disposition_of_the_day = current_disposition;
}
