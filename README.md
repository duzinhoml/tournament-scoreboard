# Tournament Scoreboard 🏆

A modern C++ object-oriented tournament management and scoreboard application featuring a desktop graphical interface. It supports team registrations, match results tracking, pluggable scoring rules (e.g. Win/Draw/Loss vs. Win/Loss), and sorted league standings.

---

## GUI Framework & Environment

- **GUI Framework:** **Qt 6** (specifically **Qt 6.10.3**)
- **GUI Module:** **Qt Widgets** (`QtWidgets`, `QtGui`, `QtCore`)
- **C++ Standard:** **C++17** (`CONFIG += c++17`)
- **Build System:** `qmake` via `tournament-scoreboard.pro` / Qt Creator

---

## Features

- **Graphical User Interface (Qt 6):** Modern desktop window featuring team input, interactive registration buttons, real-time status feedback, and a dynamic scoreboard table (`Team`, `W`, `D`, `L`, `Points`).
- **Object-Oriented Design:** Clear separation of concerns between domain logic (`Team`, `Match`, `Tournament`, and `ScoringRule`) and the Qt GUI layer (`main.cpp`).
- **Strategy Pattern for Scoring:** Pluggable scoring rules using the `ScoringRule` abstract base class:
  - `WinDrawLossRule`: 3 points for a win, 1 point for a draw, 0 for a loss.
  - `WinLossRule`: 3 points for a win, 0 for draws/losses.
- **Sorted Standings:** Standings are automatically ranked in descending order by points (with tiebreakers for wins and team name).
- **Validation:** Enforces non-empty team names, unique registrations, and valid non-negative match scores between registered teams with user-facing error messages in the GUI.

---

## Project Structure

```text
tournament-scoreboard/
├── README.md                  # Documentation and build/run instructions
├── tournament-scoreboard.pro  # qmake project configuration file (Qt 6)
├── include/
│   └── Tournament.h           # Core domain classes: Team, Match, ScoringRule, Tournament
└── src/
    ├── Tournament.cpp         # Domain implementation
    └── main.cpp               # Qt 6 GUI application and event handling
```

---

## Building and Running

### Prerequisites

- **Qt 6** (version **6.10.3** or later recommended) with **Qt Widgets** module installed.
- A **C++17** compatible compiler (Clang, Apple Clang, GCC, or MSVC).
- **Qt Creator** (recommended IDE) or command-line **qmake** + **make**.

---

### Option 1: Using Qt Creator (Recommended)

1. Launch **Qt Creator**.
2. Select **File > Open File or Project...**
3. Choose the [`tournament-scoreboard.pro`](file:///Users/duzinho/fgcu/tournament-scoreboard/tournament-scoreboard.pro) file from the project root.
4. Select your **Qt 6 kit** (e.g., *Qt 6.10.3 for macOS* or your platform's equivalent).
5. Click **Build** (or press <kbd>Ctrl+B</kbd> / <kbd>Cmd+B</kbd>).
6. Click **Run** (green play button or press <kbd>Ctrl+R</kbd> / <kbd>Cmd+R</kbd>) to launch the application.

---

### Option 2: Command Line (qmake + make)

1. Open a terminal and navigate to the project directory:
   ```bash
   cd tournament-scoreboard
   ```

2. Run `qmake` to generate the Makefile:
   ```bash
   qmake tournament-scoreboard.pro
   ```
   > **Note:** If `qmake` is not in your system `PATH`, specify the full path to your Qt 6 `qmake` binary. For example:
   > ```bash
   > ~/Qt/6.10.3/macos/bin/qmake tournament-scoreboard.pro
   > ```

3. Compile the application:
   ```bash
   make
   ```

4. Launch the application:
   - **macOS:**
     ```bash
     open tournament-scoreboard.app
     ```
     *(Or run the binary directly: `./tournament-scoreboard.app/Contents/MacOS/tournament-scoreboard`)*
   - **Linux / Windows:**
     ```bash
     ./tournament-scoreboard
     ```

---

### Option 3: Visual Studio Code

1. Open the project folder in VS Code.
2. Ensure you have the C/C++ extension installed and that the Qt 6 include/framework paths are configured in [`.vscode/c_cpp_properties.json`](file:///Users/duzinho/fgcu/tournament-scoreboard/.vscode/c_cpp_properties.json).
3. Run the build task via **Terminal > Run Build Task...** (<kbd>Cmd+Shift+B</kbd> / <kbd>Ctrl+Shift+B</kbd>) to execute the `Build` task.
4. Run via **Terminal > Run Task... > Run**.

---

## Future Implementation

- **Planned:** `TournamentFileManager` to save and load tournament data and reject corrupted files without replacing valid in-memory data.
- **Planned Overload:** `Tournament::registerTeam(const Team& team)` in addition to `registerTeam(const std::string&)`.
- **Planned Template:** `template<typename T> void displayItems(const std::vector<T>& items)` with types `Team` and `Match`, using suitable display logic for each.
