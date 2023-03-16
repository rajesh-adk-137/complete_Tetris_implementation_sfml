#include "home_scr.h"
bool home_scr::get_into_game(sf::RenderTarget* target)
{
	return false;
}

home_scr::home_scr()
{
	this->initilization();
}
void home_scr::initilization()
{
	this->shape.setSize(sf::Vector2f(720, 800)); //for falling blocks themselves in the game
	this->background.loadFromFile("texture/22117.jpg");
	this->shape.setTexture(&background);

	if (!font3.loadFromFile("texture/8bitlimr.ttf"))
		throw("Could not load font!");

	up_down = 0; //tracks the position of the user's selection in the menu
	mode = 0; //0 is the homescreen menu 1 is the gameover menu
	txt[0].setFont(font3);
	txt[0].setCharacterSize(24);
	txt[0].setStyle(Text::Bold);
	txt[0].setString("PLAY");
	txt[0].setPosition(720 * 0.45, 800 * 0.4);
	txt[0].setFillColor(Color::Red);

	txt[1].setFont(font3);
	txt[1].setCharacterSize(24);
	txt[1].setStyle(Text::Bold);
	txt[1].setString("HIGH SCORES");
	txt[1].setPosition(720 * 0.45, 800 * 0.45);
	txt[1].setFillColor(Color::Blue);

	txt[2].setFont(font3);
	txt[2].setCharacterSize(24);
	txt[2].setStyle(Text::Bold);
	txt[2].setString("INSTRUCTIONS");
	txt[2].setPosition(720 * 0.45, 800 * 0.5);
	txt[2].setFillColor(Color::Blue);

	txt[3].setFont(font3);
	txt[3].setCharacterSize(24);
	txt[3].setStyle(Text::Bold);
	txt[3].setString("SOUND ON");
	txt[3].setPosition(720 * 0.45, 800 * 0.55);
	txt[3].setFillColor(Color::Blue);

	for (int i = 0; i < 10; i++)
	{
		volume[i].setFont(font3);
		volume[i].setCharacterSize(24);
		volume[i].setStyle(Text::Bold);
		volume[i].setString("I");
		volume[i].setFillColor(Color::Blue);
		volume[i].setPosition(720 * (0.65 + i * 0.01), 800 * 0.55);
	}
	for (int i = 0; i < volume_control; i++)
	{
		volume[i].setFillColor(Color::Red);
	}
	for (int i = volume_control; i < 10; i++)
	{
		volume[i].setFillColor(Color::Blue);
	}

	txt[4].setFont(font3);
	txt[4].setCharacterSize(24);
	txt[4].setStyle(Text::Bold);
	txt[4].setString("EXIT");
	txt[4].setPosition(720 * 0.45, 800 * 0.6);
	txt[4].setFillColor(Color::Blue);
}
void home_scr::draw_background(sf::RenderTarget* target)
{
	target->draw(this->shape);
}


void home_scr::draw_background_options(sf::RenderTarget* target)
{
	
	target->draw(this->txt[1]);
	target->draw(this->txt[2]);
	target->draw(this->txt[3]);
	target->draw(this->txt[4]);
	target->draw(this->txt[0]);
	for (int i = 0; i < 10; i++)
	{
		target->draw(this->volume[i]);
	}
}

//Returns the volume
int home_scr::volume_level(sf::RenderTarget* target)
{
	return volume_control;
}

//Checks the users inputs and acts accordingly
void home_scr::Checkevent(sf::Event evt)
{
	if (evt.type == sf::Event::KeyPressed)
	{
		 if (mode == 0 && evt.key.code == sf::Keyboard::Down)
		 {
			 txt[up_down].setFillColor(Color::Blue);
			 up_down = (up_down + 1) % 5;
			 txt[up_down].setFillColor(Color::Red);
		}
		else if (mode == 0 && evt.key.code == sf::Keyboard::Up)
		{
			 txt[up_down].setFillColor(Color::Blue);
			 if (up_down == 0)
				 up_down = 4;
			 else
				 up_down = up_down - 1;
			 txt[up_down].setFillColor(Color::Red);
			 
		}
		 //For entering the state of user's choice
		if (mode == 0 && up_down == 0 && evt.key.code == Keyboard::Return)
		{
			playText_check = true;
		}
		else if (mode == 0 && up_down == 1 && evt.key.code == Keyboard::Return)
		{
			HighScores_check = true;
		}
		else if (mode == 0 && up_down == 2 && evt.key.code == Keyboard::Return)
		{
			Instructions_check = true;
		}
		else if (mode == 0 && up_down == 3 && evt.key.code == Keyboard::Return)
		{
			sound_check = true;
		}
		else if (mode == 0 && up_down == 4 && evt.key.code == Keyboard::Return)
		{
			exit_check = true;
		}

		//To increase the sound
		else if (mode == 0 && up_down==3 && evt.key.code == sf::Keyboard::Right)
		{
			if (this->volume_control < 10)
			{
				this->volume_control += 1;
				volume[volume_control - 1].setFillColor(Color::Red);
			}
			
		}

		//To decrease the sound
		else if (mode == 0 && up_down == 3  && evt.key.code == sf::Keyboard::Left)
		{
			if (this->volume_control > 0)
			{
				volume[this->volume_control - 1].setFillColor(Color::Blue);
				this->volume_control -= 1;
			}
		}
		
	}
}
