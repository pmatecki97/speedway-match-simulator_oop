#include "Rider.h"
#include "Team.h"
#include "Match.h"
#include "Engine.h"
#include <vector>
#include <ctime>
#include <cstdlib>

int main() {

    srand(time(NULL));


    Rider star("Bartosz", "Zmarzlik", 98);
    Rider junior("Nazar", "Parnicki", 84);


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


    Engine game_engine(match);
    game_engine.run();

    return 0;
}