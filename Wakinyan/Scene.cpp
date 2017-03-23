#include "Scene.h"
#include "main.h"
#include "tinyxml.h"

Scene::Scene()
{
	character = new Character;
	_changeScene = false;
	sceneWidth = 0;
	sceneHeight = 0;
}

Scene::~Scene()
{
	free();
}

bool Scene::loadFromFile(const char * path)
{
	bool success = true;

	//load file that defines a scene
	TiXmlDocument sceneFile(path);
	if (sceneFile.LoadFile())
	{
		TiXmlElement* sceneRoot = sceneFile.RootElement();
		if (strcmp(sceneRoot->Value(), "spriteList") == 0)
		{
			//loop through elements in the file, checking type and adding to:
			// collider list, sprite list, camera, character, background
			for (TiXmlElement* sprite = sceneRoot->FirstChildElement(); sprite; sprite = sprite->NextSiblingElement())
			{
				TiXmlElement* temp = sprite->FirstChildElement();
				// extract the sprite type from the XML element
				const char* t = (temp->FirstChild()->Value());
				int type = std::atoi(t);
				std::string spriteImagePath;
				bool animate = false;

				if (type == CHARACTER)
				{
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "name") == 0)
					{
						character->setName(temp->FirstChild()->Value());
					}

					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "image") == 0)
					{
						spriteImagePath = temp->FirstChild()->Value();
					}

					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "x") == 0)
					{
						character->setX( std::stoi(temp->FirstChild()->Value()));
					}

					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "y") == 0)
					{
						character->setY( std::stoi(temp->FirstChild()->Value()));
					}

					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "animation") == 0)
					{
						if (strcmp(temp->FirstChild()->Value(), "true") == 0)
						{
							animate = true;
						}
						if (!character->setSprite(std::string(spriteImagePath), animate))
						{
							success = false;
						}
					}
				}
				else if (type == SPRITE)
				{
					//load a sprite
					int x = 0, y = 0;
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "image") == 0)
					{
						spriteImagePath = temp->FirstChild()->Value();
					}
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "x") == 0)
					{
						x = std::stoi(temp->FirstChild()->Value());
					}
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "y") == 0)
					{
						y = std::stoi(temp->FirstChild()->Value());
					}
					Sprite* tempSprite = new Sprite;
					if (!tempSprite->loadFromFile(spriteImagePath))
					{
						success = false;
					}
					tempSprite->setXPos(x);
					tempSprite->setYPos(y);
					sprites.push_back(tempSprite);

				}
				else if (type == COLLISION_TRIGGER)
				{
					//load a collider
					// itterate to the next sibling ot the sceneRoot
				}
				else if (type == BACKGROUND)
				{
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "image") == 0)
					{
						spriteImagePath = temp->FirstChild()->Value();
					}
					if (!background.loadFromFile(std::string(spriteImagePath)))
					{
						success = false;
					}
				}
				else if (type == CAMERA)
				{
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "sceneWidth") == 0)
					{
						sceneWidth = std::stoi(temp->FirstChild()->Value());
					}
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "sceneHeight") == 0)
					{
						sceneHeight = std::stoi(temp->FirstChild()->Value());
					}

					camera = { 0, 0, sceneWidth, sceneHeight };
				}
			}
		}
	}

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
		(*vSprite)->render((*vSprite)->getXPos() - camera.x, (*vSprite)->getYPos() - camera.y);
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
