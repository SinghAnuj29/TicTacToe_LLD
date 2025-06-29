#include "Player.hpp"

using namespace std;

Player::Player(const string &name, char symbol, bool isHuman)
    : name(name), symbol(symbol), isHuman(isHuman) {}

string Player::getName() const
{
    return name;
}

char Player::getSymbol() const
{
    return symbol;
}

bool Player::isHumanPlayer() const
{
    return isHuman;
}
