#include "Game.hpp"
#include <iostream>
using namespace std;

int main()
{
    cout << "Welcome to Tic Tac Toe! Developed by anujthengineer" << endl;
    Game game;
    game.initializePlayers("Human", "Computer");
    game.play();

    return 0;
}