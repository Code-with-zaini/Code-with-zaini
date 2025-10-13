# Makefile for Number Guessing Game

CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = game
SOURCE = number_guessing_game.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
