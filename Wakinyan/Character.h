#pragma once
#include <SDL.h>
#include "Sprite.h"

struct KEYPRESS
{
	bool leftMove = false;
	bool rightMove = false;
	bool punch = false;
	bool talk = false;
	bool kick = false;
	bool jump = false;
	bool turn = false;
};

class Character
{
public:
	const int vLimit = 5;
	int cVel;
	Character();
	~Character();
	void free();
	void update(bool collision);
	void render(int camX, int camY) const;
	void handleEvent(SDL_Event& e, bool collision);
	void setX(int x);
	void setY(int y);
	void setLastMoveLeft();
	void setLastMoveRight();
	void resetLastTouch();
	void setType(int type) const;
	void animate() const;
	void setName(std::string name) const;
	void resetKeys();
	void talk(bool talk);
	bool setSprite(std::string path, bool animate = false) const;
	int getXPos() const;
	int getYPos() const;
	int getWidth() const;
private:
	// Character position on x & y and their velocity
	KEYPRESS _keys;
	Sprite* _cSprite;
	bool lastMoveRight, lastMoveLeft, _listen;
	int _cPosX, _cPosY;
};
