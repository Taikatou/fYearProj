#include "Scene.h"
#include <SDL.h>
#include <SDL_image.h>
#include "main.h"
#include "Character.h"
#include "Sprite.h"

enum SceneElements
{
	CHARACTER = 0,
	SPRITE = 1,
	COLLISION_TRIGGER = 2
};

Scene::Scene()
{
	Sprites = NULL;
	_changeScene = false;
}

Scene::~Scene()
{
	free();
}

bool Scene::loadFromFile(std::string path)
{
	bool success = false;
	//load file that defines a scene
	//the file contains what sprites and characters are in the scene
	//function returns true if it successfully loads the scene
	if (character.setSprite(path, true))
	{
		success = true;
	}

	return success;

}
void Scene::free()
{
	character.free();
	if (Sprites != NULL)
	{
		Sprites->clear();
		Sprites->erase(Sprites->begin(), Sprites->end());
	}
}

void Scene::update(SDL_Event& e)
{
	//presuming that the elements to a scene need to be rendered in a certain order
	//they will be saved in the file in the correct order with an ID
	//iterate through the vectors to fine the next elements to be rendered and call the correct render function

	character.handleEvent(e);
	if (e.type == SDL_KEYDOWN)
	{
		character.move();
	}
	
	//check for collisions
	//if there is a scene trigger it will flip the _changeScene boolean
	//change scenes

}

void Scene::render()
{
	character.render();
}

std::string Scene::changeScene(Sprite* collisionTrigger)
{
	//dereferencing the pointer
	std::string nextScene = *collisionTrigger->getName();
	free();
	return nextScene;
}
