#include "../include/Tournament.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

Team::Team(const std::string& teamName) 
    : m_name(teamName) {}

const std::string& Team::getName() const { return m_name; }
int Team::getWins() const { return m_wins; }
int Team::getDraws() const { return m_draws; }
int Team::getLosses() const { return m_losses; }
void Team::addWin() { m_wins++; }
void Team::addDraw() { m_draws++; }
void Team::addLoss() { m_losses++; }

Match::Match(const std::string& first, const std::string& second, int score1, int score2)
    : m_firstTeam{first}, m_secondTeam{second}, m_firstScore{score1}, m_secondScore{score2} {}

const std::string& Match::getFirstTeam() const { return m_firstTeam; }
const std::string& Match::getSecondTeam() const { return m_secondTeam; }
int Match::getFirstScore() const { return m_firstScore; }
int Match::getSecondScore() const { return m_secondScore; }

int WinLossRule::calculatePoints(int wins, int, int) const { return wins * 3; }
int WinDrawLossRule::calculatePoints(int wins, int draws, int) const { return wins * 3 + draws; }

Tournament::Tournament(const ScoringRule& scoringRule) 
    : m_rule{scoringRule} {}

int Tournament::findTeam(const std::string& name) const {
    for (int i = 0; i < static_cast<int>(m_teams.size()); i++) {
        if (m_teams[i].getName() == name) return i;
    }
    return -1;
}

void Tournament::registerTeam(const std::string& name) {
    if (name.empty() || name.find_first_not_of(" \t\n\r") == std::string::npos || findTeam(name) != -1)
        throw std::invalid_argument("Team name is empty or already registered");
    m_teams.emplace_back(name);
}

void Tournament::recordMatch(const std::string& first, const std::string& second, int score1, int score2) {
    int a = findTeam(first);
    int b = findTeam(second);
    if (a == -1 || b == -1 || a == b || score1 < 0 || score2 < 0)
        throw std::invalid_argument("Invalid match");

    m_matches.emplace_back(first, second, score1, score2);
    if (score1 > score2) {
        m_teams[a].addWin();
        m_teams[b].addLoss();
    } else if (score2 > score1) {
        m_teams[b].addWin();
        m_teams[a].addLoss();
    } else {
        m_teams[a].addDraw();
        m_teams[b].addDraw();
    }
}

void Tournament::printStandings() const {
    std::vector<Team> sortedTeams = m_teams;
    std::sort(sortedTeams.begin(), sortedTeams.end(), [&](const Team& a, const Team& b) {
        int pointsA = m_rule.calculatePoints(a.getWins(), a.getDraws(), a.getLosses());
        int pointsB = m_rule.calculatePoints(b.getWins(), b.getDraws(), b.getLosses());
        if (pointsA != pointsB) return pointsA > pointsB;
        if (a.getWins() != b.getWins()) return a.getWins() > b.getWins();
        return a.getName() < b.getName();
    });

    std::cout << "Team | W | D | L | Points\n";
    for (const Team& team : sortedTeams) {
        int points = m_rule.calculatePoints(team.getWins(), team.getDraws(), team.getLosses());
        std::cout << team.getName() << " | " << team.getWins() << " | "
                  << team.getDraws() << " | " << team.getLosses()
                  << " | " << points << "\n";
    }
}

const std::vector<Team>& Tournament::getTeams() const {
    return m_teams;
}

const std::vector<Match>& Tournament::getMatches() const {
    return m_matches;
}
