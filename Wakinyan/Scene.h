#pragma once
#include <SDL.h>
#include <string>
#include "Character.h"
#include "Sprite.h"
#include <vector>
#include "Interaction.h"

class Scene
{
public:
	Character* character;
	Sprite background;
	SDL_Rect camera;
	std::vector<Sprite*> sprites;
	std::vector<Sprite*> screenOverlayText;
	std::vector<SDL_Rect> colliders;
	std::vector<Interaction> sAutoSceneChange;
	Scene();
	~Scene();
	void checkInteractions();
	void free();
	void update(SDL_Event& e);
	void render();
	bool loadFromFile(const char* path);
	bool checkCollision();
	bool checkThisCollision(SDL_Rect collider) const;
	bool checkSceneChange();
	std::string changeScene();
private:
	std::vector<Interaction> _sInteractions;
	std::string _newScenePath;
	bool _changeScene;
};