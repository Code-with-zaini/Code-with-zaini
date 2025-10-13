#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <limits>

using namespace std;

// Node structure for linked list to store player data
struct PlayerNode {
    string playerName;
    int attempts;
    bool won;
    int numberGuessed;
    PlayerNode* next;
    
    // Constructor
    PlayerNode(string name, int att, bool win, int num) {
        playerName = name;
        attempts = att;
        won = win;
        numberGuessed = num;
        next = nullptr;
    }
};

// Global head pointer for scoreboard linked list
PlayerNode* head = nullptr;

// Function prototypes
void printHeader(string title);
void printSeparator();
void delay(int milliseconds);
void clearScreen();
void singlePlayerMode();
void multiPlayerMode();
void displayScoreboard();
void insertPlayerNode(string name, int attempts, bool win, int number);
void freeLinkedList();
int getValidInput();
void pressEnterToContinue();

// Print fancy header with ASCII art
void printHeader(string title) {
    cout << "\n";
    cout << "==========================================" << endl;
    cout << "        " << title << endl;
    cout << "==========================================" << endl;
}

// Print separator line
void printSeparator() {
    cout << "==========================================\n";
}

// Add delay for animations
void delay(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

// Clear screen (cross-platform)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Get valid integer input
int getValidInput() {
    int input;
    while (!(cin >> input)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

// Press enter to continue
void pressEnterToContinue() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

// Single Player Mode
void singlePlayerMode() {
    clearScreen();
    printHeader("🎯 SINGLE PLAYER MODE 🎯");
    
    string playerName;
    cout << "\nEnter your name: ";
    getline(cin, playerName);
    
    // Generate random number between 1-100
    int targetNumber = (rand() % 100) + 1;
    int guess;
    int attempts = 0;
    bool won = false;
    
    cout << "\n🎮 Great! " << playerName << ", I'm thinking of a number between 1 and 100..." << endl;
    delay(800);
    cout << "Can you guess it? Let's begin! 🔥\n" << endl;
    
    while (true) {
        cout << "Enter your guess (1-100): ";
        guess = getValidInput();
        attempts++;
        
        if (guess < 1 || guess > 100) {
            cout << "❌ Please enter a number between 1 and 100!\n" << endl;
            attempts--; // Don't count invalid attempts
            continue;
        }
        
        if (guess < targetNumber) {
            cout << "📈 Too low! Try again...\n" << endl;
            delay(500);
        } else if (guess > targetNumber) {
            cout << "📉 Too high! Try again...\n" << endl;
            delay(500);
        } else {
            won = true;
            break;
        }
    }
    
    // Victory animation
    cout << "\n";
    delay(300);
    printSeparator();
    cout << "🎉 CORRECT! You guessed it in " << attempts << " attempt(s)! 🎉" << endl;
    printSeparator();
    delay(500);
    cout << "\n🏆 Congratulations " << playerName << "! You won! 🏆\n" << endl;
    
    // Save to scoreboard
    insertPlayerNode(playerName, attempts, won, targetNumber);
    cout << "✅ Result saved to scoreboard.\n" << endl;
    
    pressEnterToContinue();
}

// Multiplayer Mode
void multiPlayerMode() {
    clearScreen();
    printHeader("🎮 MULTIPLAYER MODE 🎮");
    
    string player1Name, player2Name;
    cout << "\nEnter Player 1 name: ";
    getline(cin, player1Name);
    cout << "Enter Player 2 name: ";
    getline(cin, player2Name);
    
    // Generate random number between 1-100
    int targetNumber = (rand() % 100) + 1;
    int guess;
    int player1Attempts = 0;
    int player2Attempts = 0;
    string currentPlayer;
    bool player1Turn = true;
    bool gameWon = false;
    string winner;
    int winnerAttempts = 0;
    
    cout << "\n🎮 Let the battle begin! I'm thinking of a number between 1 and 100..." << endl;
    delay(800);
    cout << player1Name << " vs " << player2Name << " 🔥\n" << endl;
    
    while (!gameWon) {
        // Determine current player
        if (player1Turn) {
            currentPlayer = player1Name;
        } else {
            currentPlayer = player2Name;
        }
        
        cout << "🎯 " << currentPlayer << "'s turn!" << endl;
        cout << "Enter your guess (1-100): ";
        guess = getValidInput();
        
        // Increment attempts for current player
        if (player1Turn) {
            player1Attempts++;
        } else {
            player2Attempts++;
        }
        
        if (guess < 1 || guess > 100) {
            cout << "❌ Please enter a number between 1 and 100!\n" << endl;
            // Decrement invalid attempt
            if (player1Turn) {
                player1Attempts--;
            } else {
                player2Attempts--;
            }
            continue;
        }
        
        if (guess < targetNumber) {
            cout << "📈 Too low! Try again...\n" << endl;
            delay(500);
            player1Turn = !player1Turn; // Switch player
        } else if (guess > targetNumber) {
            cout << "📉 Too high! Try again...\n" << endl;
            delay(500);
            player1Turn = !player1Turn; // Switch player
        } else {
            gameWon = true;
            winner = currentPlayer;
            winnerAttempts = player1Turn ? player1Attempts : player2Attempts;
        }
    }
    
    // Victory animation
    cout << "\n";
    delay(300);
    printSeparator();
    cout << "🎉 CORRECT! " << winner << " guessed it! 🎉" << endl;
    printSeparator();
    delay(500);
    cout << "\n🏆 " << winner << " WINS! 🏆" << endl;
    cout << "Attempts: " << winnerAttempts << endl;
    
    // Save both players to scoreboard
    insertPlayerNode(player1Name, player1Attempts, (winner == player1Name), targetNumber);
    insertPlayerNode(player2Name, player2Attempts, (winner == player2Name), targetNumber);
    
    cout << "\n✅ Results saved to scoreboard.\n" << endl;
    
    pressEnterToContinue();
}

// Display Scoreboard
void displayScoreboard() {
    clearScreen();
    printHeader("📊 SCOREBOARD 📊");
    
    if (head == nullptr) {
        cout << "\n❌ No games played yet! Scoreboard is empty.\n" << endl;
        pressEnterToContinue();
        return;
    }
    
    cout << "\n";
    cout << "-------------------------------------------------------------" << endl;
    cout << "Player Name          Attempts     Number      Result" << endl;
    cout << "-------------------------------------------------------------" << endl;
    
    PlayerNode* current = head;
    while (current != nullptr) {
        // Format player name (pad to 20 characters)
        string name = current->playerName;
        if (name.length() > 18) {
            name = name.substr(0, 18);
        }
        
        // Print player data
        cout << name;
        for (int i = name.length(); i < 20; i++) cout << " ";
        
        cout << current->attempts;
        if (current->attempts < 10) cout << "            ";
        else cout << "           ";
        
        cout << current->numberGuessed;
        if (current->numberGuessed < 10) cout << "           ";
        else if (current->numberGuessed < 100) cout << "          ";
        else cout << "         ";
        
        if (current->won) {
            cout << "✅ Won";
        } else {
            cout << "❌ Lost";
        }
        cout << endl;
        
        current = current->next;
    }
    
    cout << "-------------------------------------------------------------" << endl;
    
    pressEnterToContinue();
}

// Insert player node into linked list
void insertPlayerNode(string name, int attempts, bool win, int number) {
    PlayerNode* newNode = new PlayerNode(name, attempts, win, number);
    
    // Insert at the beginning of the list
    if (head == nullptr) {
        head = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
}

// Free linked list memory
void freeLinkedList() {
    PlayerNode* current = head;
    PlayerNode* next;
    
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    
    head = nullptr;
}

// Main menu
void displayMenu() {
    clearScreen();
    cout << "\n";
    cout << "==========================================" << endl;
    cout << "        🎮 NUMBER GUESSING GAME 🎯      " << endl;
    cout << "==========================================" << endl;
    cout << "1. Single Player Mode" << endl;
    cout << "2. Multiplayer Mode" << endl;
    cout << "3. View Scoreboard" << endl;
    cout << "4. Exit" << endl;
    cout << "==========================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    // Seed random number generator
    srand(time(0));
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMenu();
        choice = getValidInput();
        
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
                clearScreen();
                cout << "\n";
                printSeparator();
                cout << "👋 Thanks for playing! Goodbye! 👋" << endl;
                printSeparator();
                cout << "\n";
                running = false;
                break;
            default:
                cout << "\n❌ Invalid choice! Please enter 1-4.\n" << endl;
                delay(1000);
        }
    }
    
    // Clean up memory
    freeLinkedList();
    
    return 0;
}
