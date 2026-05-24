#include "Match.h"
#include "Engine.h"
#include "Team.h"
#include <cstdlib>
#include <ctime>
int main() {
    srand(time(NULL));

    Team home_team("drużyna 1");
    Team away_team("drużyna 2");

    home_team.load_from_file("unia_leszno.txt");
    away_team.load_from_file("wlokniarz_czestochowa.txt");


    Match match(home_team, away_team);


    Engine engine(match);


    engine.run();

    return 0;
}