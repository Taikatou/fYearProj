#include "Character.h"
#include "main.h"


Character::Character()
{
	resetKeys();
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
	resetKeys();
	_cSprite->free();
	_cPosX = 0;
	_cPosY = 0;
	lastMoveRight = false;
	lastMoveLeft = false;
	_listen = false;
	cVel = 0;
}

void Character::update(bool collision)
{
	//move Character
	if (_keys.leftMove)
	{
		cVel = vLimit * -1;
		_cSprite->sFlip(true);
		_cSprite->setSpriteSheetOffset(WALK); _cPosX += cVel;

		if (_cPosX < 0 || collision)
		{
			_cPosX -= cVel;
		}

		if (lastMoveRight && cVel < 0 || lastMoveLeft && cVel >0)
		{
			_cPosX += cVel;
		}
		cVel = 0;
	}
	else if (_keys.rightMove)
	{
		cVel = vLimit;
		_cSprite->sFlip(false);
		_cSprite->setSpriteSheetOffset(WALK); _cPosX += cVel;

		if (_cPosX + _cSprite->getWidth() >= BACKGROUND_WIDTH || collision)
		{
			_cPosX -= cVel;
		}

		if (lastMoveRight && cVel < 0 || lastMoveLeft && cVel >0)
		{
			_cPosX += cVel;
		}
		cVel = 0;
	}
	else if (_keys.punch)
	{
		_cSprite->setSpriteSheetOffset(PUNCH);
	}
	else if (_keys.talk)
	{
		_cSprite->setSpriteSheetOffset(TALK);
	}
	else if (_keys.kick)
	{
		_cSprite->setSpriteSheetOffset(KICK);
	}
	else if (_keys.jump)
	{
		_cSprite->setSpriteSheetOffset(JUMP);
	}
	else if (_keys.turn)
	{
		_cSprite->setSpriteSheetOffset(TURN);
	}
	else
	{
		_cSprite->setSpriteSheetOffset(IDLE);
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

void Character::handleEvent(SDL_Event& e, bool collision)
{
//	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: _keys.leftMove = true; break;
		case SDLK_RIGHT: _keys.rightMove = true;  break;
		case SDLK_UP: _keys.jump = true; break;
		case SDLK_a: _keys.leftMove = true; break;
		case SDLK_d: _keys.rightMove = true; break;
		case SDLK_SPACE: _keys.talk = true; break;
			default:;
		}
		update(collision);
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_LEFT: _keys.leftMove = false; break;
			case SDLK_RIGHT: _keys.rightMove = false; break;
			case SDLK_UP: _keys.jump = false; break;
			case SDLK_a: _keys.leftMove = false; break;
			case SDLK_d: _keys.rightMove = false; break;
			default:;
		}
		_cSprite->setSpriteSheetOffset(IDLE);
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

void Character::resetKeys()
{
	_keys.leftMove = false;
	_keys.rightMove = false;
	_keys.punch = false;
	_keys.talk = false;
	_keys.kick = false;
	_keys.jump = false;
	_keys.turn = false;
}

void Character::talk()
{
	_keys.talk = true;
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