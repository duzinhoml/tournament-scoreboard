#pragma once
#include <string>
#include <vector>

class Team {
    public:
        Team(const std::string& teamName);
        const std::string& getName() const;
        int getWins() const;
        int getDraws() const;
        int getLosses() const;
        void addWin();
        void addDraw();
        void addLoss();

    private:
        std::string m_name;
        int m_wins = 0;
        int m_draws = 0;
        int m_losses = 0;
};

class Match {
    public:
        Match(const std::string& first, const std::string& second, int score1, int score2);
        const std::string& getFirstTeam() const;
        const std::string& getSecondTeam() const;
        int getFirstScore() const;
        int getSecondScore() const;
    
    private:
        std::string m_firstTeam;
        std::string m_secondTeam;
        int m_firstScore;
        int m_secondScore;
};

class ScoringRule {
    public:
        virtual ~ScoringRule() = default;
        virtual int calculatePoints(int wins, int draws, int losses) const = 0;
};

class WinLossRule : public ScoringRule {
    public:
        int calculatePoints(int wins, int draws, int losses) const override;
};

class WinDrawLossRule : public ScoringRule {
    public:
        int calculatePoints(int wins, int draws, int losses) const override;
};

class Tournament {
    public:
        Tournament(const ScoringRule& scoringRule);
        void registerTeam(const std::string& name);
        void recordMatch(const std::string& first, const std::string& second, int score1, int score2);
        void printStandings() const;
        const std::vector<Team>& getTeams() const;
        const std::vector<Match>& getMatches() const;

    private:
        std::vector<Team> m_teams;
        std::vector<Match> m_matches;
        const ScoringRule& m_rule;
        int findTeam(const std::string& name) const;
};
