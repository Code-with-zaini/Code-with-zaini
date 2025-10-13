# 🚀 Quick Start Guide

Get started with the Number Guessing Game in less than a minute!

## ⚡ Fast Setup

### Step 1: Compile
```bash
make
```

### Step 2: Run
```bash
./game
```

That's it! 🎉

## 🎮 Quick Play Guide

1. **Main Menu**: Choose your game mode
   - `1` = Single Player (you vs computer)
   - `2` = Multiplayer (player 1 vs player 2)
   - `3` = View Scoreboard
   - `4` = Exit

2. **Enter Name**: Type your name and press Enter

3. **Choose Difficulty**:
   - `1` = Easy (1-50)
   - `2` = Medium (1-100)
   - `3` = Hard (1-200)

4. **Start Guessing**: Enter numbers to find the secret number!
   - 📈 = Too low
   - 📉 = Too high
   - 🎉 = Correct!

5. **Win**: Your score is automatically saved to the scoreboard!

## 💡 Pro Tips

- **Fewer attempts = Better score** - Try to guess efficiently!
- **Use binary search** - Start with middle numbers and narrow down
- **Check scoreboard** - Press `3` to see all previous games
- **Play again** - After each game, you can replay immediately

## 🎯 Example Session

```
Choose: 1 (Single Player)
Name: Alex
Difficulty: 2 (Medium)

Guess: 50 → Too high
Guess: 25 → Too low
Guess: 37 → Too high
Guess: 31 → Correct! ✅

Result: Alex won in 4 attempts! 🏆
```

## 🛠️ Quick Commands

```bash
make         # Compile the game
make run     # Compile and run
make clean   # Remove compiled files
./game       # Run the game
```

## ❓ Need Help?

- Read the full README.md for detailed information
- Check that your terminal supports colors (most modern terminals do)
- Ensure you have g++ with C++11 support

---

**Ready to play? Run `make run` and start guessing!** 🎮🎯
