#include "Play.h"

void Play::initGameObj()
{
	//Initializing game objects

	this->cell.setSize(sf::Vector2f(cell_size, cell_size));//for falling blocks themselves in the game

	//Loads the texture from file and sets it to required size
	this->texture.loadFromFile("texture/image.png");
	this->cell.setTexture(&texture);
	this->textureSize = texture.getSize();
	this->textureSize.x /= 10;
	this->textureSize.y /= 1;
	this->texture.setSmooth(false);

	//For the background grid in game
	this->grid.setSize(sf::Vector2f(cell_size - 1, cell_size - 1));

	//For blocks after game is over
	this->dead_block.setSize(sf::Vector2f(cell_size - 2, cell_size - 2));
	this->dead_block.setTexture(&texture);

	//For explosion of the block while clearing
	this->explode.setSize(sf::Vector2f(cell_size - 15, cell_size - 15));
	this->explode.setTexture(&texture);

	//For shadow of the blocks at the bottom of the board
	this->shadow.setSize(sf::Vector2f(cell_size - 2, cell_size - 2));

	//For preview of the new block
	this->preview_border.setSize(sf::Vector2f(320, h_cnt * cell_size));// to get that white line that seperates the grid from side window
	preview_border.setFillColor(sf::Color(100, 100, 100, 150));
	preview_border.setOutlineThickness(1);
	preview_border.setPosition(w_cnt * cell_size, 0);

	this->preview_border1.setSize(sf::Vector2f(cell_size * 4, cell_size * 4));//to get the preview block window border(that white border)
	preview_border1.setFillColor(sf::Color(25, 0, 0, 255));
	preview_border1.setOutlineThickness(-1);
	preview_border1.setPosition((w_cnt + 2) * cell_size, cell_size * 2);
	/*for (int y = 0; y<20; y++)
		for (int x = 0; x < 10; x++)
		{
			
			world[y][x] = 0;//just to get them to 0..i know it is done on default..but ..was trying to solve buffer over run warning
			world_temp[y][x] = 0;
			
		}
		*/
	
	game_speed = 0.5;
	game_over_check = false;

	//Initializing sounds
	buffer_clearline.loadFromFile("audio/clearline.ogg");
	sfx_clearline.setBuffer(buffer_clearline);


	/*

	Sound sfx_combo1;
	SoundBuffer buffer_combo1;
	buffer_combo1.loadFromFile("audio/combo_1.ogg");
	sfx_combo1.setBuffer(buffer_combo1);
	*/
	buffer_gameover.loadFromFile("audio/gameover.ogg");
	sfx_gameover.setBuffer(buffer_gameover);

	buffer_harddrop.loadFromFile("audio/harddrop.ogg");
	sfx_harddrop.setBuffer(buffer_harddrop);
	
	buffer_mainsound.loadFromFile("audio/tetris.ogg");
	sfx_mainsound.setBuffer(buffer_mainsound);
	sfx_mainsound.setLoop(true);
    sfx_mainsound.play();
	
	//Initializing fonts and texts
	if (!font.loadFromFile("texture/8bitlimr.ttf"))
		throw("Could not load font!");
	txt.setFont(font);
	txt.setCharacterSize(24);
	txt.setStyle(Text::Bold);
	txt.setString("Next Block");
	txt.setPosition(720 * float(0.69), 800 * float(0.05));
	
	gameisover.setFont(font);
	gameisover.setCharacterSize(50);
	gameisover.setStyle(Text::Bold);
	gameisover.setFillColor(Color::Red);
	gameisover.setString("GAME OVER");
	gameisover.setPosition(720 * 0.10, 800 * 0.43);

	highscore.setFont(font);
	highscore.setCharacterSize(45);
	highscore.setStyle(Text::Bold);
	highscore.setFillColor(Color::Color(34, 139, 34));
	highscore.setString("HIGH SCORE!!!");
	highscore.setPosition(720 * 0.10, 800 * 0.35);

	scr.setFont(font);
	scr.setCharacterSize(24);
	scr.setString("SCORE : " + score_value_converted_string);
	scr.setPosition(720 * float(0.69), 800* float(0.6));

	final_score.setFont(font);
	final_score.setCharacterSize(25);
	final_score.setStyle(Text::Bold);
	final_score.setFillColor(Color::Red);
}


Play::Play()
{
	srand((unsigned int(time(NULL))));
	new_block();
	preview_block();
	this->initGameObj();

}
void Play::clear_lines()
{                    //which is called after 0.5 sec to create time gap between clearning and falling of block...
	int var;//this variable is to store the row number that are cleared to this array check_line[] )

	to = h_cnt - 1;
	//from bottom line to top line...
	for (from = h_cnt - 1; from >= 0; from--)
	{
		int cnt = 0;
		for (int x = 0; x < w_cnt; x++)
			if (world[from][x])
				cnt++;

		if (cnt < w_cnt)
		{
			if (to != from)
			{
				line_check = true;
				this->sfx_clearline.setVolume(float(this->volume_value * 10));
				sfx_clearline.play();
			}

			for (int x = 0; x < w_cnt; x++)
			{
				world_temp[to][x] = world[from][x];
			}
			to--;

		}
	}
	for (to = h_cnt - 1; to >= 0; to--) //removes block if needed
	{
		var = to;
		int cnt = 0;
		for (int x = 0; x < w_cnt; x++)
			if (world[to][x])
				cnt++;
		if (cnt == w_cnt)
		{
			for (int x = 0; x < w_cnt; x++)
			{
				world[to][x] = 0;
				check_line[var] = 1;//since multiple row can be cleared at once,,this takes value 1 if row is to vleared and 0 otherwise
				//goes for all 20 rows,this variable is again use below in animation drawing function..it reads value for which row to clear from this variable
				stop_animation = false;
			}
			score_value += new_score_on_clearing();
			if (game_speed > 0.25)
				game_speed -= static_cast<float>(0.01);//decreases falling speed
			if (game_speed <= 0.25)
				game_speed = 0.25;
		}
		else
			check_line[var] = 0;
	}

	score_value_converted_string = to_string(score_value);
};


void Play::game_over() 
{
	int temp2 = 4;
	if (kind == 0)
		temp2 = 3; //because(____) this starts from 3
	for (int y = 0; y < 4; y++)for (int x = 0; x < 4; x++)
		if (block_board[kind][y][x])
			if (world_temp[y][x + temp2])
			{
				game_over_check=true;
				sfx_mainsound.pause();
				this->sfx_gameover.setVolume(float(this->volume_value * 10));
			    sfx_gameover.play();

			}
};
int Play::new_score_on_clearing()
	 {
		 if (game_speed >= 0.45)
			 return 50;
		 else if (game_speed < 0.45 && game_speed >= 0.4)
			 return 75;
		 else if (game_speed < 0.4 && game_speed >= 0.35)
			 return 100;
		 else if (game_speed < 0.35 && game_speed >= 0.3)
			 return 125;
		 else if (game_speed < 0.3 && game_speed>0.25)
			 return 150;
		 else if (game_speed == 0.25)
			 return 200;
		 else
			 return 0;
	 }

void Play::new_block()
{
	kind = next, cx = 4, cy = 0;//cx is set to 4 so to make blocks fall from the center from the top of the grid...if cx=0,block fall from left most part
	for (int y = 0; y < 4; y++)//kind=next because kind should be the block seen in the preview window(next is for preview window..read comment below)
		for (int x = 0; x < 4; x++)
			block_board[kind][y][x] = block[kind][y][x];// we are writing value is block_board()() to cause that delay effect..ask me if confused
	if (kind == 0)
		cx--;
}

void Play::preview_block()
{
	next = rand() % 7;//(next is used for block for preview window)
	px = w_cnt + static_cast<float>(3.0);
	py = 2+0.5;
	if (next == 0)//for this(----) block to get it to center in the preview window
	{
		py = 2 + 1.5;
		px--;//remove this px-- and run the program and look for(----) this block in preview window...you will see why it is added
	}
	if (next == 3) {
		py = 2 + 1;//for square block
	}
}
bool Play::check_block()
{
	for (int y = 0; y < 4; y++)for (int x = 0; x < 4; x++)
	{
		if (block_board[kind][y][x] == 0) continue;
		if (x + cx < 0 || x + cx >= w_cnt || y + cy >= h_cnt) return false; // hit wall
		if (world[cy + y][cx + x]) return false;//hit another block
	}
	return true;
}



void Play::clear_lines_d()
{
	for (int y = h_cnt - 1; y >= 0; y--)for (int x = 0; x < w_cnt; x++)
	{
		world[y][x] = world_temp[y][x];
	}
	stop_animation = true;
}


void Play::rotate()
{
	int len = 0; //to check rotation block size
	int temp[4][4];// check rotation block size
	int d[4][4] = { 0 };
	for (int y = 0; y < 4; y++)for (int x = 0; x < 4; x++)
	{
		temp[y][x] = block_board[kind][y][x];
		if (block_board[kind][y][x])
			len = std::max(std::max(x, y) + 1, len);
	}

	//rotate conter-clock wise 90 degree
	for (int y = 0; y < len; y++)for (int x = 0; x < len; x++)
		if (block_board[kind][y][x])
			d[len - 1 - x][y] = 1;// d[x][len - 1 - y] for clockwise if we add clockwise button as well
	for (int y = 0; y < 4; y++)for (int x = 0; x < 4; x++)
		block_board[kind][y][x] = d[y][x];
	if (!check_block())
		for (int y = 0; y < 4; y++)for (int x = 0; x < 4; x++)
			block_board[kind][y][x] = temp[y][x];

}

bool Play::go_down()
{
	cy++;
	if (check_block() == false)
	{
		cy--;
		score_value += new_score_on_clearing()/ 20;
		for (int y = 0; y < 4; y++)for (int x = 0; x < 4; x++)
			if (block_board[kind][y][x])
			{

				if (!game_over_check)
					world[cy + y][cx + x] = kind + 1;//+1 to avoid 0 because kind starts from zero...ask me if not clear
				//solved!! now gameover takes world_temp value...
			}

		clear_lines();
		if (!game_over_check)//this is new change i made on july 24 ask me
		{
			new_block();
			game_over();
			preview_block();

		}

		return false;
	}
	else return true;
};

void Play::update()
{
	
	 static float prev = clock.getElapsedTime().asSeconds();
	
	if (clock.getElapsedTime().asSeconds() - prev >= game_speed)
	{
		go_down();
		prev = clock.getElapsedTime().asSeconds();

	}
	static float prev1 = clock.getElapsedTime().asSeconds();
	if (clock.getElapsedTime().asSeconds() - prev1 >= 0.4)
	{
		prev1 = clock.getElapsedTime().asSeconds();

		if (line_check == true)
		{
			clear_lines_d();
			line_check = false;
		}
	}
}
	

void Play::Render(sf::RenderTarget* target)
{
	for (int a = 0; a < w_cnt; a++)for (int b = 0; b < h_cnt; b++)
	{
		this->grid.setPosition(cell_size * static_cast<float> (a), cell_size * static_cast<float> (b));
		this->grid.setFillColor(sf::Color(50, 50, 100, 250));
		target->draw(this->grid);
	}
	target->draw(this->preview_border);
	target->draw(this->preview_border1);
	target->draw(this->txt);
	if (!game_over_check)
	{
		scr.setString("score : " + score_value_converted_string);
		target->draw(this->scr);
	}


}


void Play::draw_block(sf::RenderTarget* target)
{
	this->cell.setTextureRect(sf::IntRect(textureSize.x * kind, textureSize.y * 0, textureSize.x, textureSize.y));
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if(block_board[kind][y][x])
			{
				this->cell.setPosition(sf::Vector2f((cx + x) * cell_size, (cy + y) * cell_size));//cy increase by 1 every 0.5 sec to drop block continuiosly
				target->draw(this->cell);
			}
		}
	}
}


void Play::draw_world(sf::RenderTarget* target)
{
	for (int y = 0; y < h_cnt; y++)for (int x = 0; x < w_cnt; x++)
		if (world[y][x])
		{
			cell.setTextureRect(sf::IntRect(textureSize.x * (world[y][x] - 1), textureSize.y * 0, textureSize.x, textureSize.y));
			cell.setPosition(sf::Vector2f(x * cell_size, y * cell_size));
			target->draw(cell);
		}
	
}




bool Play::shadow_check()
{
	sx = cx;
	for (int y = 0; y < 4; y++)for (int x = 0; x < 4; x++)
		{
			if (block_board[kind][y][x])
			{
				if (y + sy >= h_cnt)
				{
					sy--;
					return false;
				}
				if (world[sy + y][cx + x])
				{
					sy--;
					return false;
				}
			}
		}
	return true; 
}

void Play::draw_shadow(sf::RenderTarget* target)
{
	shadow.setFillColor(sf::Color(100, 100, 100, 255));
	while (shadow_check())
		sy++;
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
		{	
			if (block_board[kind][y][x])
			{
				shadow.setPosition(sf::Vector2f((sx + x) * cell_size, (sy + y) * cell_size));
				target->draw(shadow);
			}
		}
	sy = cy;
}

void Play::clear_anm(sf::RenderTarget* target)
{
	if (!stop_animation)
	{
		for (int j = 0; j < 20; j++)
			if (check_line[j] == 1)
				for (int x = 0; x < w_cnt; x++)
				{
					this->explode.setTextureRect(sf::IntRect(textureSize.x * 9, 0, textureSize.x, textureSize.y));
					this->explode.setPosition(sf::Vector2f(x * cell_size + float(7.5), j * cell_size + float(7.5)));
					target->draw(explode);
				}
	}
}



void Play::draw_Pblock(sf::RenderTarget* target)
{
	this->cell.setTextureRect(sf::IntRect(textureSize.x * next, textureSize.y * 0, textureSize.x, textureSize.y));

	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
		{
			if (block[next][y][x])
			{
				cell.setPosition(sf::Vector2f((px + x) * (cell_size), (py + y) * (cell_size)));
				target->draw(cell);
			}
		}
}
void Play::draw_dead_block(sf::RenderTarget* target)
{
	int temp = 4;//this part is new in slight change 2(from here to 'there' down)
	if (kind == 0)
		temp = 3;//because this block(----) starts from cx=3 and other block from cx=4
	for (int yy = 0; yy < 4; yy++)for (int xx = 0; xx < 4; xx++)
	{//this loop updates the value of world for the block that causes gameover,that final block is also displayed by this function
		if (block_board[kind][yy][xx])
		{
			world_temp[yy][xx + temp] = kind + 1;//we can write just 1 here..next+1 is not necesary..i did it to test for some bug

		}
		//there
	}
	for (int b = 0; b < h_cnt; b++) for (int a = 0; a < w_cnt; a++)//finally,the dead block
	{
		if (world_temp[b][a])
		{
			dead_block.setTextureRect(sf::IntRect(textureSize.x * 8, 0, textureSize.x, textureSize.y));
			dead_block.setPosition(cell_size * static_cast<float>(a), cell_size * static_cast<float>(b));

			target->draw(dead_block);
		}
	}
	target->draw(this->gameisover);
	if (score_value > 0) {
		final_score.setPosition(720 * float(0.14), 800 * float(0.5));
	}
	else if (score_value == 0)
	{
		final_score.setPosition(720 * float(0.17), 800 * float(0.5));
	}
	
	final_score.setString("SCORE  " + score_value_converted_string);
	target->draw(this->final_score);
}
void Play::clear_game(sf::RenderTarget* target)
{
	
		score_value = 0;
		score_value_converted_string = to_string(score_value);

		for (int y = 0; y < h_cnt; y++)
		for (int x = 0; x < w_cnt; x++)
		{
			world[y][x] = 0;
			world_temp[y][x] = 0;
		}
		
		new_block();
		preview_block();
		sfx_gameover.pause();
		//sfx_mainsound.play();
		game_over_check = false;
		game_speed = 0.5;
		
		
}
void Play::draw_high(sf::RenderTarget* target)
{
	target->draw(this->highscore);
}
int Play::score()
{
	if (game_over_check)
		return score_value;
	return 0;
}
void Play::Checkevent(sf::Event e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		if (e.key.code == sf::Keyboard::Left)
		{
			cx--;
			if (check_block() == false) cx++;
		}
		else if (e.key.code == sf::Keyboard::Right)
		{
			cx++;
			if (check_block() == false) cx--;
		}
		else if (e.key.code == sf::Keyboard::Down)
		{
			go_down();
		}
		else if (e.key.code == sf::Keyboard::Space)
		{
			
			if (line_check == true)
				clear_lines_d();// this is necessary, you can ask me
			while (go_down() == true);
			this->sfx_harddrop.setVolume(float(this->volume_value * 10));
			sfx_harddrop.play();
		}
		else if (e.key.code == sf::Keyboard::Up)
			rotate();	
	}
}
