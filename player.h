#pragma once

#include "game_object.h"
#include "assets.h"

#include <stack>

class Player : public Game_Object
{
public:
	Player(std::string id);
	~Player();

	bool _is_hit;
	int _health;
	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config) override;

	void get_hit();
	double getSimulateTime();
	void set_speed(float speed);
	float speed();
	std::string getTextureID();
	void useChance();
	bool hasChance();

	enum class State
	{
		Idle,
		Walking,
		Jumping,
		Hit,
		Dead,
		Dying,
		Attack
	};
	void push_state(State state, Assets* assets);
	void pop_state(Assets* assets);

private:
	void handle_enter_state(State state, Assets* assets);
	void handle_exit_state(State state, Assets* assets);
	bool _is_dead;
	float _speed;
	double _animation_timer;
	bool game_win(Scene*);
	bool _win;
	int _chance_to_attack;
	bool _has_chance;
	
	std::stack<State> _state;
};