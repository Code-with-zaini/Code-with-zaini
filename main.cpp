#include <iostream>
#include <string>
#include <random>
#include <thread>
#include <chrono>
#include <limits>

using namespace std;

// ====== Console styling (ANSI) ======
static const string RESET = "\033[0m";
static const string BOLD = "\033[1m";
static const string DIM = "\033[2m";
static const string RED = "\033[31m";
static const string GREEN = "\033[32m";
static const string YELLOW = "\033[33m";
static const string BLUE = "\033[34m";
static const string MAGENTA = "\033[35m";
static const string CYAN = "\033[36m";

// ====== Scoreboard Linked List ======
struct PlayerNode {
    string playerName;
    int attemptsCount;
    bool didWin;
    int correctNumber; // stored for reference (not shown by default)
    PlayerNode* next;

    PlayerNode(const string& name, int attempts, bool win, int correct)
        : playerName(name), attemptsCount(attempts), didWin(win), correctNumber(correct), next(nullptr) {}
};

static PlayerNode* scoreboardHead = nullptr;
static PlayerNode* scoreboardTail = nullptr;
static int lastSecretNumber = -1; // set before inserting nodes

// ====== Utility: sleep ======
static inline void sleepMs(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

// ====== Headers ======
void printHeader(const string& title) {
    string border(38, '=');
    cout << CYAN << border << RESET << "\n";
    cout << CYAN << "        " << "\xF0\x9F\x8E\xAF" << " " << BOLD << title << RESET << " " << "\xF0\x9F\x8E\xAF" << RESET << "\n"; // 🎯
    cout << CYAN << border << RESET << "\n";
}

// ====== Input helpers ======
static string readLine(const string& prompt) {
    cout << prompt;
    cout.flush();
    string s;
    getline(cin, s);
    return s;
}

static int readInt(const string& prompt) {
    while (true) {
        cout << prompt;
        cout.flush();
        string line;
        if (!getline(cin, line)) {
            // EOF or error
            return 0;
        }
        try {
            size_t idx = 0;
            int value = stoi(line, &idx);
            if (idx != line.size()) throw invalid_argument("junk");
            return value;
        } catch (...) {
            cout << RED << "Please enter a valid integer." << RESET << "\n";
        }
    }
}

static int readIntInRange(const string& prompt, int lo, int hi) {
    while (true) {
        int v = readInt(prompt);
        if (v >= lo && v <= hi) return v;
        cout << YELLOW << "Enter a number between " << lo << " and " << hi << "." << RESET << "\n";
    }
}

// ====== RNG ======
static int generateSecretNumber(int low, int high) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

// ====== Scoreboard ops ======
void insertPlayerNode(string name, int attempts, bool win) {
    PlayerNode* node = new PlayerNode(name, attempts, win, lastSecretNumber);
    if (!scoreboardHead) {
        scoreboardHead = scoreboardTail = node;
    } else {
        scoreboardTail->next = node;
        scoreboardTail = node;
    }
}

void displayScoreboard() {
    printHeader("SCOREBOARD");
    if (!scoreboardHead) {
        cout << DIM << "No games played yet." << RESET << "\n";
        return;
    }

    cout << BOLD << "-------------------------------------" << RESET << "\n";
    cout << BOLD << "Player Name" << string(9, ' ') << "Attempts" << string(5, ' ') << "Result" << RESET << "\n";
    cout << BOLD << "-------------------------------------" << RESET << "\n";

    for (PlayerNode* p = scoreboardHead; p != nullptr; p = p->next) {
        string resultIcon = p->didWin ? (string("\xE2\x9C\x85 ") + "Won") : (string("\xE2\x9D\x8C ") + "Lost"); // ✅ / ❌
        // Column widths: Name (16), Attempts (11), Result
        string nameCol = p->playerName;
        if (nameCol.size() < 16) nameCol += string(16 - nameCol.size(), ' ');
        string attemptsCol = to_string(p->attemptsCount);
        if (attemptsCol.size() < 11) attemptsCol += string(11 - attemptsCol.size(), ' ');
        cout << nameCol << attemptsCol << resultIcon << "\n";
    }

    cout << BOLD << "-------------------------------------" << RESET << "\n";
}

// ====== Difficulty ======
struct Difficulty { int low; int high; string label; };

static Difficulty chooseDifficulty() {
    cout << MAGENTA << BOLD << "\nChoose difficulty:" << RESET << "\n";
    cout << "1. Easy (1-50)\n";
    cout << "2. Normal (1-100)\n";
    cout << "3. Hard (1-200)\n";
    int choice = readIntInRange("Select 1-3: ", 1, 3);
    switch (choice) {
        case 1: return {1, 50, "Easy"};
        case 2: return {1, 100, "Normal"};
        case 3: return {1, 200, "Hard"};
    }
    return {1, 100, "Normal"};
}

// ====== Modes ======
void singlePlayerMode();
void multiPlayerMode();

void singlePlayerMode() {
    printHeader("SINGLE PLAYER MODE");
    string playerName;
    while (playerName.empty()) {
        playerName = readLine("Enter your name: ");
        if (playerName.empty()) cout << YELLOW << "Name cannot be empty." << RESET << "\n";
    }

    Difficulty diff = chooseDifficulty();
    lastSecretNumber = generateSecretNumber(diff.low, diff.high);

    cout << CYAN << "\nGuess the number (" << diff.low << "-" << diff.high << ")" << RESET << "\n";

    int attempts = 0;
    while (true) {
        int guess = readInt("Your guess: ");
        attempts++;

        if (guess < diff.low || guess > diff.high) {
            cout << YELLOW << "Out of range. Stay within " << diff.low << "-" << diff.high << "." << RESET << "\n";
            continue;
        }

        if (guess < lastSecretNumber) {
            cout << BLUE << "Too low! Try again..." << RESET << "\n";
        } else if (guess > lastSecretNumber) {
            cout << BLUE << "Too high! Try again..." << RESET << "\n";
        } else {
            cout << GREEN << BOLD << "\n\xF0\x9F\x8E\x89 Correct!" << RESET << " You guessed it in " << attempts << " attempts." << "\n";
            cout << BOLD << "\xF0\x9F\x8F\x86 Congratulations " << playerName << "! You won!" << RESET << "\n"; // 🏆
            insertPlayerNode(playerName, attempts, true);
            // Optionally record a losing computer entry for symmetry (0 attempts)
            insertPlayerNode("Computer", 0, false);
            break;
        }

        sleepMs(200);
    }

    cout << DIM << "\nResult saved in scoreboard." << RESET << "\n";
}

void multiPlayerMode() {
    printHeader("MULTIPLAYER MODE");
    string player1, player2;
    while (player1.empty()) {
        player1 = readLine("Enter Player 1 name: ");
        if (player1.empty()) cout << YELLOW << "Name cannot be empty." << RESET << "\n";
    }
    while (player2.empty()) {
        player2 = readLine("Enter Player 2 name: ");
        if (player2.empty()) cout << YELLOW << "Name cannot be empty." << RESET << "\n";
    }

    Difficulty diff = chooseDifficulty();
    lastSecretNumber = generateSecretNumber(diff.low, diff.high);

    cout << CYAN << "\nI have a number between " << diff.low << " and " << diff.high << ". Take turns guessing!" << RESET << "\n";

    int attempts1 = 0, attempts2 = 0;
    bool player1Turn = true;

    while (true) {
        const string& currentName = player1Turn ? player1 : player2;
        int& currentAttempts = player1Turn ? attempts1 : attempts2;

        cout << BOLD << (player1Turn ? "\n[" + player1 + "]" : "\n[" + player2 + "]") << RESET << "\n";
        int guess = readInt("Your guess: ");
        currentAttempts++;

        if (guess < diff.low || guess > diff.high) {
            cout << YELLOW << "Out of range. Stay within " << diff.low << "-" << diff.high << "." << RESET << "\n";
            continue;
        }

        if (guess < lastSecretNumber) {
            cout << BLUE << "Too low!" << RESET << "\n";
        } else if (guess > lastSecretNumber) {
            cout << BLUE << "Too high!" << RESET << "\n";
        } else {
            cout << GREEN << BOLD << "\n\xF0\x9F\x8E\x89 Correct!" << RESET << "\n";
            cout << BOLD << "\xF0\x9F\x8F\x86 " << currentName << " wins in " << currentAttempts << " attempts!" << RESET << "\n";

            // Winner record
            insertPlayerNode(currentName, currentAttempts, true);
            // Loser record
            const string& loserName = player1Turn ? player2 : player1;
            int loserAttempts = player1Turn ? attempts2 : attempts1;
            insertPlayerNode(loserName, loserAttempts, false);
            break;
        }

        player1Turn = !player1Turn;
        sleepMs(150);
    }

    cout << DIM << "\nResults saved in scoreboard." << RESET << "\n";
}

// ====== Menu ======
static void showMenu() {
    printHeader("NUMBER GUESSING GAME");
    cout << BOLD
         << "1. Single Player Mode\n"
         << "2. Multiplayer Mode\n"
         << "3. View Scoreboard\n"
         << "4. Exit\n" << RESET;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        showMenu();
        int choice = readIntInRange("Enter your choice: ", 1, 4);
        cout << "\n";
        switch (choice) {
            case 1:
                singlePlayerMode();
                break;
            case 2:
                multiPlayerMode();
                break;
            case 3:
                displayScoreboard();
                break;
            case 4:
                cout << DIM << "Goodbye!" << RESET << "\n";
                // Free nodes before exit
                while (scoreboardHead) {
                    PlayerNode* nxt = scoreboardHead->next;
                    delete scoreboardHead;
                    scoreboardHead = nxt;
                }
                return 0;
        }

        cout << "\n" << DIM << "Press Enter to return to the menu..." << RESET << "\n";
        string dummy;
        getline(cin, dummy);
        cout << "\n";
    }
}
