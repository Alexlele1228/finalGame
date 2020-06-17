#include "assets.h"
#include "texture.h"
#include "animated_texture.h"
#include "sound.h"

#include <iostream>

Assets::Assets(SDL_Renderer* renderer)
{
	
	{
	
		const int frame_count = 1;
		const Uint32 frame_duration_milliseconds = 100;
		Asset* player_animated_texture = new Animated_Texture("My_Char_Dead", "Assets/my_char_dead.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[player_animated_texture->id()] = player_animated_texture; 
	}

	{

		const int frame_count = 1;
		const Uint32 frame_duration_milliseconds = 100;
		Asset* player_animated_texture = new Animated_Texture("win", "Assets/win.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[player_animated_texture->id()] = player_animated_texture;
	}

	{

		const int frame_count = 1;
		const Uint32 frame_duration_milliseconds = 100;
		Asset* player_animated_texture = new Animated_Texture("heart", "Assets/heart.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[player_animated_texture->id()] = player_animated_texture;
	}

	{

		const int frame_count = 1;
		const Uint32 frame_duration_milliseconds = 100;
		Asset* player_animated_texture = new Animated_Texture("background", "Assets/river.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[player_animated_texture->id()] = player_animated_texture;
	}

	{

		const int frame_count = 1;
		const Uint32 frame_duration_milliseconds = 100;
		Asset* player_animated_texture = new Animated_Texture("lose", "Assets/lose.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[player_animated_texture->id()] = player_animated_texture;
	}

	{

		const int frame_count = 1;
		const Uint32 frame_duration_milliseconds = 100;
		Asset* player_animated_texture = new Animated_Texture("text", "Assets/text.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[player_animated_texture->id()] = player_animated_texture;
	}
	


	{
		const int frame_count = 7;
	    const Uint32 frame_duration_milliseconds = 100;
	    Asset* player_animated_texture = new Animated_Texture("My_Char_Idle", "Assets/My_Char_Idle.png", renderer, frame_count, frame_duration_milliseconds);
	    _assets[player_animated_texture->id()] = player_animated_texture; 
	
	}

	{

		const int frame_count = 7;
		const Uint32 frame_duration_milliseconds = 100;
		Asset* player_animated_texture = new Animated_Texture("My_Char_Attack", "Assets/my_char_attack.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[player_animated_texture->id()] = player_animated_texture;
	}


	{
		const int frame_count = 7;
		const Uint32 frame_duration_milliseconds = 100;
		Asset* player_animated_texture = new Animated_Texture("My_Char_jumping", "Assets/my_char_jumping.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[player_animated_texture->id()] = player_animated_texture;

	}



	{
		const int frame_count = 7;
		const Uint32 frame_duration_milliseconds = 100;
	    Asset* player_animated_texture = new Animated_Texture("My_Char_Walking", "Assets/my_char_walking.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[player_animated_texture->id()] = player_animated_texture;

	}


	{
		const int frame_count = 7;
		const Uint32 frame_duration_milliseconds = 100;
		Asset* player_animated_texture = new Animated_Texture("My_Char_Hit", "Assets/My_Char_Hit.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[player_animated_texture->id()] = player_animated_texture;

	}

	{
		const int frame_count = 7;
		const Uint32 frame_duration_milliseconds = 100;
		Asset* player_animated_texture = new Animated_Texture("My_Char_dying", "Assets/my_char_dying.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[player_animated_texture->id()] = player_animated_texture;

	}

	{
		Sound* sound = new Sound("Sound.Music", "Assets/background.wav");
		_assets[sound->id()] = sound;

		Mix_PlayChannel(0, sound->data(), -1);
	}

	{
		Sound* sound = new Sound("Sound.Walking", "Assets/char_walking.wav");
		_assets[sound->id()] = sound;
	}

	{
		Sound* sound = new Sound("Sound.Attacking", "Assets/char_attack.wav");
		_assets[sound->id()] = sound;
	}

	{
		Sound* sound = new Sound("Sound.win", "Assets/win.wav");
		_assets[sound->id()] = sound;
	}

	{
		Sound* sound = new Sound("Sound.dying", "Assets/char_dying.wav");
		_assets[sound->id()] = sound;
	}


	{
		Sound* sound = new Sound("Sound.get_hit", "Assets/char_get_hit.wav");
		_assets[sound->id()] = sound;

	}

	{
		Sound* sound = new Sound("Sound.lose", "Assets/game_lose.wav");
		_assets[sound->id()] = sound;
	}

	{
		const int frame_count = 1;
		const Uint32 frame_duration_milliseconds = 100;
		Asset* player_animated_texture = new Animated_Texture("rocks", "Assets/a.png", renderer, frame_count, frame_duration_milliseconds);
	    _assets[player_animated_texture->id()] = player_animated_texture;
	}



	
}

Assets::~Assets()
{

}

Asset* Assets::get_asset(std::string id)
{
	if (_assets.find(id) == _assets.end())
	{
		std::cout << "Attempted to find an asset that was not loaded. ID: " << id << std::endl;
		exit(1);
	}

	return _assets[id];
}