#include "Menu.h"

void Menu::maininit()
{
	//Initializing the menu objects and variables

	if (!font2.loadFromFile("texture/8bitlimr.ttf"))
		throw("Could not load font!");
	pause_selection = 0;
	play_end= 0;
	resume.setFont(font2);
	resume.setCharacterSize(24);
	resume.setStyle(Text::Bold);
	resume.setFillColor(Color::Red);
	resume.setString("Resume");
	resume.setPosition(720 * 0.2, 800 * 0.43);

	newgame.setFont(font2);
	newgame.setCharacterSize(24);
	newgame.setStyle(Text::Bold);
	newgame.setString("New Game");
	newgame.setPosition(720 * 0.2, 800 * 0.5);

	exit.setFont(font2);
	exit.setCharacterSize(24);
	exit.setStyle(Text::Bold);
	exit.setString("Exit");
	exit.setPosition(720 * 0.2, 800 * 0.64);

	sound.setFont(font2);
	sound.setCharacterSize(24);
	sound.setStyle(Text::Bold);
	sound.setPosition(720 * 0.2, 800 * 0.57);

	AskContinue.setFont(font2);
	AskContinue.setCharacterSize(24);
	AskContinue.setStyle(Text::Bold);
	AskContinue.setPosition(720 * 0.585,800 * 0.45);
	AskContinue.setString("Do u want a new game?");

	YesOption.setFont(font2);
	YesOption.setCharacterSize(24);
	YesOption.setStyle(Text::Bold);
	YesOption.setPosition(720* 0.65, 800 * 0.5);
	YesOption.setString("Yes");
	YesOption.setFillColor(Color::Red);

	NoOption.setFont(font2);
	NoOption.setCharacterSize(24);
	NoOption.setStyle(Text::Bold);
	NoOption.setPosition(720* 0.87,800 * 0.5);
	NoOption.setString("No");
}




Menu::Menu()
{
	this->maininit();
}

void Menu::Checkevent(sf::Event evt)
{
	if (evt.type == sf::Event::KeyPressed)
	{
		if (mode == 0)
		{
			//For paused mode
			//Allows the user to select options with the down or up key
			if (evt.key.code == sf::Keyboard::Down)
			{

				if (this->pause_selection == 0)
				{
					this->newgame.setFillColor(Color::Red);
					this->resume.setFillColor(Color::White);
					this->pause_selection = pause_selection + 1;

				}

				else if (this->pause_selection == 1)
				{
					this->sound.setFillColor(Color::Red);
					this->newgame.setFillColor(Color::White);
					this->pause_selection = pause_selection + 1;

				}
				else if (this->pause_selection == 2)
				{
					this->exit.setFillColor(Color::Red);
					this->sound.setFillColor(Color::White);
					this->pause_selection = pause_selection + 1;

				}
				else if (this->pause_selection == 3)
				{
					this->resume.setFillColor(Color::Red);
					this->exit.setFillColor(Color::White);
					this->pause_selection = 0;
				}
			}
			if (evt.key.code == sf::Keyboard::Up)
			{
				if (this->pause_selection == 1)
				{
					this->resume.setFillColor(Color::Red);
					this->newgame.setFillColor(Color::White);
					this->pause_selection = pause_selection - 1;
				}
				else if (this->pause_selection == 2)
				{
					this->sound.setFillColor(Color::White);
					this->newgame.setFillColor(Color::Red);
					this->pause_selection = pause_selection - 1;
				}

				else if (this->pause_selection == 3)
				{
					this->sound.setFillColor(Color::Red);
					this->exit.setFillColor(Color::White);
					this->pause_selection = pause_selection - 1;

				}
				else if (this->pause_selection == 0)
				{
					this->resume.setFillColor(Color::White);
					this->exit.setFillColor(Color::Red);
					this->pause_selection = 3;
				}

			}
			//To enter into a certain selection
			if (pause_selection == 0 && evt.key.code == Keyboard::Return)
			{
				this->resume_check = true;
			}
			else if (pause_selection == 1 && evt.key.code == Keyboard::Return)
			{
				this->new_game_check = true;

			}
			if (pause_selection == 2 && evt.key.code == Keyboard::Return)
			{
				if (sound_check == true)
				{
					this->on_off = "OFF";
					this->sound_check = false;
				}
				else if (sound_check == false)
				{

					this->on_off = "ON";
					this->sound_check = true;
				}


			}
			else if (pause_selection == 3 && evt.key.code == Keyboard::Return)
			{
				this->exit_check = true;
			}
		}
		
		else if (mode == 1)
		{
			//For gameover mode
			if (evt.key.code == sf::Keyboard::Right)
			{
				if (play_end == 0)//play_end means if you want to play again or exit
				{
					YesOption.setFillColor(Color::White);
					NoOption.setFillColor(Color::Red);
					play_end = 1;
				}
				else if (play_end == 1)
				{
					YesOption.setFillColor(Color::Red);
					NoOption.setFillColor(Color::White);
					play_end = 0;
				}
			}
			if (evt.key.code == sf::Keyboard::Left)
			{
				if (play_end == 0)
				{
					YesOption.setFillColor(Color::White);
					NoOption.setFillColor(Color::Red);
					play_end = 1;
				}
				else if (play_end == 1)
				{
					YesOption.setFillColor(Color::Red);
					NoOption.setFillColor(Color::White);
					play_end = 0;
				}
			}
			if (play_end == 0 && evt.key.code == Keyboard::Return)
			{
				nnewgame = true;
			}
			else if (play_end == 1 && evt.key.code == Keyboard::Return)
			{
				exitgame = true;
			}
		}
	}

}

//Draws the paused menu
void Menu::paused_menu_items(sf::RenderTarget* target)
{
	target->draw(this->resume);
	target->draw(this->newgame);
	this->sound.setString("Music " + on_off);
	target->draw(this->sound);
	target->draw(this->exit);
}

//Draws the gameover menu
void Menu::game_over_selection(sf::RenderTarget* target)
{
	target->draw(this->NoOption);
	target->draw(this->YesOption);
	target->draw(this->AskContinue);
}