# Tic Tac Toe - C++ Console Game 🎮

A simple and interactive 3x3 Tic Tac Toe game built using Object-Oriented Programming in C++. Play as a human against a computer opponent powered by the Minimax algorithm.

## Features
- 3x3 Board Display in Console
- Two Players: Human (X) vs Computer (O)
- Turn-based Gameplay
- Minimax AI to ensure the computer plays optimally
- Result Detection: Win or Draw

## Classes
- `Player`: Represents each player (name, symbol, type)
- `Board`: Manages the 3x3 grid, moves, and win conditions
- `Game`: Handles game loop, player turns, and AI logic
- `TicTacToe.cpp`: Entry point to start and play the game

## Getting Started

### Compile and Run
```bash
g++ TicTacToe.cpp Game.cpp Board.cpp Player.cpp -o TicTacToe
./TicTacToe
