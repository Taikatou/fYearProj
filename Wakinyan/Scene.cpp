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
	COLLISION_TRIGGER = 2,
	BACKGROUND = 3
};

Scene::Scene()
{
	character = new Character;
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
	if (character->setSprite(path, true))
	{
		success = true;
	}

	if (background.loadFromFile("Assets/Other/backgroundBig.png"))
	{
		success = true;
	}

	character->setCharacterPosition(200, 200);

	//will read in renderer size for the scene
	sceneWidth = 800;
	sceneHeight = 600;

	//sets up camera
	camera = { 0, 0, sceneWidth, sceneHeight };

	//sets the renderer size
	if (SDL_RenderSetLogicalSize(g_renderer, sceneWidth, sceneHeight) < 0)
	{
		success = false;
	}

	return success;

}
void Scene::free()
{
	character->free();
	
	//need to destroy elements in the vector as they are pointers
//	while (sprites.size() < 0)
//	{
//		sprites.data();
//	}

	sprites.clear();
	sprites.erase(sprites.begin(), sprites.end());
}

void Scene::update(SDL_Event& e)
{
	//presuming that the elements to a scene need to be rendered in a certain order
	//they will be saved in the file in the correct order with an ID
	//iterate through the vectors to fine the next elements to be rendered and call the correct render function

	character->handleEvent(e);
	if (e.type == SDL_KEYDOWN)
	{
		character->move();
	}

	

	//check for collisions
	//if there is a scene trigger it will flip the _changeScene boolean
	//change scenes

}

void Scene::render()
{
	//centering camera over sprite
	camera.x = (character->getXPos() + character->getWidth() / 2) - sceneWidth / 2;
	camera.y = character->getYPos() - sceneHeight / 2;

	//Keep the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > SCREEN_WIDTH - camera.w)
	{
		camera.x = SCREEN_WIDTH - camera.w;
	}
	if (camera.y > SCREEN_HEIGHT - camera.h)
	{
		camera.y = SCREEN_HEIGHT - camera.h;
	}

	// renders all scene elements in order
	background.render(0, 0, &camera);
	for (std::vector<Sprite*>::iterator vSprite = sprites.begin(); vSprite != sprites.end(); ++vSprite)
	{
		(*vSprite)->render((*vSprite)->getXPos(), (*vSprite)->getYPos());
	}
	character->render(camera.x, camera.y);
}

std::string Scene::changeScene(Sprite* collisionTrigger)
{
	//dereferencing the pointer
	std::string nextScene = collisionTrigger->getName();
	free();
	return nextScene;
}
