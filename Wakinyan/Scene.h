#pragma once
#include <SDL.h>
#include <string>
#include "Character.h"
#include "Sprite.h"
#include <vector>

class Scene
{
public:
	Character* character;
	Sprite background;
	SDL_Rect camera;
	std::vector<Sprite*> sprites;
	Scene();
	~Scene();
	bool loadFromFile(const char* path);
	void free();
	void update(SDL_Event& e);
	void render();
	std::string changeScene(Sprite* collisionTrigger);
private:
	bool _changeScene;
	int sceneWidth;
	int sceneHeight;
};