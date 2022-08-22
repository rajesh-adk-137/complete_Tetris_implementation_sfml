#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include<sstream>
#include<string>
#include<fstream>
#include "Play.h"
#include "home_scr.h"

class store_data
{
private:
	int count = 0, temp = 0;
	int arr[6]={0};
	Text inst[20];
	Text scores[6];
	string instruct;
	fstream file;
	fstream file1;
	Font font3;

	void instructions();
public:
	void score();
	store_data();
	void display_instructions(sf::RenderTarget* target);
	void display_highscores(sf::RenderTarget* target);
	bool check(int);
};


