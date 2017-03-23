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
	std::vector<SDL_Rect> colliders;
	std::vector<Interaction> sInteractions;
	Scene();
	~Scene();
	bool loadFromFile(const char* path);
	bool checkCollision();
	bool checkSceneChange() const;
	void checkInteractions();
	void free();
	void update(SDL_Event& e);
	void render();
	std::string changeScene();
private:
	std::string _newScenePath;
	bool _changeScene;
	int sceneWidth;
	int sceneHeight;
};