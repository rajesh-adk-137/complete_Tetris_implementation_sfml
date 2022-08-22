#include <iostream>
#include "Game.h"
#include "Play.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "home_scr.h"

int main()
{
	Game* game = new Game;//Creating a game class which has all the implementation of the game
	while (game->getWindowIsOpen())
	{
		//Updates the game
		game->update();

		//Renders the game
		game->render();
	}
	delete game;
	return 0;
}