#include "../include/Tournament.h"
#include <iostream>

int main() {
    srand(time(0));
    int randomNumber1{0};
    int randomNumber2{0};
    int randomNumber3{0};
    int randomNumber4{0};

    WinDrawLossRule rule;
    Tournament tournament(rule);

    std::string userTeam{"default"};
    std::string opponentTeam{"default"};

    std::cout << "Enter your team to manage: ";
    std::cin >> userTeam;
    tournament.registerTeam(userTeam);

    std::vector<std::string> opponents = {};
    for (int i = 1; i <= 3; ++i) {
        std::cout << "Enter opponent " << i << "'s name: ";
        std::cin >> opponentTeam;
        opponents.push_back(opponentTeam);
        tournament.registerTeam(opponentTeam);
    }

    for (int i = 0; i < 3; ++i) {
        randomNumber1 = rand() % 5 + 1;
        randomNumber2 = rand() % 5 + 1;
        randomNumber3 = rand() % 5 + 1;
        randomNumber4 = rand() % 5 + 1;

        tournament.recordMatch(userTeam, opponents[i], randomNumber1, randomNumber2);
        tournament.recordMatch(opponents[(i + 1 >= 3) ? i - 1 : i + 1], opponents[(i + 2 >= 3) ? (i - 2 < 0 ? 0 : i - 2) : i + 2], randomNumber3, randomNumber4);
    }

    tournament.printStandings();
    return 0;
}
