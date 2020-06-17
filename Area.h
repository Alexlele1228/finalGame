#pragma once

#include "game_object.h"
#include <vector>
#include<random>

class Area : public Game_Object
{
public:
	Area(Vector_2D,std::string);
	~Area();
	std::vector<std::string>list = {"a"};
	bool hitAlready(std::string);
	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config) override;

	
private:
	int _change_direction_timer;
	std::minstd_rand0 _generator;
	
};