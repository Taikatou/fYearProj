#pragma once
#include <SDL.h>
#include "Sprite.h"

class Character
{
public:
	const int vLimit = 5;
	int cVel;
	Character();
	~Character();
	void free();
	void move(bool collision);
	void render(int camX, int camY) const;
	bool setSprite(std::string path, bool animate = false) const;
	void handleEvent(SDL_Event &e);
	void setX(int x);
	void setY(int y);
	void setLastMoveLeft();
	void setLastMoveRight();
	void resetLastTouch();
	void setType(int type) const;
	void animate() const;
	void setName(std::string name) const;
	int getXPos() const;
	int getYPos() const;
	int getWidth() const;
private:
	// Character position on x & y and their velocity
	bool lastMoveRight, lastMoveLeft, _listen;
	Sprite* _cSprite;
	int _cPosX, _cPosY;
};