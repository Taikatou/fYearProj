#include "Interaction.h"


Interaction::Interaction()
{
	_blackTextColour = { 0,0,0 };
	_whiteTextColour = { 255, 255, 255, 255 };
	_iDialog = new Sprite;
	_dPosition = 0;
	_type = 0;
}


Interaction::~Interaction()
{
	free();
}

void Interaction::free()
{
	_iDialog->free();
	_iDialog = nullptr;

	_dialog.clear();
	_dialog.erase(_dialog.begin(), _dialog.end());
	
	_path = "";
	_type = 0;
	_dPosition = 0;
}

void Interaction::setDialog(std::string dialog)
{
	_dialog.push_back(dialog);
}

void Interaction::setPath(std::string path)
{
	_path = path;
}

void Interaction::setType(int type)
{
	_type = type;
}

void Interaction::createDialogSprite()
{
	if (_dialog.size() > 0 && (_type == CONVERSATION || _type == ONSCREEN_INTERACTION))
	{
		if (_type == ONSCREEN_INTERACTION)
		{
			SDL_Surface* textSurface = TTF_RenderText_Solid(g_font, _dialog.at(0).c_str(), _whiteTextColour);
			SDL_Surface* textBackground = IMG_Load("Assets/Other/onScreenOverlay.png");
			SDL_Rect textHolder =
			{
				textBackground->w / 2 - textSurface->w / 2,
				textBackground->h / 2 - textSurface->h / 2,
				textSurface->w,
				textSurface->h
			};

			if (textSurface != nullptr && textBackground != nullptr)
			{
				if (SDL_BlitSurface(textSurface, &textHolder, textBackground, &textHolder) == 0)
				{
					SDL_Texture* tempText = SDL_CreateTextureFromSurface(g_renderer, textBackground);
					_iDialog->setName(_dialog.at(0));
					_iDialog->setSpriteTexture(tempText);
					_iDialog->setWidth(textBackground->w);
					_iDialog->setHeight(textBackground->h);
					_iDialog->setXPos(sceneWidth / 2 - textBackground->w / 2);
					_iDialog->setYPos(sceneHeight / 2 - textBackground->h / 2);
				}
			}
		}
		else {
			SDL_Surface* textSurface = TTF_RenderText_Solid(g_font, _dialog.at(0).c_str(), _blackTextColour);
			if (textSurface != nullptr)
			{
				SDL_Texture* tempText = SDL_CreateTextureFromSurface(g_renderer, textSurface);
				_iDialog->setName(_dialog.at(0));
				_iDialog->setSpriteTexture(tempText);
				_iDialog->setWidth(textSurface->w);
				_iDialog->setHeight(textSurface->h);
				_iDialog->setXPos(collider.x - (textSurface->w / 2));
				_iDialog->setYPos(collider.y - textSurface->h);
			}
		}
		_dialog.erase(_dialog.begin());
	}
	else
	{
		_iDialog->setSpriteTexture(nullptr);
		resetType();
	}
 }

void Interaction::resetType()
{
	if (_path != "null")
	{
		_type = CHANGESCENE;
	}
	else
	{
		_type = ENDEDCONVERSATION;
	}
}


Sprite* Interaction::getInteractionSprite() const
{
	return _iDialog;
}

bool Interaction::hasRemainingDialong() const
{
	return _dialog.size() > 0;
}

std::string Interaction::getDialog() const
{
	return _dialog.at(0);
}

std::string Interaction::getPath() const
{
	return _path;
}

int Interaction::getType() const
{
	return _type;
}

int Interaction::getXPos() const
{
	return collider.x;
}

int Interaction::getYPos() const
{
	return collider.y;
}