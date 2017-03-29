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
					BACKGROUND_WIDTH = background.getWidth();
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
 					while (strcmp(temp->Value(), "interaction") == 0)
					{
						auto tempIterator = temp->FirstChild();
						int interactionType = std::stoi(tempIterator->FirstChild()->Value());
						tempInteraction.setType(interactionType);

						if (interactionType == CONVERSATION || interactionType == ONSCREEN_INTERACTION)
						{
							tempIterator = tempIterator->NextSiblingElement();
							if (strcmp(tempIterator->Value(), "dialog") == 0)
							{
								while (strcmp(tempIterator->Value(), "null") != 0)
								{
									tempInteraction.setDialog(interactionType, tempIterator->FirstChild()->Value());
									tempIterator = tempIterator->NextSiblingElement();
								}
							}
						}
						temp = temp->NextSiblingElement();
					}
					
					_sInteractions.push_back(tempInteraction);
#pragma endregion //load interactions
				}
				else if (type == SCENELINK)
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

						int interactionType = std::stoi(temp->FirstChild()->FirstChild()->Value());
						tempInteraction.setType(interactionType);
					}

					sAutoSceneChange.push_back(tempInteraction);
#pragma endregion //load the auto scene change interactions
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
	// refactor this to use the checkThisCollision() function
	// get the result, if it's true and the x of the character is less than the x of collider, setLastMoveRight true
	// get the result, if it's true and the x of the character is greater than the x the collder, setLastMoveLeft true
	for (std::vector<SDL_Rect>::iterator sCollider = colliders.begin(); sCollider != colliders.end(); ++sCollider)
	{
		if (character->getXPos() > sCollider->x && character->getXPos() + character->getWidth() < sCollider->x + sCollider->w)
		{
			return true;
		}
		if (character->getXPos() == sCollider->x + sCollider->w)
		{
			//checks if the character is touching the right side of the collider
			character->setLastMoveLeft();
			return true;
		}
		if (character->getWidth() + character->getXPos() == sCollider->x)
		{
			//checks if the character is touching the left side of the collider
			character->setLastMoveRight();
			return true;
		}
		if (character->getXPos() < sCollider->x + sCollider->w && character->getXPos() > sCollider->x)
		{
			//checks if the character has overlapped the collider from the right
			character->setLastMoveLeft();
			return true;
		}
		if (character->getXPos() + character->getWidth() > sCollider->x && character->getXPos() + character->getWidth() < sCollider->x + sCollider->w)
		{
			//checks if the character has over lapped the collider from the left
			character->setLastMoveRight();
			return true;
		}
	}

	// if no collision detected, it resets the last move that touched
	character->resetLastTouch();
	return false;
}

bool Scene::checkThisCollision(SDL_Rect collider) const
{
	// checks all forms of collision
	// touch on the left or right of the collider
	// encroach on the left or right of the collider
	if ((character->getXPos() == collider.x + collider.w)
		
		||
		
		(character->getWidth() + character->getXPos() == collider.x)
		
		||
		
		(character->getXPos() + character->getWidth() > collider.x && character->getXPos() + character->getWidth() < collider.x + collider.w)
		
		||
		
		(character->getXPos() < collider.x + collider.w && character->getXPos() > collider.x)
		
		||
		
		(character->getXPos() > collider.x && character->getXPos() + character->getWidth() < collider.x + collider.w))
	{
		return true;
	}
	return false;
}

bool Scene::checkSceneChange()
{
	if (_changeScene)
	{
		return _changeScene;
	}
	else
	{
		for (std::vector<Interaction>::iterator sAutochange = sAutoSceneChange.begin(); sAutochange != sAutoSceneChange.end(); ++sAutochange)
		{
			if (checkThisCollision(sAutochange->collider))
			{
				if (sAutochange->getType() == AUTOCHANGESCENE)
				{
					_changeScene = true;
					_newScenePath = sAutochange->getPath();
				}
			}
		}

		return _changeScene;
	}
}

void Scene::checkInteractions()
{
 	for (std::vector<Interaction>::iterator sInteraction = _sInteractions.begin(); sInteraction != _sInteractions.end(); ++sInteraction)
	{
		if (checkThisCollision(sInteraction->collider))
		{
			if (sInteraction->getType() == CHANGESCENE)
			{
				_changeScene = true;
				_newScenePath = sInteraction->getPath();
			}
			else if (sInteraction->getDialogType() == CONVERSATION)
			{
					sInteraction->createDialogSprite();
  					npcDialog.push_back(sInteraction->getInteractionSprite());
			}
			else if (sInteraction->getDialogType() == ONSCREEN_INTERACTION)
			{
				if (sInteraction->hasRemainingDialong())
				{
					screenOverlayText.erase(screenOverlayText.begin(), screenOverlayText.end());
					sInteraction->createDialogSprite();
					screenOverlayText.push_back(sInteraction->getInteractionSprite());
				}
				else
				{
					sInteraction->resetType();
				}
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
	camera.x = 0;
	camera.y = 0;
	camera.w = 0;
	camera.h = 0;

	for (std::vector<Sprite*>::iterator vSprite = sprites.begin(); vSprite != sprites.end(); ++vSprite)
	{
		(*vSprite)->free();
		*vSprite = nullptr;
	}

	for (std::vector<Sprite*>::iterator sDialog = npcDialog.begin(); sDialog != npcDialog.end(); ++sDialog)
	{
		(*sDialog)->free();
		*sDialog = nullptr;
	}

	for (std::vector<Sprite*>::iterator vOverlay = screenOverlayText.begin(); vOverlay != screenOverlayText.end(); ++vOverlay)
	{
		(*vOverlay)->free();
		*vOverlay = nullptr;
	}

	sprites.clear();
	npcDialog.clear();
	screenOverlayText.clear();
	colliders.clear();
	_sInteractions.clear();
	sAutoSceneChange.clear();

	npcDialog.erase(npcDialog.begin(), npcDialog.end());
	screenOverlayText.erase(screenOverlayText.begin(), screenOverlayText.end());
	sprites.erase(sprites.begin(), sprites.end());
	colliders.erase(colliders.begin(), colliders.end());
	_sInteractions.erase(_sInteractions.begin(), _sInteractions.end());
	sAutoSceneChange.erase(sAutoSceneChange.begin(), sAutoSceneChange.end());
}

void Scene::update(SDL_Event& e)
{
	if (checkSceneChange())
	{
		std::string path = changeScene();
		loadFromFile(path.c_str());
		_changeScene = false;
	}
	else if (screenOverlayText.size() > 0)
	{
		if (e.type == SDL_MOUSEBUTTONUP || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && e.key.repeat == 0))
		{
			character->talk();
			screenOverlayText.erase(screenOverlayText.begin(), screenOverlayText.end());
			checkInteractions();
		}
	}
	else
	{
		bool collision = checkCollision();
			
		character->handleEvent(e, collision);
			
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
		{
  			checkInteractions();
		}
	}
}

void Scene::render()
{
	//centering camera over sprite
	camera.x = (character->getXPos() + character->getWidth() * 2) - sceneWidth / 2;
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
	if (camera.x > BACKGROUND_WIDTH - camera.w)
	{
		camera.x = BACKGROUND_WIDTH - camera.w;
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
	
//	for (std::vector<Sprite*>::iterator sDialog = npcDialog.begin(); sDialog != npcDialog.end(); ++sDialog)
//	{
//		(*sDialog)->render((*sDialog)->getXPos() - camera.x, (*sDialog)->getYPos() - camera.y);
//	}

	character->render(camera.x, camera.y);

	if (screenOverlayText.size() > 0)
	{
		for (std::vector<Sprite*>::iterator vOverlay = screenOverlayText.begin(); vOverlay != screenOverlayText.end(); ++vOverlay)
		{
			(*vOverlay)->render((*vOverlay)->getXPos(), (*vOverlay)->getXPos());
		}
	}
	else if (npcDialog.size() > 0)
	{
		//npc dialog is getting populated with the sprite that is being pushed onto screenOverlayText WITHOUT my code explicitly pushing
		//it is pushed on AND it overrides all the previous values in the vector
		//this work around will render the first sprite in the vector
		//I see this as safe based off the fact that ALL sprites in the vector at any given time are identical
		//a smarted but longer to implement fix would be to just have 2 sprite pointers in the scene and if they aren't nullptr then render
		// and if they render, set them to nullptr immedietly after rendering
		Sprite* sText = npcDialog.at(0);
		sText->render(sText->getXPos() - camera.x, sText->getYPos() - camera.y);
	}
}

std::string Scene::changeScene()
{
	//dereferencing the pointer
	std::string nextScene = _newScenePath;
	free();
	return nextScene;
}
