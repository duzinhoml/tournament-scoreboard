# Tournament Scoreboard 🏆

A modern C++ object-oriented tournament management and scoreboard application. It supports team registrations, match results tracking, pluggable scoring rules (e.g. Win/Draw/Loss vs. Win/Loss), and sorted league standings.

## Features

- **Object-Oriented Design:** Clear separation of concerns between `Team`, `Match`, `Tournament`, and `ScoringRule`.
- **Strategy Pattern for Scoring:** Pluggable scoring rules using the `ScoringRule` abstract base class:
  - `WinDrawLossRule`: 3 points for a win, 1 point for a draw, 0 for a loss.
  - `WinLossRule`: 3 points for a win, 0 for draws/losses.
- **Sorted Standings:** Standings are automatically ranked in descending order by points (with tiebreakers for wins and team name).
- **Validation:** Enforces non-empty team names, unique registrations, and valid non-negative match scores between registered teams.

## Project Structure

```text
tournament-scoreboard/
├── README.md
├── include/
│   └── Tournament.h     # Header file defining Team, Match, ScoringRule, Tournament
└── src/
    ├── Tournament.cpp   # Implementation file
    └── main.cpp         # Driver program
```

## Building and Running

### Manual Compilation

Using Clang or GCC:

```bash
g++ -std=c++20 -Iinclude src/Tournament.cpp src/main.cpp -o scoreboard && ./scoreboard
```

## Example Output

```text
Team | W | D | L | Points
Devs | 1 | 0 | 0 | 3
Pros | 0 | 1 | 0 | 1
Vets | 0 | 1 | 1 | 1
```

## Future Implementation

**Planned:** `TournamentFileManager` will save and load data and reject corrupted files without replacing valid in-memory data. A future GUI will call `Tournament` methods rather than duplicate validation/scoring rules.

**Possible overload (planned):** `Tournament::registerTeam(const Team& team)` in addition to `registerTeam(const std::string&)`.

**Possible template (planned):** `template<typename T> void displayItems(const std::vector<T>& items)` with types `Team` and `Match`, using suitable display logic for each. Neither is implemented yet.
