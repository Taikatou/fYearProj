#include "Character.h"
#include "main.h"

Character::Character()
{
	lastMoveRight = false;
	lastMoveLeft = false;
	_cSprite = new Sprite;
	_cPosX = 0;
	_cPosY = 0;
	cVel = 0;
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
	lastMoveRight = false;
	lastMoveLeft = false;
	cVel = 0;
}

void Character::move(bool collision)
{
	//moves Character
	_cPosX += cVel;

	if ((_cPosX < 0) || (_cPosX + _cSprite->getWidth() > SCREEN_WIDTH) || collision)
	{
		_cPosX -= cVel;
	}

	if ((lastMoveRight && cVel < 0) || (lastMoveLeft && cVel >0))
	{
		_cPosX += cVel;
	}
}

void Character::render(int camX, int camY) const
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
			case SDLK_LEFT: cVel -= vLimit; _cSprite->sFlip(true); _cSprite->setSpriteSheetOffset(WALK); break;
			case SDLK_RIGHT: cVel += vLimit; _cSprite->sFlip(false); _cSprite->setSpriteSheetOffset(WALK);  break;
			case SDLK_a: _cSprite->setSpriteSheetOffset(PUNCH); break;
			default:;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0 )
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
			case SDLK_LEFT: cVel += vLimit; _cSprite->setSpriteSheetOffset(IDLE); break;
			case SDLK_RIGHT: cVel -= vLimit; _cSprite->setSpriteSheetOffset(IDLE); break;
			case SDLK_a: _cSprite->setSpriteSheetOffset(IDLE); break;
			default:;
		}
	}
}

void Character::setX(int x)
{
	_cPosX = x;
}

void Character::setY(int y)
{
	_cPosY = y;
}

void Character::setLastMoveLeft()
{
	lastMoveLeft = true;
}

void Character::setLastMoveRight()
{
	lastMoveRight = true;
}

void Character::resetLastTouch()
{
	lastMoveLeft = false;
	lastMoveRight = false;
}

void Character::setType(int type) const
{
	_cSprite->type = type;
}

void Character::animate() const
{
	_cSprite->animate();
}

void Character::setName(std::string name) const
{
	_cSprite->setName(name);
}

int Character::getXPos() const
{
	return _cPosX;
}

int Character::getYPos() const
{
	return _cPosY;
}

int Character::getWidth() const
{
	return _cSprite->getWidth();
}
