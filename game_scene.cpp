#include "game_scene.h"
#include "player.h"
#include "Area.h"
#include "Lose.h"
#include "MyImage.h"
#include "Win.h"
#include <vector>
#include <Windows.h>
#include<time.h>
#include "text.h"
#include<stdio.h>
#include<String>
using namespace std;

Game_Scene::Game_Scene()
	: Scene("Game")
{

	counter = 0;
	Game_Object* MyChar = new Player("MyChar");
	_game_objects[MyChar->id()] = MyChar;

	Game_Object* background = new MyImage(Vector_2D(0, 100), "background", 800, 800, "background");
	_game_objects[background->id()] = background;



	Game_Object* hp1 = new MyImage(Vector_2D(305,0),"hp1",50,50,"heart");
	_game_objects[hp1->id()] = hp1;

	Game_Object* hp2 = new MyImage(Vector_2D(375, 0), "hp2",50,50, "heart");
	_game_objects[hp2->id()] = hp2;

	Game_Object* hp3 = new MyImage(Vector_2D(445, 0), "hp3",50,50, "heart");
	_game_objects[hp3->id()] = hp3;

	Game_Object* text = new MyImage(Vector_2D(0, 50), "text", 800, 30, "text");
	_game_objects[text->id()] =text;
	_game_timer = 60000;





	
	




}

Game_Scene::~Game_Scene()
{
}

void Game_Scene::update(SDL_Window*)
{

	Player* player = (Player*)this->get_game_object("MyChar");
	_game_timer -= player->getSimulateTime();
	
	if (player->_health > 0 && _game_timer>0) {
		float b = 150 + rand() % 750 + 0.1f;
		if (timer == 0) {
			string rockID = to_string(++counter);
			Game_Object* area1 = new Area(Vector_2D(800, b),rockID);
			
			this->add_game_object(area1);
			
			objList.push_back(area1->id());
		}

		timer += 0.1f;
		if (timer > 1)
			timer = 0;

		
	}
	else if(_game_timer<=0&& player->_health > 0)
	{
		Game_Object* win = new Win();
		_game_objects["win"] = win;
		for (int i = 0; i < objList.size(); i++)
		{
			if (_game_objects.find(objList.at(i)) != _game_objects.end())
					this->remove_game_object(objList.at(i));
		}


	}
	else {
		
		Game_Object* lose = new Lose();
		_game_objects["lose"] = lose;
		for (int i = 0; i < objList.size(); i++)
		{
			if (_game_objects.find(objList.at(i)) != _game_objects.end())
				this->remove_game_object(objList.at(i));
		}
		
	}
	if (objList.size() > 0)
	{
		for (int i = 0; i < objList.size(); i++)
		{
			if(_game_objects.find(objList.at(i)) != _game_objects.end())
			if (this->get_game_object(objList.at(i))->translation().x() < 0)
				this->remove_game_object(objList.at(i));
		}
    }


	if (player->_health == 2)
	{
		this->remove_game_object("hp3");

	}
	else if (player->_health == 1)
	{
		this->remove_game_object("hp2");
	}
	else if (player->_health == 0)
	{
		this->remove_game_object("hp1");
	}

	
	
}

