#include "../include/Tournament.h"
#include <iostream>

int main() {
    WinDrawLossRule rule;
    Tournament tournament(rule);

    tournament.registerTeam("Devs");
    tournament.registerTeam("Pros");
    tournament.registerTeam("Vets");

    tournament.recordMatch("Devs", "Vets", 2, 1);
    tournament.recordMatch("Pros", "Vets", 1, 1);

    tournament.printStandings();
    return 0;
}
