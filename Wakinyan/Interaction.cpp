#include "Interaction.h"


Interaction::Interaction()
{
	_textColour = { 0,0,0 };
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
	if (_dPosition < _dialog.size())
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(g_font, _dialog.at(_dPosition).c_str(), _textColour);
		if (textSurface != nullptr)
		{
			_dPosition++;
			SDL_Texture* temp = SDL_CreateTextureFromSurface(g_renderer, textSurface);
			_iDialog->setSpriteTexture(temp);
			_iDialog->setWidth(textSurface->w);
			_iDialog->setHeight(textSurface->h);
			_iDialog->setXPos(collider.x - (textSurface->w / 2));
			_iDialog->setYPos(collider.y - textSurface->h);
		}
	}
	else
	{
		_iDialog->setSpriteTexture(nullptr);
		_type = CHANGESCENE;
	}
 }

Sprite* Interaction::getDialogSprite() const
{
	return _iDialog;
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