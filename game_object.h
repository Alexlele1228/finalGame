#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <string>

#include "assets.h"
#include "input.h"
#include "vector_2D.h"
#include "configuration.h"
#include "circle_2D.h"
#include "scene.h"


class Game_Object
{
public:
	Game_Object(std::string id, std::string texture_id);
	~Game_Object();
	
	
	std::string id();
	

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) = 0;
	virtual void simulate_physics(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene);
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config);

	Vector_2D translation();
	Circle_2D collider();
	int height();
	int width();



	void set_translation(Vector_2D translation);
	void setTextureId(std::string a);
protected:
	std::string _id;
	std::string _texture_id;

	Circle_2D _collider;

	//float _x;
	//float _y;
	Vector_2D _translation;

	Vector_2D _velocity;

	int _width;
	int _height;

	SDL_RendererFlip _flip;
};