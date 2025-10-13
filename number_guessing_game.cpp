#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <iomanip>

using namespace std;

// ANSI color codes for better visuals
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// Node structure for Linked List
struct Node {
    string playerName;
    int attempts;
    bool won;
    int numberGuessed;
    Node* next;
    
    Node(string name, int att, bool w, int num) {
        playerName = name;
        attempts = att;
        won = w;
        numberGuessed = num;
        next = nullptr;
    }
};

// Global head pointer for the scoreboard linked list
Node* head = nullptr;

// Function declarations
void printHeader(string title);
void printLine(char c, int length);
void delay(int milliseconds);
void displayMenu();
void singlePlayerMode();
void multiPlayerMode();
void displayScoreboard();
void insertPlayerNode(string name, int attempts, bool win, int number);
void clearScreen();
int getDifficulty();

// Main function
int main() {
    srand(time(0)); // Seed random number generator
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMenu();
        cout << CYAN << "Enter your choice: " << RESET;
        cin >> choice;
        
        switch (choice) {
            case 1:
                clearScreen();
                singlePlayerMode();
                break;
            case 2:
                clearScreen();
                multiPlayerMode();
                break;
            case 3:
                clearScreen();
                displayScoreboard();
                break;
            case 4:
                printHeader("THANK YOU FOR PLAYING!");
                cout << YELLOW << "\n🎮 See you next time! 🎯\n" << RESET;
                delay(1000);
                running = false;
                break;
            default:
                cout << RED << "\n❌ Invalid choice! Please try again.\n" << RESET;
                delay(1000);
        }
    }
    
    // Clean up linked list memory
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    
    return 0;
}

// Clear screen function (cross-platform)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Delay function for animations
void delay(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

// Print a line of characters
void printLine(char c, int length) {
    for (int i = 0; i < length; i++) {
        cout << c;
    }
    cout << endl;
}

// Print stylish header
void printHeader(string title) {
    cout << "\n" << CYAN << BOLD;
    printLine('=', 50);
    cout << "        🎮 " << title << " 🎯" << endl;
    printLine('=', 50);
    cout << RESET;
}

// Display main menu
void displayMenu() {
    clearScreen();
    cout << CYAN << BOLD;
    printLine('=', 50);
    cout << "        🎮 NUMBER GUESSING GAME 🎯" << endl;
    printLine('=', 50);
    cout << RESET;
    
    cout << YELLOW << "\n1. " << RESET << "🎯 Single Player Mode" << endl;
    cout << YELLOW << "2. " << RESET << "👥 Multiplayer Mode" << endl;
    cout << YELLOW << "3. " << RESET << "🏆 View Scoreboard" << endl;
    cout << YELLOW << "4. " << RESET << "🚪 Exit" << endl;
    printLine('-', 50);
    cout << endl;
}

// Get difficulty level
int getDifficulty() {
    int diff;
    cout << MAGENTA << "\nSelect Difficulty:" << RESET << endl;
    cout << "1. 🟢 Easy (1-50)" << endl;
    cout << "2. 🟡 Medium (1-100)" << endl;
    cout << "3. 🔴 Hard (1-200)" << endl;
    cout << CYAN << "Enter choice (1-3): " << RESET;
    cin >> diff;
    
    switch (diff) {
        case 1: return 50;
        case 2: return 100;
        case 3: return 200;
        default: return 100;
    }
}

// Single Player Mode
void singlePlayerMode() {
    printHeader("SINGLE PLAYER MODE");
    
    string playerName;
    cout << GREEN << "\nEnter your name: " << RESET;
    cin.ignore();
    getline(cin, playerName);
    
    int maxRange = getDifficulty();
    int secretNumber = (rand() % maxRange) + 1;
    int guess;
    int attempts = 0;
    
    cout << YELLOW << "\n🎯 I'm thinking of a number between 1 and " << maxRange << "..." << RESET << endl;
    delay(500);
    cout << CYAN << "Can you guess it? Let's begin! 🚀\n" << RESET << endl;
    delay(500);
    
    while (true) {
        cout << BLUE << "Guess the number (1-" << maxRange << "): " << RESET;
        cin >> guess;
        attempts++;
        
        if (guess < secretNumber) {
            cout << YELLOW << "📈 Too low! Try again...\n" << RESET << endl;
            delay(300);
        } else if (guess > secretNumber) {
            cout << YELLOW << "📉 Too high! Try again...\n" << RESET << endl;
            delay(300);
        } else {
            cout << GREEN << BOLD << "\n🎉 Correct! You guessed it in " << attempts << " attempts!\n" << RESET << endl;
            delay(500);
            
            // Victory animation
            cout << CYAN;
            printLine('*', 50);
            cout << BOLD << "🏆 Congratulations " << playerName << "! You won! 🏆" << endl;
            printLine('*', 50);
            cout << RESET << endl;
            
            // Save to scoreboard
            insertPlayerNode(playerName, attempts, true, secretNumber);
            cout << GREEN << "✅ Result saved in scoreboard.\n" << RESET << endl;
            break;
        }
    }
    
    // Ask for replay
    char replay;
    cout << MAGENTA << "\nPlay again? (y/n): " << RESET;
    cin >> replay;
    if (replay == 'y' || replay == 'Y') {
        singlePlayerMode();
    }
}

// Multiplayer Mode
void multiPlayerMode() {
    printHeader("MULTIPLAYER MODE");
    
    string player1Name, player2Name;
    cout << GREEN << "\nEnter Player 1 name: " << RESET;
    cin.ignore();
    getline(cin, player1Name);
    cout << GREEN << "Enter Player 2 name: " << RESET;
    getline(cin, player2Name);
    
    int maxRange = getDifficulty();
    int secretNumber = (rand() % maxRange) + 1;
    int guess;
    int player1Attempts = 0;
    int player2Attempts = 0;
    bool player1Turn = true;
    
    cout << YELLOW << "\n🎯 I'm thinking of a number between 1 and " << maxRange << "..." << RESET << endl;
    delay(500);
    cout << CYAN << "Players will take turns guessing! Let's begin! 🚀\n" << RESET << endl;
    delay(500);
    
    while (true) {
        string currentPlayer = player1Turn ? player1Name : player2Name;
        cout << "\n" << MAGENTA << BOLD << "👤 " << currentPlayer << "'s turn!" << RESET << endl;
        cout << BLUE << "Guess the number (1-" << maxRange << "): " << RESET;
        cin >> guess;
        
        if (player1Turn) {
            player1Attempts++;
        } else {
            player2Attempts++;
        }
        
        if (guess < secretNumber) {
            cout << YELLOW << "📈 Too low! Try again...\n" << RESET << endl;
            delay(300);
        } else if (guess > secretNumber) {
            cout << YELLOW << "📉 Too high! Try again...\n" << RESET << endl;
            delay(300);
        } else {
            int winnerAttempts = player1Turn ? player1Attempts : player2Attempts;
            cout << GREEN << BOLD << "\n🎉 Correct! " << currentPlayer << " guessed it!\n" << RESET << endl;
            delay(500);
            
            // Victory animation
            cout << CYAN;
            printLine('*', 50);
            cout << BOLD << "🏆 " << currentPlayer << " WINS! 🏆" << endl;
            cout << "Attempts: " << winnerAttempts << endl;
            printLine('*', 50);
            cout << RESET << endl;
            
            // Save both players to scoreboard
            insertPlayerNode(player1Name, player1Attempts, player1Turn, secretNumber);
            insertPlayerNode(player2Name, player2Attempts, !player1Turn, secretNumber);
            cout << GREEN << "✅ Results saved in scoreboard.\n" << RESET << endl;
            break;
        }
        
        // Switch turns
        player1Turn = !player1Turn;
    }
    
    // Display final stats
    cout << "\n" << YELLOW;
    printLine('-', 50);
    cout << "📊 Final Stats:" << endl;
    cout << player1Name << ": " << player1Attempts << " attempts" << endl;
    cout << player2Name << ": " << player2Attempts << " attempts" << endl;
    printLine('-', 50);
    cout << RESET << endl;
    
    // Ask for replay
    char replay;
    cout << MAGENTA << "\nPlay again? (y/n): " << RESET;
    cin >> replay;
    if (replay == 'y' || replay == 'Y') {
        multiPlayerMode();
    }
}

// Insert player node into linked list
void insertPlayerNode(string name, int attempts, bool win, int number) {
    Node* newNode = new Node(name, attempts, win, number);
    
    // Insert at the beginning of the list
    if (head == nullptr) {
        head = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
}

// Display scoreboard
void displayScoreboard() {
    printHeader("SCOREBOARD");
    
    if (head == nullptr) {
        cout << YELLOW << "\n📋 No games played yet! Scoreboard is empty.\n" << RESET << endl;
        delay(2000);
        return;
    }
    
    cout << "\n" << CYAN << BOLD;
    printLine('-', 70);
    cout << left << setw(20) << "Player Name" 
         << setw(15) << "Attempts" 
         << setw(15) << "Number" 
         << setw(20) << "Result" << endl;
    printLine('-', 70);
    cout << RESET;
    
    Node* current = head;
    int rank = 1;
    
    while (current != nullptr) {
        cout << left << setw(20) << current->playerName
             << setw(15) << current->attempts
             << setw(15) << current->numberGuessed;
        
        if (current->won) {
            cout << GREEN << "✅ Won" << RESET << endl;
        } else {
            cout << RED << "❌ Lost" << RESET << endl;
        }
        
        current = current->next;
        rank++;
    }
    
    cout << CYAN;
    printLine('-', 70);
    cout << RESET << endl;
    
    // Show top performer
    Node* temp = head;
    Node* topPlayer = nullptr;
    int minAttempts = 999999;
    
    while (temp != nullptr) {
        if (temp->won && temp->attempts < minAttempts) {
            minAttempts = temp->attempts;
            topPlayer = temp;
        }
        temp = temp->next;
    }
    
    if (topPlayer != nullptr) {
        cout << YELLOW << BOLD << "🏆 Best Player: " << topPlayer->playerName 
             << " (Only " << topPlayer->attempts << " attempts!)\n" << RESET << endl;
    }
    
    cout << MAGENTA << "\nPress Enter to continue..." << RESET;
    cin.ignore();
    cin.get();
}

