#include "Match.h"
#include "Engine.h"
#include "Team.h"
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(NULL));

    Team home_team("Gospodarz");
    Team away_team("Gosc");

    Match match(home_team, away_team);

    Engine engine(match);
    engine.run();

    return 0;
}