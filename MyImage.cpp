#pragma once

#include "MyImage.h"
#include "scene.h"
#include "game_object.h"
#include "assets.h"
#include <string>
using namespace std;
MyImage::MyImage(Vector_2D a, string thisId,int width,int height,string _asset_id)
	: Game_Object(thisId, _asset_id)
{

	_width = width;
	_height = height;
	_translation = a;
	

	_velocity.normalize();
	_velocity.scale(0.1f);
}


MyImage::~MyImage()
{

}
void MyImage::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config);
}

void MyImage::simulate_AI(Uint32, Assets*, Input*, Scene* scene)
{
	scene->get_game_objects();

}



