#pragma once

#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;

//this class is used for during_gameplay option like pause or play again type
class Menu
{
private:
	Font font2;
	Text  resume, sound, newgame, exit, AskContinue, YesOption, NoOption ;
	int pause_selection;//for choosing option when paused
	int play_end;//for game over selection
	
	
	
public:
	int mode;//for paused more or gameover mode check only
	bool resume_check = false, new_game_check = false, exit_check = false, sound_check=true;
	string on_off = "ON";
	bool nnewgame = false;
	bool exitgame = false;
	Menu();
	void maininit();
	void Checkevent(sf::Event evtt);
	void paused_menu_items(sf::RenderTarget* target);
	void game_over_selection(sf::RenderTarget* target);

};

