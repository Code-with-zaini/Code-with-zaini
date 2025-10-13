#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <limits>

using namespace std;
using namespace std::chrono_literals;

// ANSI color helpers (optional, will work in most terminals)
static const string COLOR_RESET = "\033[0m";
static const string COLOR_CYAN = "\033[36m";
static const string COLOR_YELLOW = "\033[33m";
static const string COLOR_GREEN = "\033[32m";
static const string COLOR_RED = "\033[31m";
static const string COLOR_MAGENTA = "\033[35m";

struct PlayerNode {
    string name;
    int attempts;
    bool win;
    int correctNumber;
    PlayerNode* next;

    PlayerNode(const string& n, int a, bool w, int c)
        : name(n), attempts(a), win(w), correctNumber(c), next(nullptr) {}
};

// Head of the scoreboard linked list
static PlayerNode* scoreboardHead = nullptr;

void insertPlayerNode(const string& name, int attempts, bool win, int correctNumber) {
    PlayerNode* node = new PlayerNode(name, attempts, win, correctNumber);
    node->next = scoreboardHead;
    scoreboardHead = node;
}

void printLine(int width = 38, char ch = '=') {
    for (int i = 0; i < width; ++i) cout << ch;
    cout << "\n";
}

void printHeader(const string& title) {
    printLine();
    cout << COLOR_CYAN << "        \xF0\x9F\x8E\xAF NUMBER GUESSING GAME \xF0\x9F\x8F\x86" << COLOR_RESET << "\n"; // 🎯 🏆
    printLine();
    if (!title.empty()) {
        cout << COLOR_YELLOW << title << COLOR_RESET << "\n";
    }
}

int generateRandom(int low, int high) {
    return low + (std::rand() % (high - low + 1));
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readIntInRange(const string& prompt, int low, int high) {
    while (true) {
        cout << prompt;
        int x;
        if (cin >> x) {
            if (x >= low && x <= high) return x;
            cout << COLOR_RED << "Please enter a number between " << low << " and " << high << ".\n" << COLOR_RESET;
        } else {
            cout << COLOR_RED << "Invalid input. Please enter a number.\n" << COLOR_RESET;
            clearInput();
        }
    }
}

int chooseDifficulty() {
    cout << "\nSelect difficulty level:\n";
    cout << "1. Easy (1-50)\n";
    cout << "2. Normal (1-100)\n";
    cout << "3. Hard (1-200)\n";
    int choice = readIntInRange("Enter choice (1-3): ", 1, 3);
    if (choice == 1) return 50;
    if (choice == 2) return 100;
    return 200;
}

void displayScoreboard() {
    printHeader("Scoreboard");
    cout << "---------------------------------------------\n";
    cout << "Player Name       Attempts     Result     Number\n";
    cout << "---------------------------------------------\n";
    if (!scoreboardHead) {
        cout << COLOR_YELLOW << "(No games played yet)" << COLOR_RESET << "\n";
    }
    for (PlayerNode* cur = scoreboardHead; cur != nullptr; cur = cur->next) {
        cout.setf(std::ios::left);
        cout.width(18); cout << cur->name;
        cout.unsetf(std::ios::left);
        cout.setf(std::ios::right);
        cout.width(8); cout << cur->attempts << "     ";
        cout << (cur->win ? (COLOR_GREEN + string("\xE2\x9C\x85 Won") + COLOR_RESET)
                           : (COLOR_RED + string("\xE2\x9D\x8C Lost") + COLOR_RESET));
        cout << "     ";
        cout << cur->correctNumber;
        cout << "\n";
        cout.unsetf(std::ios::right);
    }
    cout << "---------------------------------------------\n";
}

void announceWinner(const string& name, int attempts, int correctNumber) {
    printLine(45, '-');
    cout << COLOR_GREEN << "\xF0\x9F\x8F\x86 Congratulations, " << name << "! You won!" << COLOR_RESET << "\n"; // 🏆
    cout << COLOR_MAGENTA << "\xF0\x9F\x8E\x89 Correct number: " << correctNumber
         << ", Attempts: " << attempts << COLOR_RESET << "\n"; // 🎉
    printLine(45, '-');
}

void singlePlayerMode();
void multiPlayerMode();

void singlePlayerMode() {
    clearInput();
    printHeader("[Single Player Mode]");
    cout << "Enter your name: ";
    string name;
    getline(cin, name);
    if (name.empty()) name = "Player";

    int high = chooseDifficulty();
    std::this_thread::sleep_for(300ms);

    int secret = generateRandom(1, high);
    int attempts = 0;

    cout << "\nGuess the number (1-" << high << ")" << ":\n";
    while (true) {
        int guess = readIntInRange("Your guess: ", 1, high);
        attempts++;
        if (guess == secret) {
            cout << COLOR_GREEN << "\xF0\x9F\x8E\x89 Correct!" << COLOR_RESET << " You guessed it in " << attempts << " attempts.\n";
            announceWinner(name, attempts, secret);
            insertPlayerNode(name, attempts, true, secret);
            break;
        } else if (guess < secret) {
            cout << COLOR_CYAN << "Too low!" << COLOR_RESET << " Try again...\n";
        } else {
            cout << COLOR_YELLOW << "Too high!" << COLOR_RESET << " Try again...\n";
        }
        std::this_thread::sleep_for(200ms);
    }
}

void multiPlayerMode() {
    clearInput();
    printHeader("[Multiplayer Mode]");
    cout << "Enter Player 1 name: ";
    string p1; getline(cin, p1); if (p1.empty()) p1 = "Player1";
    cout << "Enter Player 2 name: ";
    string p2; getline(cin, p2); if (p2.empty()) p2 = "Player2";

    int high = chooseDifficulty();
    std::this_thread::sleep_for(300ms);

    int secret = generateRandom(1, high);
    int attemptsP1 = 0, attemptsP2 = 0;

    cout << "\nTake turns guessing the number (1-" << high << ")" << ":\n";
    bool p1Turn = true;
    while (true) {
        string currentName = p1Turn ? p1 : p2;
        int& currentAttempts = p1Turn ? attemptsP1 : attemptsP2;

        int guess = readIntInRange(currentName + "'s guess: ", 1, high);
        currentAttempts++;

        if (guess == secret) {
            cout << COLOR_GREEN << "\xF0\x9F\x8E\x89 Correct!" << COLOR_RESET << "\n";
            announceWinner(currentName, currentAttempts, secret);
            insertPlayerNode(currentName, currentAttempts, true, secret);
            // Mark the other player as lost (for scoreboard context)
            string otherName = p1Turn ? p2 : p1;
            int otherAttempts = p1Turn ? attemptsP2 : attemptsP1;
            insertPlayerNode(otherName, otherAttempts, false, secret);
            break;
        } else if (guess < secret) {
            cout << COLOR_CYAN << "Too low!" << COLOR_RESET << "\n";
        } else {
            cout << COLOR_YELLOW << "Too high!" << COLOR_RESET << "\n";
        }
        p1Turn = !p1Turn;
        std::this_thread::sleep_for(200ms);
    }
}

void showMenu() {
    printLine();
    cout << COLOR_CYAN << "        \xF0\x9F\x8E\xAE NUMBER GUESSING GAME \xF0\x9F\x8E\xAF" << COLOR_RESET << "\n"; // 🎮 🎯
    printLine();
    cout << "1. Single Player Mode\n";
    cout << "2. Multiplayer Mode\n";
    cout << "3. View Scoreboard\n";
    cout << "4. Exit\n";
    printLine();
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    while (true) {
        showMenu();
        int choice = readIntInRange("Enter your choice: ", 1, 4);
        switch (choice) {
            case 1: singlePlayerMode(); break;
            case 2: multiPlayerMode(); break;
            case 3: displayScoreboard(); break;
            case 4:
                cout << COLOR_YELLOW << "Goodbye!" << COLOR_RESET << "\n";
                // Free linked list before exit
                while (scoreboardHead) {
                    PlayerNode* tmp = scoreboardHead;
                    scoreboardHead = scoreboardHead->next;
                    delete tmp;
                }
                return 0;
        }
        cout << "\n";
        std::this_thread::sleep_for(250ms);
    }
}
