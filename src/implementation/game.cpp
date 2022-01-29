#include "../headers/game.h"

Game::Game(int FPS)
{
	this -> FPS = FPS;
}

void Game::setDelayCount(int value)
{
	this -> iDelayCount = value;
}

void Game::toggleGameOver()
{
	this -> bGameOver = !this -> bGameOver;
}

void Game::setGameOver(bool value)
{
	this -> bGameOver = value;
}
