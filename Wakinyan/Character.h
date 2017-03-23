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
	void render(int camX, int camY);
	bool setSprite(std::string path, bool animate = false) const;
	void handleEvent(SDL_Event &e);
	void setX(int x);
	void setY(int y);
	void setLastMoveLeft(bool move);
	void setLastMoveRight(bool move);
	void setType(int type);
	void animate();
	void setName(std::string name);
	int getXPos();
	int getYPos();
	int getWidth();
private:
	// Character position on x & y and their velocity
	bool lastMoveRight, lastMoveLeft;
	Sprite* _cSprite;
	int _cPosX, _cPosY;
};

