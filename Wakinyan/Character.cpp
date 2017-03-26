#include "Character.h"
#include "main.h"

Character::Character()
{
	lastMoveRight = false;
	lastMoveLeft = false;
	_listen = false;
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
	_listen = false;
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
			case SDLK_UP: _cSprite->setSpriteSheetOffset(JUMP); break;
			case SDLK_a: _cSprite->setSpriteSheetOffset(PUNCH); break;
			default:;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0 && _listen)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
			case SDLK_LEFT: cVel += vLimit; _cSprite->setSpriteSheetOffset(IDLE); break;
			case SDLK_RIGHT: cVel -= vLimit; _cSprite->setSpriteSheetOffset(IDLE); break;
			case SDLK_UP: _cSprite->setSpriteSheetOffset(IDLE); break;
			case SDLK_a: _cSprite->setSpriteSheetOffset(IDLE); break;
			default:;
		}
	}
	// hacked together way of making sure that the engine is only affecting velocity
	// after a scene load AFTER the first key has been released
	// when scenes were being auto changed, the key was still pressed down
	// thus the first event to handle was a key up event
	// When the key up was an directional arrow, after a scene load that key would no longer work and
	// the other direction would affect the velocity twice as much
	// the logic dictates that when a key up even occurs that the velocity limit for that direction is deducted from the active velocity
	// if the right key was the last key up even that would have velocity constantly equal to -vLimit instead of zero
	// so when the left arrow is pressed, velocity isn't set to -vLimit but is set to (-vLimit - vLimit)
	else if (e.type == SDL_KEYUP && e.key.repeat == 0 && !_listen)
	{
		_cSprite->setSpriteSheetOffset(IDLE);
		cVel = 0;
		_listen = true;
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
