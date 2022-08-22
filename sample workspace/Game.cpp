#include "Game.h"
//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
#include <cstring>


//Protected functions
void Game::initvariable()
{
	//Window pointer initialization
	this->window = nullptr;
}

void Game::initwindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(720, 800), "Tetris", sf::Style::Close);
	this->window->setFramerateLimit(60);
}

//Constructors / Destructors
Game::Game()
{
	this->initvariable();
	this->initwindow();
}
Game::~Game()
{
	delete this->window;
}

//Accessors

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}


//Functions
void Game::render()
{
	this->window->clear();

	//Checking the game state and drawing accordingly
	if (strcmp(state, "play") == 0 or strcmp(state, "paused") == 0 or strcmp(state, "gameover") == 0)
		this->play.Render(this->window);
	if (strcmp(state, "home") == 0)
	{
		home.draw_background(this->window);
		if (home.mode == 0)
		{
			home.draw_background_options(this->window);
		}
	 else if (home.mode == 1)
		{ 
			data.display_instructions(this->window);
		}
	 else if (home.mode == 2)
		{
			data.display_highscores(this->window);
		}
	}



	if (strcmp(state, "play") == 0 or strcmp(state, "paused") == 0)
	{
		this->play.draw_shadow(this->window);
		this->play.draw_block(this->window);
		this->play.draw_Pblock(this->window);
		this->play.draw_world(this->window);
		this->play.clear_anm(this->window);
	}
	if (strcmp(state, "paused") == 0)
	{
		menu.paused_menu_items(this->window);
	}
	if (play.game_over_check)
	{
		this->play.draw_dead_block(this->window);
		if (!(strcmp(state, "home") == 0))
		{
			strcpy_s(state, 9, "gameover");
			if (set)
			{
				if (data.check(play.score()) == true)
					c = true;
				set = false;
			}
			if(c)
				this->play.draw_high(this->window);
		}
		
		this->menu.game_over_selection(this->window);
	}
	this->window->display();
}

//Updates the game in each frame
void Game::update()
{
	if (menu.sound_check == true)//by default true
	{

		if (music_off_check == true)//by default false
		{
			this->play.sfx_mainsound.play();
			music_off_check = false;
		}
		this->play.sfx_mainsound.setVolume(this->play.volume_value * 10);
	}

	this->UpdateEvents();
	
	if (strcmp(state, "play") == 0)
		this->play.update();
	
	if (strcmp(state, "paused") == 0)//paused mode ignores input for gameover mode and read actually paused mode inputs 
	{
		if (menu.sound_check == false)
		{
			this->play.sfx_mainsound.pause();
			music_off_check = true;
		}
		
		if (menu.resume_check)
		{
			strcpy_s(state, 5, "play");
			menu.resume_check = false;

		}
		if (menu.new_game_check)
		{
			this->play.clear_game(this->window);
            strcpy_s(state, 5, "play");
			menu.new_game_check = false;
			if (music_off_check == false)
				this->play.sfx_mainsound.play();

		}

		if (menu.exit_check)
		{

			menu.exit_check = false;
			this->play.clear_game(this->window);
			strcpy_s(state, 5, "home");
			if (music_off_check == false)
				this->play.sfx_mainsound.play();

		}

		
	}
	else if (strcmp(state, "gameover") == 0) //gameover mode ignores input for input mode and read actually gameover mode inputs 
	{
		
		if (menu.nnewgame)
		{
			
			menu.nnewgame = false;
			strcpy_s(state, 5, "play");
			this->play.clear_game(this->window);
			if (music_off_check == false)
				this->play.sfx_mainsound.play();
			set = true;
			c = false;
		}
		else if (menu.exitgame)
		{
			menu.exitgame = false;
			strcpy_s(state, 5, "home");
			this->play.clear_game(this->window);
			if (music_off_check == false)
				this->play.sfx_mainsound.play();
			set = true;
			c = false;
		}
		
	}
	else if (strcmp(state, "home") == 0)
	{
		if (home.playText_check)
		{
			home.playText_check = false;
			strcpy_s(state, 5, "play");
			this->play.clear_game(this->window);
			if (music_off_check == false)
			this->play.sfx_mainsound.play();
		}
		if (home.HighScores_check)
		{
			home.mode = 2;
			home.HighScores_check = false;
		}
		if (home.Instructions_check)
		{
			home.mode = 1;
			home.Instructions_check = false;
		}
		if (home.exit_check)
		{
			home.exit_check = false;
			this->window->close();
		}
		if (home.sound_check)
		{
			//home.sound_check = false;
		}
	}
	this->play.volume_value = this->home.volume_control;
	
}


void Game::UpdateEvents()
{
	while (this->window->pollEvent(this->e))
	{
		switch (this->e.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (home.mode==0 && e.key.code == sf::Keyboard::Escape)
			    {
					this->window->close();
				}
			else if (home.mode == 1 or home.mode==2 && e.key.code == sf::Keyboard::Escape)
			{
				this->home.mode = 0;
			}
			else if (e.key.code == sf::Keyboard::P)
			{
				if (strcmp(state, "play") == 0)
				{
					if (!play.game_over_check)
					{

						strcpy_s(state, 7, "paused");
					}
				}
				else if (strcmp(state, "paused") == 0)
					if (!play.game_over_check)
					{
						{

							strcpy_s(state, 5, "play");
						}
					}
			}
			
			break;


		}
		if (strcmp(state, "paused") == 0 or strcmp(state, "gameover") == 0)
		{
			if (strcmp(state, "paused") == 0)
				menu.mode = 0;//mode=0 for paused mode
			else if (strcmp(state, "gameover") == 0)
				menu.mode = 1;//mode=1 for gameover mode
			menu.Checkevent(e);
		}
		if (strcmp(state, "play") == 0)
			play.Checkevent(e);
		if (strcmp(state, "home") == 0)
			home.Checkevent(e);
	}
}
