#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include<sstream>
#include<string>
#include<SFML/Audio.hpp>
using namespace std;
using namespace sf;
class Play
{
private:
	//Initialize game variables
	const float cell_size = 40.0;
	const int w_cnt = 10;
	const int h_cnt = 20;
	int world[20][10] = { 0 };
	int world_temp[20][10] = { 0 };
	int next = rand() % 7;//to initialize with a random block on new block as (kind=next in new block function)
	float px, py;//preview ..it is made float to get preview blocks to center with adding 0.5 or something
	int kind;// block kind (block from 1 to 7)
	int cx, cy;
	int sx, sy;
	int cl_row;
	int to = 0 , from = 0;
	

	int block[7][4][4] = 
	{
	1,1,1,1,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,

	1,0,0,0,
	1,1,0,0,
	0,1,0,0,
	0,0,0,0,

	0,1,0,0,
	1,1,0,0,
	1,0,0,0,
	0,0,0,0,

	1,1,0,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,

	1,0,0,0,
	1,1,0,0,
	1,0,0,0,
	0,0,0,0,

	1,0,0,0,
	1,0,0,0,
	1,1,0,0,
	0,0,0,0,

	0,1,0,0,
	0,1,0,0,
	1,1,0,0,
	0,0,0,0,
	};
	int block_board[7][4][4];
	int check_line[20] = { 0 };

	sf::Clock clock;
	//sf::Clock clock1;

	bool line_check = false;
	bool stop_animation = true;//intentionally made true
	
	sf::RectangleShape cell, grid, explode, shadow, preview_border, preview_border1, p_block, dead_block;
	sf::Texture texture;
	sf::Vector2u textureSize;

	void initGameObj();
	Sound sfx_clearline;
	SoundBuffer buffer_clearline;

	Sound sfx_gameover;
	SoundBuffer buffer_gameover;

	Sound sfx_combo1;
	SoundBuffer buffer_combo1;

	Sound sfx_harddrop;
	SoundBuffer buffer_harddrop;

	Font font;
	Text txt, scr, gameisover, final_score, highscore;

	float game_speed;
	int new_score_on_clearing();
public:
	//Initialize game variables
	Play();
	bool game_over_check=false;
	int score_value = 0;
	string score_value_converted_string = to_string(score_value);
	int volume_value=0;

	Sound sfx_mainsound;
	SoundBuffer buffer_mainsound;

	 //NEW FUNCTION
	//Functions for the game logic
	void rotate();
	void game_over();// bool game_over();
	void new_block();
	void preview_block();
	bool check_block();
	void clear_lines();
	void clear_lines_d();
	bool go_down();
	
	

	//Update
	void update();
	
	//Render
	void Render(sf::RenderTarget* target);
	void p_draw(sf::RenderTarget* target);
	void draw_cell(sf::RenderTarget* target);

	void Checkevent(sf::Event ev);

	bool shadow_check();
	void draw_shadow(sf::RenderTarget* target);
	void clear_anm(sf::RenderTarget* target);
	void draw_block(sf::RenderTarget* target);
	void draw_world(sf::RenderTarget* target);
	void draw_Pblock(sf::RenderTarget* target);

	void draw_dead_block(sf::RenderTarget* target);
	void clear_game(sf::RenderTarget* target);
	//void mainsound_Play(sf::RenderTarget* target);
	void draw_high(sf::RenderTarget* target);

	int score();
};


