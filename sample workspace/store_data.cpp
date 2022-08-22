#include "store_data.h"

//Loads the instructions from the file
void store_data::instructions()
{
	if (!font3.loadFromFile("texture/8bitlimr.ttf"))
		throw("Could not load font!");
	int i = 0;
	count = 0;
	file.open("Instructions.txt");
	if (!file)
	{
		std::exit(1);
	}
	while (getline(file, instruct))
	{
		inst[i].setFont(font3);
		inst[i].setCharacterSize(14);
		inst[i].setString(instruct);
		inst[i].setPosition(720 * 0.26, 800 * (0.34 + i * 0.02));
		inst[i].setFillColor(Color::Blue);
		i++;
		count++;
	}
	file.close();
}

//The constructor initializes the instructions	
store_data::store_data()
{
	instructions();
}

//This function gets the score from file and creates text objects to display
void store_data::score()
{
	file.open("score.txt");
	for (int i = 0; i < 5; i++)
	{
		file >> arr[i];
	}
	file.close();
	for (int i = 0; i < 5; i++)
	{
		scores[i].setFont(font3);
		scores[i].setCharacterSize(24);
		scores[i].setStyle(Text::Bold);
		scores[i].setString(to_string(arr[i]));
		scores[i].setPosition(720 * 0.45, 800 * (0.37 + i * 0.05));
		scores[i].setFillColor(Color::Blue);
	}
	scores[5].setFont(font3);
	scores[5].setCharacterSize(16);
	scores[5].setStyle(Text::Bold);
	scores[5].setPosition(720 * 0.40, 800 * (0.37 + 5 * 0.05));
	scores[5].setFillColor(Color::Blue);
	scores[5].setString("ESC to return...");
}


//Displays instructions
void store_data::display_instructions(sf::RenderTarget* target)
{
	for (int i = 0; i < count; i++)
		target->draw(this->inst[i]);
}

//Displays high scores
void store_data::display_highscores(sf::RenderTarget* target)
{
	score();
	for (int i = 0; i < 5; i++)
	{
		scores[i].setString("" + to_string(i + 1) + "." + to_string(arr[i]));
		target->draw(this->scores[i]);
	}
	target->draw(this->scores[5]);
}

//Adds score to highscore list if eligible
bool store_data::check(int s)
{
	file.open("score.txt");
	for (int i = 0; i < 5; i++)
	{
		file >> arr[i];
	}
	file.close();
	bool check = false;
	if (s > arr[0])
		check = true;
	int tmp;
	for (int i = 0; i < 5; i++)
	{
		if (s > arr[i])
		{
			tmp = arr[i];
			arr[i] = s;
			s = tmp;
		}
	}
	file1.open("score.txt" , ios::out);
	for (int i = 0; i < 5; i++)
	{
		file1 << arr[i] << endl;
	}
	file1.close();

	if (check)
		return true;
	return false;
}

