#pragma once
#include <iostream>
#include "Play.h"
#include "store_data.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<fstream>
class home_scr
{
private:
	Texture background;
	RectangleShape shape;
	Text playText, HighScores, Instructions, exit, sound,volume[10];
	Text txt[5];
	Font font3;
	int up_down = 0;
public:
	int volume_control = 2;
	bool playText_check = false, HighScores_check = false, Instructions_check = false, exit_check = false, sound_check = false;
	home_scr();
	void initilization();
	bool get_into_game(sf::RenderTarget* target);
	void draw_background(sf::RenderTarget* target);
	void draw_background_options(sf::RenderTarget* target);
	void Checkevent(sf::Event evtt);
	int volume_level(sf::RenderTarget* target);
	int mode = 0;//0 for main screen,1 for instructions,2 for highscores
	
};

