//
// Created by maja on 16.05.2026.
//

#include "Team.h"
#include <iostream>
#include <fstream>
/* konstruktor drużyny z nazwy*/
Team::Team(const std::string& team_name):team_name(team_name) {
    team_points =0;
}
/* konstruktor drużyny ze składu*/
Team::Team(const std::vector<Rider>& roster) : line_up(roster) {

}
/* getter punktów całej drużyny*/
int Team::get_team_points() const {
    return team_points;
}
/* getter nazwy drużyny*/
std::string Team::get_team_name() const {
    return team_name;
}
/* getter wektora drużyn*/
const std::vector<Rider>& Team::get_line_up() const {
    return line_up;
}
/* dodaje zawodnika do drużyny*/
void Team::add_rider(const Rider& rider) {
    line_up.push_back(rider);
}
/* dodaje punkty całej druzynie*/
void Team::add_points(int points) {
    team_points += points;
}
/* pobiera wskaźnik na zawodnika z wektora drużyny*/
Rider* Team::get_rider_ptr(int index) {
    return &line_up[index];
}
/* pobiera zawodników z plików tekstowych i dodaje ich do wektora druzyny*/
void Team::load_from_file(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout<<"Plik nie istnieje"<<std::endl;
        return;
    }
    std::string name;
    std::string surname;
    int strength;
    while (file>>name>>surname>>strength) {
        Rider new_rider(name,surname,strength);
        line_up.push_back(new_rider);
    }
    file.close();
}
