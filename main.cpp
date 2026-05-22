#include <iostream>
#include <vector>
#include "Rider.h"
#include "Team.h"
#include "Match.h"
#include <ctime>
#include <cstdlib>

int main() {
    srand(time(NULL));

    Rider star("Bartosz", "Zmarzlik", 95);
    Rider junior("Nazar", "Parnicki", 80);
    std::vector<Rider> home_roster;
    std::vector<Rider> away_roster;
    for(int i = 0; i < 5; i++) {
        home_roster.push_back(star);
        away_roster.push_back(star);
    }
    for(int i = 0; i < 2; i++) {
        home_roster.push_back(junior);
        away_roster.push_back(junior);
    }
    Team home_team(home_roster);
    Team away_team(away_roster);

    Match match(home_team, away_team);

    std::cout << "Rozpoczynamy symulacje meczu...\n";


    match.play_match();


    std::cout << "\nKoniec meczu!\n";
    std::cout << "Gospodarze " << match.get_home_match_points()
              << " : " << match.get_away_match_points() << " Goscie\n";

    std::cout << "Punkty lidera gospodarzy (nr 9): "
              << home_team.get_rider_ptr(0)->get_match_points() << "\n";

    return 0;
}