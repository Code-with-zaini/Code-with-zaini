# 🎯 Number Guessing Game with Linked List Scoreboard

A fun C++ console-based number guessing game that uses **Linked Lists** to maintain a scoreboard of all players and their game results.

## 🎮 Features

- **Single Player Mode**: Play against the computer
- **Multiplayer Mode**: Two players compete against each other
- **Linked List Scoreboard**: All game results stored in a linked list data structure
- **Visual Enhancements**: ASCII art, emojis, and animations
- **Player Statistics**: Track attempts, guessed numbers, and win/loss records

## 🧠 Core Components

### Linked List Structure
```cpp
struct PlayerNode {
    string playerName;
    int attempts;
    bool won;
    int numberGuessed;
    PlayerNode* next;
};
```

### Game Modes

1. **Single Player Mode**
   - Player competes against the computer
   - Computer generates a random number (1-100)
   - Player tries to guess with feedback (too high/too low)
   - Result saved to scoreboard

2. **Multiplayer Mode**
   - Two players take turns guessing
   - First to guess correctly wins
   - Both players' results saved to scoreboard

3. **Scoreboard**
   - Displays all game history
   - Shows player names, attempts, target numbers, and results
   - Data stored and traversed using linked list

## 📦 Compilation Instructions

### On Linux/macOS:
```bash
g++ -std=c++11 number_guessing_game.cpp -o game
./game
```

### On Windows (MinGW):
```bash
g++ -std=c++11 number_guessing_game.cpp -o game.exe
game.exe
```

### On Windows (Visual Studio):
```bash
cl /EHsc number_guessing_game.cpp
number_guessing_game.exe
```

## 🚀 How to Play

1. Run the compiled executable
2. Choose from the main menu:
   - **1**: Single Player Mode
   - **2**: Multiplayer Mode
   - **3**: View Scoreboard
   - **4**: Exit
3. Enter player name(s) when prompted
4. Guess the number between 1-100
5. Follow the hints (too high/too low)
6. Win by guessing the correct number!
7. Check the scoreboard to see all game results

## 🎯 Example Gameplay

```
==========================================
        🎮 NUMBER GUESSING GAME 🎯      
==========================================
1. Single Player Mode
2. Multiplayer Mode
3. View Scoreboard
4. Exit
==========================================
Enter your choice: 1

==========================================
        🎯 SINGLE PLAYER MODE 🎯
==========================================

Enter your name: Zain

🎮 Great! Zain, I'm thinking of a number between 1 and 100...
Can you guess it? Let's begin! 🔥

Enter your guess (1-100): 50
📉 Too high! Try again...

Enter your guess (1-100): 25
📈 Too low! Try again...

Enter your guess (1-100): 37
📈 Too low! Try again...

Enter your guess (1-100): 43
🎉 CORRECT! You guessed it in 4 attempt(s)! 🎉

🏆 Congratulations Zain! You won! 🏆

✅ Result saved to scoreboard.
```

## 📊 Scoreboard Display

```
==========================================
           📊 SCOREBOARD 📊
==========================================

-------------------------------------------------------------
Player Name          Attempts     Number      Result
-------------------------------------------------------------
Ahsan                7            67          ❌ Lost
Zain                 5            89          ✅ Won
Sarah                3            42          ✅ Won
-------------------------------------------------------------
```

## 🛠️ Technical Details

### Data Structures Used:
- **Linked List**: Custom implementation using pointers
- **Node Structure**: Stores player data and next pointer

### Libraries Used:
- `<iostream>` - Input/output operations
- `<string>` - String handling
- `<cstdlib>` - Random number generation
- `<ctime>` - Time seeding for randomness
- `<thread>` - Sleep/delay functionality
- `<chrono>` - Time duration management
- `<limits>` - Input validation

### Key Functions:
- `singlePlayerMode()` - Handles single player gameplay
- `multiPlayerMode()` - Handles multiplayer gameplay
- `displayScoreboard()` - Traverses and displays linked list
- `insertPlayerNode()` - Adds new player to linked list
- `freeLinkedList()` - Cleans up memory before exit
- `printHeader()` - Creates ASCII art headers

## 🎨 Visual Features

- ASCII art borders and headers
- Emoji indicators (🎯, 🎮, 🏆, ✅, ❌, etc.)
- Animated delays for better UX
- Clear screen functionality for clean interface
- Formatted scoreboard table

## 💡 Bonus Features Implemented

- ✅ Input validation (handles invalid inputs gracefully)
- ✅ Cross-platform screen clearing
- ✅ Memory management (proper cleanup of linked list)
- ✅ Turn-based multiplayer system
- ✅ Comprehensive scoreboard with game history
- ✅ Visual feedback with delays and animations

## 🔧 Future Enhancements (Ideas)

- Add difficulty levels (Easy: 1-50, Medium: 1-100, Hard: 1-200)
- Implement guess history per player using another linked list
- Add replay option after each game
- Save scoreboard to file (persistence)
- Add player profiles with statistics
- Implement leaderboard (sorted by attempts)

## 📝 License

This is a learning project. Feel free to use, modify, and distribute!

## 👨‍💻 Author

Created as a demonstration of Linked List implementation in C++ through an interactive game.

---

**Enjoy the game! 🎮🎯**
