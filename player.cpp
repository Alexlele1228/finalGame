#pragma once

#include "player.h"
#include "sound.h"

#include <iostream>
#include<Windows.h>
#include <SDL_mixer.h>

Player::Player(std::string id)
	: Game_Object(id, "My_Char_Idle")
{
	_speed = 0.1f;
	_health = 3;
	
	_is_hit = false;
	_is_dead = false;
	_win = false;
	_chance_to_attack = 2;
	_has_chance = true;

	_translation = Vector_2D(0, 150);

	_collider.set_radius(_width / 5.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height));

	_state.push(State::Idle);
}

Player::~Player()
{
}

void Player::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config);
}

void Player::get_hit()
{
	if (_health > 1)
	{
		_health--;
		_is_hit = true;
	}
	else
	{
		_health--;
		_is_hit = true;
		_is_dead = true;
	}
}

bool Player::game_win(Scene* scene)
{
	if (scene->get_game_timer() <= 0 && _health > 0)
		return true;
	else
		return false;

}


void Player::simulate_AI(Uint32 , Assets* assets, Input* input, Scene* scene)
{
	_win = game_win(scene);

	switch(_state.top())
	{
		case State::Idle:
		
			if (!_win) {
				if (_velocity.magnitude() > 0.0f)
				{
					push_state(State::Walking, assets);
				}
				if (_is_hit)
				{
					_animation_timer = 600;
					push_state(State::Hit, assets);
				}
				if (input->is_button_state(Input::Button::Attacking, Input::Button_State::DOWN) && _has_chance)
				{
					_animation_timer = 600;
					push_state(State::Attack, assets);
				}
			}
			else {
				push_state(State::Jumping, assets);
			}
			
		
		    break;

		case State::Attack:
			if (!_win) {
				if (_chance_to_attack > 0)
				{
					_animation_timer -= this->getSimulateTime();
					if (_animation_timer <= 0) {
						pop_state(assets);
					}
				}
				else
				{
					_has_chance = false;
					pop_state(assets);
					
				}

		   }

			break;

			
		case State::Walking:
			if (!_win) {
				if (_velocity.magnitude() == 0.0f)
				{
					push_state(State::Idle, assets);
				}
				if (_is_hit)
				{
					_animation_timer = 600;
					push_state(State::Hit, assets);
				}
				if (input->is_button_state(Input::Button::Attacking, Input::Button_State::DOWN) && _has_chance)
				{
					_animation_timer = 600;
					push_state(State::Attack, assets);
				}

			}
			else {
				push_state(State::Jumping, assets);
			}
         	break;

		
		
		case State::Jumping:
		

		
			break;

		case State::Hit:
			if (!_win) {
				std::cout << "sdf";
				_is_hit = false;
				if (!_is_dead) {
					_animation_timer -= this->getSimulateTime();
					if (_animation_timer <= 0) {
						pop_state(assets);
					}
				}
				else {
					std::cout << "123";
					_animation_timer = 500;
					push_state(State::Dying, assets);
				}
			}
			else {
				push_state(State::Jumping, assets);
			}
            break;

		case State::Dead:
		
		break;

		case State::Dying:
			_animation_timer -= this->getSimulateTime();
				if (_animation_timer <= 0) {
					push_state(State::Dead, assets);
				}
		break;
	
		

	}

	_velocity = Vector_2D(0, 0);

	if(input->is_button_state(Input::Button::RIGHT, Input::Button_State::DOWN))

	{	
		if(_translation.x()<800)
		_velocity += Vector_2D(1.0f, 0);
	}

	if(input->is_button_state(Input::Button::LEFT, Input::Button_State::DOWN))
	{
		if (_translation.x() >0)
		_velocity += Vector_2D(-1.0f, 0);
	}

	if(input->is_button_state(Input::Button::UP, Input::Button_State::DOWN))
	{
		if (_translation.y() >150)
		_velocity += Vector_2D(0, -1.0f);
	}

	if(input->is_button_state(Input::Button::DOWN, Input::Button_State::DOWN))
	{
		if (_translation.y() < 850-_height)
		_velocity += Vector_2D(0, 1.0f);
	}

	_velocity.normalize();
	_velocity.scale(_speed);
}

void Player::set_speed(float speed)
{
	_speed = speed;
}
float Player::speed()
{
	return _speed;
}

void Player::push_state(State state, Assets* assets)
{
	handle_exit_state(_state.top(), assets);

	_state.push(state);
	handle_enter_state(_state.top(), assets);
}
void Player::pop_state(Assets* assets)
{
	handle_exit_state(_state.top(), assets);

	_state.pop();
	handle_enter_state(_state.top(), assets);
}

void Player::handle_enter_state(State state, Assets* assets)
{

	switch(state)
	{
		case State::Idle:
		{
			_texture_id = "My_Char_Idle";
		    break; 
		}
		case State::Walking:
		{
			_texture_id = "My_Char_Walking";
			_speed = 0.15f;
			const int walking_channel =1;
			Sound* sound = (Sound*)assets->get_asset("Sound.Walking");
			Mix_PlayChannel(walking_channel, sound->data(), 0);
			break;
		}
		case State::Jumping:
		{
			_texture_id = "My_Char_jumping";
			Sound* sound = (Sound*)assets->get_asset("Sound.win");
			Mix_PlayChannel(0, sound->data(), 0);
			break;
		}
		case State::Hit:
		{
			_texture_id = "My_Char_Hit";
			const int get_hit_channel = 2;
			Sound* sound = (Sound*)assets->get_asset("Sound.get_hit");
			Mix_PlayChannel(get_hit_channel, sound->data(), 0);
		
			break;
		}
		case State::Dying:
		{
			_texture_id = "My_Char_dying";
			const int Dying_channel =3;
			Sound* sound = (Sound*)assets->get_asset("Sound.dying");
			Mix_PlayChannel(2, sound->data(), 0);
		
			break;
		}
		
		case State::Dead:
		{
			_texture_id = "My_Char_Dead";
			Sound* sound = (Sound*)assets->get_asset("Sound.lose");
			Mix_PlayChannel(0, sound->data(), 0);

			break;
		}

		case State::Attack:
		{
			_texture_id = "My_Char_Attack";
			const int Attacking_channel = 5;
			Sound* sound = (Sound*)assets->get_asset("Sound.Attacking");
			Mix_PlayChannel(2, sound->data(), 0);

			break;
		}


	}
}

void Player::handle_exit_state(State state, Assets*)
{
	switch(state)
	{
	    case State::Idle: 
	        break; 
	   
		case State::Walking:
		{
			const int walking_channel = 1;
			Mix_HaltChannel(walking_channel);
			break;
		}
		case State::Jumping:
		{
			const int jumping_channel = 4;
			Mix_HaltChannel(jumping_channel);
			break;
		}
		case State::Hit:
		{
			const int get_hit_channel = 2;
			Mix_HaltChannel(get_hit_channel);
			break;
		}
		case State::Dead:
		{
			const int  Dead_channel = 3;
			Mix_HaltChannel(Dead_channel);
			break;
		}

		case State::Attack:
		{
			const int  Attacking_channel = 5;
			Mix_HaltChannel(Attacking_channel);
			break;
		}
	}
	



}

double Player::getSimulateTime() {
	int frame_per_sec = 60;
	int ms_per_sec = 1000;

	return ms_per_sec / frame_per_sec;
}

std::string Player::getTextureID() {
	return _texture_id;
}

void Player::useChance() {
	_chance_to_attack--;
}

bool Player::hasChance() {
	return _has_chance;
}