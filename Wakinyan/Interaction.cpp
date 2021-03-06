#include "Interaction.h"


Interaction::Interaction()
{
	_blackTextColour = { 0,0,0 };
	_whiteTextColour = { 255, 255, 255 };
	_iDialog = new Sprite;
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

	_dialogPairs.clear();
	_dialogPairs.erase(_dialogPairs.begin(), _dialogPairs.end());
	
	_path = "";
	_type = 0;
}

void Interaction::setDialog(int _type, std::string _text)
{
	DialogPair temp;
	temp.type = _type;
	temp.text = _text;
	_dialogPairs.push_back(temp);
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
	if (_dialogPairs.size() > 0)
	{
		if (_dialogPairs.at(0).type == ONSCREEN_INTERACTION)
		{
#pragma region
			SDL_Surface* textSurface = TTF_RenderText_Solid(g_font, (_dialogPairs.at(0).text).c_str(), _whiteTextColour);
			SDL_Surface* textBackground = IMG_Load("Assets/Other/onScreenOverlay.png");

			SDL_Rect scaler = { 0, 0, sceneWidth, sceneHeight };
			if (textSurface->w > sceneWidth)
			{
				SDL_BlitScaled(textSurface, NULL, textSurface, &scaler);
			}

			textBackground->w = sceneWidth;
			textBackground->h = sceneHeight;

			SDL_Rect textHolder =
			{
				textBackground->w / 2 - textSurface->w / 2,
				textBackground->h / 3,
				textBackground->w,
				textBackground->h
			};

			if (textSurface != nullptr && textBackground != nullptr)
			{
				if (SDL_BlitSurface(textSurface, NULL, textBackground, &textHolder) == 0)
				{
					SDL_Texture* tempText = SDL_CreateTextureFromSurface(g_renderer, textBackground);
					_iDialog->setName(_dialogPairs.at(0).text);
					_iDialog->setSpriteTexture(tempText);
					_iDialog->setWidth(sceneWidth);
					_iDialog->setHeight(sceneHeight);
					_iDialog->setXPos(0);
					_iDialog->setYPos(0);
				}
			}
			SDL_FreeSurface(textSurface);
			SDL_FreeSurface(textBackground);
#pragma endregion //overlay text
		}
		else if (_dialogPairs.at(0).type == CONVERSATION)
		{
#pragma region
			SDL_Surface* textSurface = TTF_RenderText_Solid(g_font, _dialogPairs.at(0).text.c_str(), _whiteTextColour);
			SDL_Surface* textOutline = TTF_RenderText_Solid(outline_font, _dialogPairs.at(0).text.c_str(), _blackTextColour);

			// SDL_Surface* textSurface = TTF_RenderText_Solid(g_font, _dialogPairs.at(0).text.c_str(), _blackTextColour);
			if (textSurface != nullptr && textOutline != nullptr)
			{
				SDL_Rect outlineRect;
				outlineRect.w = textSurface->w;
				outlineRect.h = textSurface->h;
				outlineRect.x = 1;
				outlineRect.y = 1;
				// the two 1's here are to offset the actual text into the outline.
				// the thickness of the outline is 1 pixel as defined when the font was declared in main.cpp
				// this accounts for that and centres the white text over the black outline

				if (SDL_BlitSurface(textSurface, NULL, textOutline, &outlineRect) == 0)
				{
					SDL_Texture* tempText = SDL_CreateTextureFromSurface(g_renderer, textOutline);
					_iDialog->setName(_dialogPairs.at(0).text);
					_iDialog->setSpriteTexture(tempText);
					_iDialog->setWidth(textOutline->w);
					_iDialog->setHeight(textOutline->h);
					_iDialog->setXPos(collider.x - (collider.w / 2));
					_iDialog->setYPos(collider.y - textOutline->h);
				}
			}

			SDL_FreeSurface(textSurface);
			SDL_FreeSurface(textOutline);

			textSurface = nullptr;
			textOutline = nullptr;
#pragma endregion //conversation text
		}
		_dialogPairs.erase(_dialogPairs.begin());
		if (_dialogPairs.size() > 0)
		{
			_type = _dialogPairs.at(0).type;
		}
	}
	else
	{
		_iDialog->free();
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
	return _dialogPairs.size() > 0;
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

int Interaction::getDialogType() const
{
	return (_dialogPairs.size() > 0) ? _dialogPairs.at(0).type : _type;
}

int Interaction::getXPos() const
{
	return collider.x;
}

int Interaction::getYPos() const
{
	return collider.y;
}