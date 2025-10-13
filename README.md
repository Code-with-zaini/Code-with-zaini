# 🎮 Number Guessing Game - C++ Console Project

A feature-rich number guessing game built in C++ using **Linked Lists** to manage player data and scoreboard. The game includes both single-player and multiplayer modes with a beautiful console interface!

## ✨ Features

### 🎯 Game Modes
- **Single Player Mode**: Play against the computer
- **Multiplayer Mode**: Compete with a friend (turn-based)

### 🔗 Linked List Implementation
- Custom Node structure storing:
  - Player name
  - Number of attempts
  - Correct number guessed
  - Win/Loss status
  - Next player pointer
- Dynamic scoreboard using linked list traversal

### 🎨 Visual Enhancements
- Colorful console output using ANSI escape codes
- ASCII art borders and decorations
- Emoji icons (🎯, 🏆, 🎉, etc.)
- Animated delays for better user experience
- Stylish menu system

### 🎮 Gameplay Features
- Three difficulty levels:
  - 🟢 Easy (1-50)
  - 🟡 Medium (1-100)
  - 🔴 Hard (1-200)
- Real-time feedback (Too High/Too Low)
- Attempt counter
- Turn-based multiplayer
- Replay option
- Persistent scoreboard

### 🏆 Scoreboard
- View all game results
- Display player names, attempts, and results
- Highlight best performer
- Clean tabular format

## 📋 Requirements

- C++ compiler with C++11 support (g++, clang++, etc.)
- Linux/Unix/macOS terminal (for ANSI colors)
- Windows with compatible terminal (Windows Terminal recommended)

## 🚀 Installation & Compilation

### Method 1: Using Makefile (Recommended)

```bash
# Compile the game
make

# Compile and run
make run

# Clean build files
make clean
```

### Method 2: Manual Compilation

```bash
# Compile
g++ -std=c++11 -o game number_guessing_game.cpp

# Run
./game
```

### Windows

```bash
# Compile
g++ -std=c++11 -o game.exe number_guessing_game.cpp

# Run
game.exe
```

## 🎮 How to Play

1. **Start the Game**: Run the compiled executable
2. **Choose a Mode**:
   - Press `1` for Single Player
   - Press `2` for Multiplayer
   - Press `3` to view Scoreboard
   - Press `4` to Exit
3. **Enter Player Name(s)**: Type your name when prompted
4. **Select Difficulty**: Choose Easy, Medium, or Hard
5. **Start Guessing**: Enter numbers to guess the secret number
6. **Get Feedback**: The game will tell you if your guess is too high or too low
7. **Win**: Guess the correct number and see your score saved!
8. **View Scoreboard**: Check out all the game results

## 📁 Project Structure

```
.
├── number_guessing_game.cpp  # Main game source code
├── Makefile                  # Build automation
└── README.md                 # This file
```

## 🧩 Code Structure

### Key Components

```cpp
// Node Structure
struct Node {
    string playerName;
    int attempts;
    bool won;
    int numberGuessed;
    Node* next;
};

// Main Functions
void singlePlayerMode();       // Single player game logic
void multiPlayerMode();        // Multiplayer game logic
void displayScoreboard();      // Display all game results
void insertPlayerNode(...);    // Add player to linked list
void printHeader(string);      // Print stylish headers
int getDifficulty();          // Get difficulty selection
```

## 🎯 Game Flow

```
Start
  ↓
Display Menu
  ↓
User Choice
  ├─→ Single Player → Enter Name → Select Difficulty → Play → Save Result
  ├─→ Multiplayer   → Enter Names → Select Difficulty → Play → Save Results
  ├─→ Scoreboard    → Display Linked List
  └─→ Exit          → Clean Up Memory → End
```

## 🌈 Features Showcase

### Example Gameplay

```
==================================================
        🎮 NUMBER GUESSING GAME 🎯
==================================================

1. 🎯 Single Player Mode
2. 👥 Multiplayer Mode
3. 🏆 View Scoreboard
4. 🚪 Exit
--------------------------------------------------

Enter your choice: 1

[Single Player Mode]
Enter your name: Zain

Select Difficulty:
1. 🟢 Easy (1-50)
2. 🟡 Medium (1-100)
3. 🔴 Hard (1-200)
Enter choice: 2

🎯 I'm thinking of a number between 1 and 100...
Can you guess it? Let's begin! 🚀

Guess the number (1-100): 50
📉 Too high! Try again...

Guess the number (1-100): 25
📈 Too low! Try again...

Guess the number (1-100): 33
🎉 Correct! You guessed it in 3 attempts!

**************************************************
🏆 Congratulations Zain! You won! 🏆
**************************************************

✅ Result saved in scoreboard.
```

## 🧠 Learning Objectives

This project demonstrates:
- ✅ Linked List implementation in C++
- ✅ Dynamic memory management
- ✅ Object-oriented programming concepts
- ✅ Console I/O operations
- ✅ Random number generation
- ✅ Function modularization
- ✅ User experience design in CLI
- ✅ Data structure traversal

## 🎓 Educational Value

Perfect for:
- Data Structures & Algorithms students
- C++ beginners to intermediate learners
- Understanding linked lists in practice
- Console application development
- Game development fundamentals

## 🔧 Customization

You can easily customize:
- Difficulty ranges (modify `getDifficulty()`)
- Colors (change ANSI codes)
- ASCII art (modify `printHeader()`)
- Game rules (adjust logic in mode functions)
- Scoreboard sorting (modify linked list traversal)

## 🐛 Troubleshooting

**Colors not showing?**
- Use a terminal that supports ANSI escape codes
- Windows: Use Windows Terminal or enable ANSI support

**Compilation errors?**
- Ensure you have C++11 or later
- Check that all required headers are available

**Game crashes?**
- Check for sufficient memory
- Ensure proper input (numbers only for guesses)

## 📝 License

This project is free to use for educational purposes.

## 👨‍💻 Author

Created as a demonstration of Linked Lists in C++ with practical game development.

## 🎉 Enjoy the Game!

Have fun playing and learning! Feel free to modify and enhance the game with your own features.

---

**Pro Tip**: Try to guess the number in the fewest attempts possible to top the scoreboard! 🏆
