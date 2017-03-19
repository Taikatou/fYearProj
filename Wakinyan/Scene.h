#pragma once
#include <SDL.h>
#include <string>
#include "Character.h"
#include "Sprite.h"
#include <vector>

class Scene
{
public:
	Character character;
	std::vector<Sprite>* Sprites;
	Scene();
	~Scene();
	bool loadFromFile(std::string path);
	void free();
	void update(SDL_Event& e);
	void render();
	std::string changeScene(Sprite* collisionTrigger);
private:
	bool _changeScene;
};