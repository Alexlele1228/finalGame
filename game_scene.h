#pragma once

#include "scene.h"

class Game_Scene : public Scene
{
public:
	Game_Scene();
	~Game_Scene();
	int counter;
	float timer = 0;

	virtual void update(SDL_Window* window) override;

private:
	std::vector<std::string>objList;
	

};