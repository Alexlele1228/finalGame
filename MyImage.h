#pragma once

#include "game_object.h"


class MyImage : public Game_Object
{
public:
	MyImage(Vector_2D, std::string, int ,int,std::string);
	~MyImage();

	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config) override;
	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;





};
