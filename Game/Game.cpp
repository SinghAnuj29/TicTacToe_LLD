#include "Game.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

Game::Game(int boardSize) : board(boardSize), gameOver(false)
{
    player1 = nullptr;
    player2 = nullptr;
    currentPlayer = nullptr;
    srand(static_cast<unsigned int>(time(nullptr)));
}

Game::~Game()
{
    delete player1;
    delete player2;
}

void Game::initializePlayers(const string &p1Name, const string &p2Name)
{
    player1 = new Player(p1Name, 'X');
    player2 = new Player(p2Name, 'O', false); // This will be the computer move
    currentPlayer = player1;
}

void Game::play()
{
    while (!gameOver)
    {
        board.display();

        if (currentPlayer->isHumanPlayer())
        {
            int row, col;
            cout << currentPlayer->getName() << "'s turn (symbol: "
                 << currentPlayer->getSymbol() << ")\n";
            cout << "Enter row (0-" << board.getSize() - 1 << "): ";
            cin >> row;
            cout << "Enter column (0-" << board.getSize() - 1 << "): ";
            cin >> col;

            makeMove(row, col);
        }
        else
        {
            cout << "Computer's turn...\n";
            computerMove();
        }
    }

    displayResult();
}

void Game::makeMove(int row, int col)
{
    if (!board.isValidPosition(row, col))
    {
        cout << "Invalid position!\n";
        return;
    }

    if (!board.isEmpty(row, col))
    {
        cout << "Position already taken!\n";
        return;
    }

    board.makeMove(row, col, currentPlayer->getSymbol());

    if (board.checkWin(currentPlayer->getSymbol()))
    {
        gameOver = true;
        return;
    }

    if (board.isFull())
    {
        gameOver = true;
        currentPlayer = nullptr;
        return;
    }

    switchPlayer();
}

void Game::switchPlayer()
{
    currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

void Game::displayResult() const
{
    board.display();
    if (currentPlayer)
    {
        cout << currentPlayer->getName() << " wins!\n";
    }
    else
    {
        cout << "It's a draw!\n";
    }
}

bool Game::isGameOver() const
{
    return gameOver;
}

Player *Game::getCurrentPlayer() const
{
    return currentPlayer;
}

void Game::computerMove()
{
    pair<int, int> move = findBestMove();
    makeMove(move.first, move.second);
}

pair<int, int> Game::findBestMove() const
{
    int bestScore = numeric_limits<int>::min();
    pair<int, int> bestMove = {0, 0};

    for (int i = 0; i < board.getSize(); ++i)
    {
        for (int j = 0; j < board.getSize(); ++j)
        {
            if (board.isEmpty(i, j))
            {
                Board temp = board;
                temp.makeMove(i, j, player2->getSymbol());
                int score = minimax(temp, false, 0);

                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }

    return bestMove;
}

int Game::minimax(Board temp, bool isMax, int depth) const
{
    if (temp.checkWin(player2->getSymbol()))
        return 10 - depth;
    if (temp.checkWin(player1->getSymbol()))
        return depth - 10;
    if (temp.isFull())
        return 0;

    int bestScore = isMax ? numeric_limits<int>::min() : numeric_limits<int>::max();

    for (int i = 0; i < temp.getSize(); ++i)
    {
        for (int j = 0; j < temp.getSize(); ++j)
        {
            if (temp.isEmpty(i, j))
            {
                temp.makeMove(i, j, isMax ? player2->getSymbol() : player1->getSymbol());
                int score = minimax(temp, !isMax, depth + 1);
                bestScore = isMax ? max(bestScore, score) : min(bestScore, score);
                temp.makeMove(i, j, '-'); // Optional undo
            }
        }
    }

    return bestScore;
}
