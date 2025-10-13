#include <iostream>
#include <string>
#include <random>
#include <limits>
#include <thread>
#include <chrono>
#include <iomanip>

// ANSI color helpers (optional)
namespace Ansi {
    constexpr const char* reset = "\033[0m";
    constexpr const char* bold = "\033[1m";
    constexpr const char* dim = "\033[2m";
    constexpr const char* red = "\033[31m";
    constexpr const char* green = "\033[32m";
    constexpr const char* yellow = "\033[33m";
    constexpr const char* blue = "\033[34m";
    constexpr const char* magenta = "\033[35m";
    constexpr const char* cyan = "\033[36m";
}

// Forward declarations for required functions
void singlePlayerMode();
void multiPlayerMode();
void displayScoreboard();
void insertPlayerNode(const std::string& name, int attempts, bool win);
void printHeader(const std::string& title);

// Guess history (bonus) - singly linked list of guesses
struct GuessNode {
    int guessValue;
    GuessNode* next;
    explicit GuessNode(int value) : guessValue(value), next(nullptr) {}
};

// Player scoreboard node - singly linked list
struct PlayerNode {
    std::string playerName;
    int attemptsTaken;
    bool didWin;
    int correctNumber; // The target number of that game

    GuessNode* guessHistoryHead;  // Bonus: per-player guess history
    GuessNode* guessHistoryTail;

    PlayerNode* next;

    PlayerNode(const std::string& name,
               int attempts,
               bool win,
               int correct)
        : playerName(name),
          attemptsTaken(attempts),
          didWin(win),
          correctNumber(correct),
          guessHistoryHead(nullptr),
          guessHistoryTail(nullptr),
          next(nullptr) {}
};

// Scoreboard head/tail pointers
static PlayerNode* g_scoreboardHead = nullptr;
static PlayerNode* g_scoreboardTail = nullptr;

// Utilities
static void clearScreen() {
    std::cout << "\033[2J\033[H"; // ANSI clear + cursor home
}

static void sleepMs(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

static int readInt(const std::string& prompt, int minValue, int maxValue) {
    while (true) {
        std::cout << prompt;
        int value;
        if (std::cin >> value) {
            if (value >= minValue && value <= maxValue) {
                return value;
            }
            std::cout << Ansi::yellow << "Please enter a number between "
                      << minValue << " and " << maxValue << "." << Ansi::reset << "\n";
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << Ansi::yellow << "Invalid input. Please enter a valid integer." << Ansi::reset << "\n";
        }
    }
}

static bool readYesNo(const std::string& prompt) {
    while (true) {
        std::cout << prompt << " (y/n): ";
        std::string s;
        if (!(std::cin >> s)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (s.size() > 0) {
            char c = static_cast<char>(std::tolower(s[0]));
            if (c == 'y') return true;
            if (c == 'n') return false;
        }
        std::cout << Ansi::yellow << "Please answer with 'y' or 'n'." << Ansi::reset << "\n";
    }
}

static int randomInRange(int minValue, int maxValue) {
    static thread_local std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(minValue, maxValue);
    return dist(rng);
}

void printHeader(const std::string& title) {
    clearScreen();
    std::cout << Ansi::cyan
              << "======================================\n"
              << "        🎮 " << title << " 🎯\n"
              << "======================================\n"
              << Ansi::reset;
}

static void appendGuess(GuessNode*& head, GuessNode*& tail, int guessValue) {
    GuessNode* node = new GuessNode(guessValue);
    if (!head) {
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
}

// Extended insertion to also store correct number and guess history
static void insertPlayerNodeExtended(const std::string& name,
                                     int attempts,
                                     bool win,
                                     int correctNumber,
                                     GuessNode* historyHead,
                                     GuessNode* historyTail) {
    PlayerNode* node = new PlayerNode(name, attempts, win, correctNumber);
    node->guessHistoryHead = historyHead;
    node->guessHistoryTail = historyTail;

    if (!g_scoreboardHead) {
        g_scoreboardHead = g_scoreboardTail = node;
    } else {
        g_scoreboardTail->next = node;
        g_scoreboardTail = node;
    }
}

// Required signature from prompt (routes to extended version without history)
void insertPlayerNode(const std::string& name, int attempts, bool win) {
    insertPlayerNodeExtended(name, attempts, win, /*correctNumber*/ -1, nullptr, nullptr);
}

void displayScoreboard() {
    printHeader("SCOREBOARD");

    if (!g_scoreboardHead) {
        std::cout << Ansi::dim << "No results yet. Play a game first!" << Ansi::reset << "\n\n";
        std::cout << "Press Enter to return to menu...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }

    std::cout << "-------------------------------------\n";
    std::cout << std::left
              << std::setw(16) << "Player Name"
              << std::setw(12) << "Attempts"
              << std::setw(10) << "Result" << "\n";
    std::cout << "-------------------------------------\n";

    const PlayerNode* current = g_scoreboardHead;
    while (current) {
        std::string resultIcon = current->didWin ? "✅ Won" : "❌ Lost";
        std::cout << std::left
                  << std::setw(16) << current->playerName
                  << std::setw(12) << current->attemptsTaken
                  << std::setw(10) << resultIcon
                  << "\n";
        current = current->next;
    }
    std::cout << "-------------------------------------\n\n";

    std::cout << Ansi::dim << "Tip: Play Multiplayer to see both a win and a loss recorded." << Ansi::reset << "\n\n";
    std::cout << "Press Enter to return to menu...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

static int chooseDifficultyAndGetMax() {
    std::cout << "Choose difficulty:\n";
    std::cout << "1. Easy (1-50)\n";
    std::cout << "2. Normal (1-100)\n";
    std::cout << "3. Hard (1-200)\n";
    int choice = readInt("Enter choice: ", 1, 3);
    if (choice == 1) return 50;
    if (choice == 2) return 100;
    return 200;
}

void singlePlayerMode() {
    bool playAgain = false;
    do {
        printHeader("SINGLE PLAYER MODE");
        std::cout << "[Single Player Mode]\n";
        std::cout << "Enter your name: ";
        std::string playerName;
        // flush leftover newline if any
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, playerName);
        if (playerName.empty()) playerName = "Player";

        std::cout << "\n";
        int maxValue = chooseDifficultyAndGetMax();
        int target = randomInRange(1, maxValue);

        GuessNode* historyHead = nullptr;
        GuessNode* historyTail = nullptr;
        int attempts = 0;

        int guess = 0;
        while (true) {
            std::cout << "Guess the number (1-" << maxValue << "): ";
            if (!(std::cin >> guess)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << Ansi::yellow << "Please enter a valid integer." << Ansi::reset << "\n";
                continue;
            }
            if (guess < 1 || guess > maxValue) {
                std::cout << Ansi::yellow << "Out of range. Try again." << Ansi::reset << "\n";
                continue;
            }

            attempts++;
            appendGuess(historyHead, historyTail, guess);

            if (guess < target) {
                std::cout << Ansi::blue << "Too low! Try again..." << Ansi::reset << "\n";
            } else if (guess > target) {
                std::cout << Ansi::magenta << "Too high! Try again..." << Ansi::reset << "\n";
            } else {
                std::cout << "\n" << Ansi::green << "🎉 Correct! You guessed it in "
                          << attempts << " attempts." << Ansi::reset << "\n\n";
                std::cout << Ansi::bold << "🏆 Congratulations " << playerName << "! You won!" << Ansi::reset << "\n";
                sleepMs(500);
                insertPlayerNodeExtended(playerName, attempts, true, target, historyHead, historyTail);
                std::cout << Ansi::dim << "Result saved in scoreboard." << Ansi::reset << "\n\n";
                break;
            }
        }

        playAgain = readYesNo("Play again in Single Player mode?");
    } while (playAgain);
}

void multiPlayerMode() {
    bool playAgain = false;
    do {
        printHeader("MULTIPLAYER MODE");
        std::cout << "[Multiplayer Mode]\n";
        std::cout << "Enter Player 1 name: ";
        std::string player1Name;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, player1Name);
        if (player1Name.empty()) player1Name = "Player 1";

        std::cout << "Enter Player 2 name: ";
        std::string player2Name;
        std::getline(std::cin, player2Name);
        if (player2Name.empty()) player2Name = "Player 2";

        std::cout << "\n";
        int maxValue = chooseDifficultyAndGetMax();
        int target = randomInRange(1, maxValue);

        GuessNode* p1HistoryHead = nullptr;
        GuessNode* p1HistoryTail = nullptr;
        GuessNode* p2HistoryHead = nullptr;
        GuessNode* p2HistoryTail = nullptr;

        int p1Attempts = 0;
        int p2Attempts = 0;

        bool player1Turn = true;
        bool gameWon = false;

        while (!gameWon) {
            const std::string& currentName = player1Turn ? player1Name : player2Name;
            std::cout << Ansi::bold << "It\'s " << currentName << "\'s turn!" << Ansi::reset << "\n";
            int guess = readInt("Guess the number (1-" + std::to_string(maxValue) + "): ", 1, maxValue);

            if (player1Turn) {
                p1Attempts++;
                appendGuess(p1HistoryHead, p1HistoryTail, guess);
            } else {
                p2Attempts++;
                appendGuess(p2HistoryHead, p2HistoryTail, guess);
            }

            if (guess < target) {
                std::cout << Ansi::blue << "Too low!" << Ansi::reset << "\n\n";
            } else if (guess > target) {
                std::cout << Ansi::magenta << "Too high!" << Ansi::reset << "\n\n";
            } else {
                gameWon = true;
                const std::string& winnerName = currentName;
                const std::string& loserName = player1Turn ? player2Name : player1Name;
                int winnerAttempts = player1Turn ? p1Attempts : p2Attempts;
                int loserAttempts = player1Turn ? p2Attempts : p1Attempts;

                GuessNode* winnerHead = player1Turn ? p1HistoryHead : p2HistoryHead;
                GuessNode* winnerTail = player1Turn ? p1HistoryTail : p2HistoryTail;
                GuessNode* loserHead = player1Turn ? p2HistoryHead : p1HistoryHead;
                GuessNode* loserTail = player1Turn ? p2HistoryTail : p1HistoryTail;

                std::cout << Ansi::green << "🎉 Correct! " << winnerName
                          << " guessed the number in " << winnerAttempts
                          << " attempts." << Ansi::reset << "\n\n";
                std::cout << Ansi::bold << "🏆 Congratulations " << winnerName << "! You won!" << Ansi::reset << "\n";
                sleepMs(500);

                // Record both winner and loser
                insertPlayerNodeExtended(winnerName, winnerAttempts, true, target, winnerHead, winnerTail);
                insertPlayerNodeExtended(loserName, loserAttempts, false, target, loserHead, loserTail);
            }

            player1Turn = !player1Turn;
        }

        playAgain = readYesNo("Play another Multiplayer round?");
    } while (playAgain);
}

static void freeGuessList(GuessNode* head) {
    while (head) {
        GuessNode* next = head->next;
        delete head;
        head = next;
    }
}

static void freeScoreboard() {
    PlayerNode* current = g_scoreboardHead;
    while (current) {
        PlayerNode* next = current->next;
        freeGuessList(current->guessHistoryHead);
        delete current;
        current = next;
    }
    g_scoreboardHead = g_scoreboardTail = nullptr;
}

static void mainMenuLoop() {
    bool exitRequested = false;
    while (!exitRequested) {
        printHeader("NUMBER GUESSING GAME");
        std::cout << "1. Single Player Mode\n";
        std::cout << "2. Multiplayer Mode\n";
        std::cout << "3. View Scoreboard\n";
        std::cout << "4. Exit\n";
        std::cout << "======================================\n";
        int choice = readInt("Enter your choice: ", 1, 4);

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
                exitRequested = true;
                break;
            default:
                break;
        }
    }
}

int main() {
    // Launch menu
    mainMenuLoop();

    // Cleanup allocated memory before exit
    freeScoreboard();

    std::cout << Ansi::cyan << "Thanks for playing! Goodbye. 👋" << Ansi::reset << "\n";
    return 0;
}
