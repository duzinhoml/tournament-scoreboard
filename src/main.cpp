#include "Tournament.h"
#include <QAbstractItemView>
#include <QApplication>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QWidget>
#include <exception>

int main(int argc, char* argv[]) {
    // srand(time(0));
    // int randomNumber1{0};
    // int randomNumber2{0};
    // int randomNumber3{0};
    // int randomNumber4{0};

    // WinDrawLossRule rule;
    // Tournament tournament(rule);

    // std::string userTeam{"default"};
    // std::string opponentTeam{"default"};

    // std::cout << "Enter your team to manage: ";
    // std::cin >> userTeam;
    // tournament.registerTeam(userTeam);

    // std::vector<std::string> opponents = {};
    // for (int i = 1; i <= 3; ++i) {
    //     std::cout << "Enter opponent " << i << "'s name: ";
    //     std::cin >> opponentTeam;
    //     opponents.push_back(opponentTeam);
    //     tournament.registerTeam(opponentTeam);
    // }

    // for (int i = 0; i < 3; ++i) {
    //     randomNumber1 = rand() % 5 + 1;
    //     randomNumber2 = rand() % 5 + 1;
    //     randomNumber3 = rand() % 5 + 1;
    //     randomNumber4 = rand() % 5 + 1;

    //     tournament.recordMatch(userTeam, opponents[i], randomNumber1, randomNumber2);
    //     tournament.recordMatch(opponents[(i + 1 >= 3) ? i - 1 : i + 1], opponents[(i + 2 >= 3) ? (i - 2 < 0 ? 0 : i - 2) : i + 2], randomNumber3, randomNumber4);
    // }

    // tournament.printStandings();

    QApplication app(argc, argv);

    WinDrawLossRule rule;
    Tournament tournament(rule);

    QWidget window;
    window.setWindowTitle("Tournament Manager");

    QVBoxLayout layout(&window);

    QLabel title("Register a Team");
    QLineEdit teamInput;
    teamInput.setPlaceholderText("Enter team name");
    QPushButton addButton("Add Team");
    QLabel message("");

    QTableWidget table(0, 5);
    table.setHorizontalHeaderLabels({"Team", "W", "D", "L", "Points"});
    table.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table.setEditTriggers(QAbstractItemView::NoEditTriggers);

    layout.addWidget(&title);
    layout.addWidget(&teamInput);
    layout.addWidget(&addButton);
    layout.addWidget(&message);
    layout.addWidget(&table);

    auto updateStandings = [&]() {
        try {
            QString name = teamInput.text().trimmed();

            tournament.registerTeam(name.toStdString());

            const auto& teams = tournament.getTeams();
            table.setRowCount(static_cast<int>(teams.size()));

            for (int i = 0; i < static_cast<int>(teams.size()); i++) {
                const Team& team = teams[i];

                QStringList values = {
                    QString::fromStdString(team.getName()),
                    QString::number(team.getWins()),
                    QString::number(team.getDraws()),
                    QString::number(team.getLosses()),
                    QString::number(tournament.pointsFor(team))
                };

                for (int j = 0; j < values.size(); j++) {
                    table.setItem(i, j, new QTableWidgetItem(values[j]));
                }
            }

            message.setText("Team added: " + name);
            message.setStyleSheet("color: green;");
            teamInput.clear();

        } catch (const std::exception& error) {
            message.setText(QString::fromUtf8(error.what()));
            message.setStyleSheet("color: red;");
        }
    };

    QObject::connect(&addButton, &QPushButton::clicked, updateStandings);
    QObject::connect(&teamInput, &QLineEdit::returnPressed, updateStandings);

    window.resize(600, 400);
    window.show();

    return app.exec();
}
