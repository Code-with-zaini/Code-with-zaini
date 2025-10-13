#!/bin/bash

# Build script for Number Guessing Game

echo "🔨 Compiling Number Guessing Game..."
g++ -std=c++11 -Wall number_guessing_game.cpp -o game

if [ $? -eq 0 ]; then
    echo "✅ Compilation successful!"
    echo "🎮 Run the game with: ./game"
else
    echo "❌ Compilation failed!"
    exit 1
fi
