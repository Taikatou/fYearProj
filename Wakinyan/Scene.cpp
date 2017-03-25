#include "Scene.h"
#include "main.h"
#include "tinyxml.h"
#include "Interaction.h"

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
					Character* tempChar = new Character;
#pragma region 
					tempChar->setType(type);
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "name") == 0)
					{
						tempChar->setName(temp->FirstChild()->Value());
					}

					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "image") == 0)
					{
						spriteImagePath = temp->FirstChild()->Value();
					}

					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "x") == 0)
					{
						tempChar->setX(std::stoi(temp->FirstChild()->Value()));
					}

					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "y") == 0)
					{
						tempChar->setY(std::stoi(temp->FirstChild()->Value()));
					}

					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "animation") == 0)
					{
						if (strcmp(temp->FirstChild()->Value(), "true") == 0)
						{
							animate = true;
						}
						if (!tempChar->setSprite(std::string(spriteImagePath), animate))
						{
							success = false;
						}
					}

					character = tempChar;
#pragma endregion //character load
				}
				else if (type == SPRITE)
				{
#pragma region
					int x = 0, y = 0;
					std::string name;

					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "name") == 0)
					{
						name = temp->FirstChild()->Value();
					}
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

					tempSprite->setName(name);
					tempSprite->setXPos(x);
					tempSprite->setYPos(y);
					sprites.push_back(tempSprite);
#pragma endregion //sprite load
				}
				else if (type == COLLISION_TRIGGER)
				{
#pragma region
					SDL_Rect collider;

					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "x") == 0)
					{
						collider.x = std::stoi(temp->FirstChild()->Value());
					}
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "y") == 0)
					{
						collider.y = std::stoi(temp->FirstChild()->Value());
					}
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "w") == 0)
					{
						collider.w = std::stoi(temp->FirstChild()->Value());
					}
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "h") == 0)
					{
						collider.h = std::stoi(temp->FirstChild()->Value());
					}

					colliders.push_back(collider);
#pragma endregion // collision box load
				}
				else if (type == BACKGROUND)
				{
#pragma region
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "image") == 0)
					{
						spriteImagePath = temp->FirstChild()->Value();
					}
					if (!background.loadFromFile(std::string(spriteImagePath)))
					{
						success = false;
					}
#pragma endregion //background load
				}
				else if (type == CAMERA)
				{
#pragma region
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
#pragma endregion //camera load
				}
				else if (type == INTERACTION_TRIGGER)
				{
#pragma region
					Interaction tempInteraction;

					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "x") == 0)
					{
						tempInteraction.collider.x = std::stoi(temp->FirstChild()->Value());
					}
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "y") == 0)
					{
						tempInteraction.collider.y = std::stoi(temp->FirstChild()->Value());
					}
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "w") == 0)
					{
						tempInteraction.collider.w = std::stoi(temp->FirstChild()->Value());
					}
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "h") == 0)
					{
						tempInteraction.collider.h = std::stoi(temp->FirstChild()->Value());
					}
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "path") == 0)
					{
						tempInteraction.setPath(temp->FirstChild()->Value());
					}
					temp = temp->NextSiblingElement();
					if (strcmp(temp->Value(), "interaction") == 0)
					{
						int interactionType = std::stoi(temp->FirstChild()->Value());
						tempInteraction.setType(interactionType);

						if (interactionType == CONVERSATION)
						{
							temp = temp->NextSiblingElement();
							if (strcmp(temp->Value(), "dialog") == 0)
							{
								while (strcmp(temp->Value(), "null") != 0)
								{
									tempInteraction.setDialog(temp->FirstChild()->Value());
									temp = temp->NextSiblingElement();
								}
							}
						}
					}
					
					
					sInteractions.push_back(tempInteraction);
#pragma endregion //load interactions
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

bool Scene::checkCollision()
{
	for (std::vector<SDL_Rect>::iterator sCollider = colliders.begin(); sCollider != colliders.end(); ++sCollider)
	{
		if (character->getXPos() == (sCollider->x + sCollider->w))
		{
			//checks if the character is touching the right side of the collider
			SDL_free(&sCollider);
			character->setLastMoveLeft();
			return true;
		}
		else if ((character->getWidth() + character->getXPos()) == sCollider->w)
		{
			//checks if the character is touching the left side of the collider
			SDL_free(&sCollider);
			character->setLastMoveRight();
			return true;
		}
		else if (((character->getXPos() + character->getWidth()) > (sCollider->x)) && ((character->getXPos() + character->getWidth()) < (sCollider->x + sCollider->w)))
		{
			//checks if the character has over lapped the collider from the left
			character->setLastMoveRight();
			SDL_free(&sCollider);
			return true;
		}
		else if ((character->getXPos() < (sCollider->x + sCollider->w)) && (character->getXPos() > sCollider->x))
		{
			//checks if the character has overlapped the collider from the right
			character->setLastMoveLeft();
			SDL_free(&sCollider);
			return true;
		}
	}

	// if no collision detected, it resets the last move that touched
	character->resetLastTouch();
	return false;
}

bool Scene::checkSceneChange() const
{
	return _changeScene;
}

void Scene::checkInteractions()
{
	// check for all forms of collision at once
 	for (std::vector<Interaction>::iterator sInteraction = sInteractions.begin(); sInteraction != sInteractions.end(); ++sInteraction)
	{
		if ((character->getXPos() == (sInteraction->collider.x + sInteraction->collider.w)) || ((character->getWidth() + character->getXPos()) == sInteraction->collider.w) || (((character->getXPos() + character->getWidth()) > (sInteraction->collider.x)) && ((character->getXPos() + character->getWidth()) < (sInteraction->collider.x + sInteraction->collider.w))) || ((character->getXPos() < (sInteraction->collider.x + sInteraction->collider.w)) && (character->getXPos() > sInteraction->collider.x)))
		{
			if (sInteraction->getType() == CHANGESCENE)
			{
				_changeScene = true;
				_newScenePath = sInteraction->getPath();
			}
			if (sInteraction->getType() == CONVERSATION)
			{
				sInteraction->createDialogSprite();
  				sprites.push_back(sInteraction->getDialogSprite());
			}
		}
	}
}

void Scene::free()
{
	_newScenePath = "";
	_changeScene = false;
	sceneWidth = 0;
	sceneHeight = 0;

	character->free();
	character = nullptr;
	background.free();

	for (std::vector<Sprite*>::iterator vSprite = sprites.begin(); vSprite != sprites.end(); ++vSprite)
	{
		(*vSprite)->free();
		*vSprite = nullptr;
	}

	sprites.clear();

	colliders.clear();
	sInteractions.clear();

	sprites.erase(sprites.begin(), sprites.end());
	colliders.erase(colliders.begin(), colliders.end());
	sInteractions.erase(sInteractions.begin(), sInteractions.end());
}

void Scene::update(SDL_Event& e)
{
	bool collision = checkCollision();
	
	character->handleEvent(e);

	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_SPACE)
		{
			checkInteractions();
		}
		else
		{
			character->move(collision);
		}
	}
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

std::string Scene::changeScene()
{
	//dereferencing the pointer
	std::string nextScene = _newScenePath;
	free();
	return nextScene;
}
