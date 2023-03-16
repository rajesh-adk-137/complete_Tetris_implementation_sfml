#pragma once
#include "Play.h"
#include "Menu.h"
#include "home_scr.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "store_data.h"
using namespace std;
using namespace sf;

//Game engine class
class Game
{
protected:
	//window
	sf::RenderWindow* window;
	sf::Event e;

	home_scr home;
	Play play;//play data type variable
	Menu menu;
	store_data data;

	char state[20] = "home";

	//Initializer functions
	void initvariable();
	void initwindow();
	//bool game_is_paused;
	bool music_off_check = false;

	bool set = true;

	bool c = false;
public:

	//Constructor/Destructor
	Game();
	~Game();

	//Accessors
	const bool getWindowIsOpen() const;

	//Functions
	void UpdateEvents();
	void render();
	void update();
	
};

