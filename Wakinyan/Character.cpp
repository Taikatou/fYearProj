#include "Character.h"
#include "main.h"


Character::Character()
{
	_cSprite = new Sprite;
	_cPosX = 0;
	_cPosY = 0;
	_cVel = 0;
}

Character::~Character()
{
	free();
}

void Character::free()
{
	_cSprite->free();
	_cPosX = 0;
	_cPosY = 0;
	_cVel = 0;
}

void Character::move()
{
	//moves Character
	_cPosX += _cVel;

	if ((_cPosX < 0) || (_cPosX + _cSprite->getWidth() > SCREEN_WIDTH))
	{
		_cPosX -= _cVel;
	}
}

void Character::render(int camX, int camY)
{
	_cSprite->render(_cPosX - camX, _cPosY - camY);
}

bool Character::setSprite(std::string path, bool animate) const
{
	//creates sprite object
	return _cSprite->loadFromFile(path, animate);
}

void Character::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//adjust velocity of charcter
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: _cVel -= vLimit; break;
		case SDLK_RIGHT: _cVel += vLimit; break;
		default:; 
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: _cVel += vLimit; break;
		case SDLK_RIGHT: _cVel -= vLimit; break;
		default:;
		}
	}
}

void Character::setCharacterPosition(int x, int y)
{
	_cPosX = x;
	_cPosY = y;
}

void Character::animate()
{
	_cSprite->animate();
}

int Character::getXPos()
{
	return _cPosX;
}

int Character::getYPos()
{
	return _cPosY;
}

int Character::getWidth()
{
	//not implemented
	return _cSprite->getWidth();
}

