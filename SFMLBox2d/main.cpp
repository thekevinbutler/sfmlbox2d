#include "Game.h"
//entry point into the program
//instantiate Game class object and run
int main()
{
	Game game;
	//minimum frame count ensures correct physics steps if fps too low
	return game.run(30);
}