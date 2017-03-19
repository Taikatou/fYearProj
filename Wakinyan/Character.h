#pragma once
#include <SDL.h>
#include "Sprite.h"

class Character
{
public:
	const int vLimit = 10;
	Character();
	~Character();
	void free();
	void move();
	void render() const;
	bool setSprite(std::string path, bool animate = false) const;
	void handleEvent(SDL_Event &e);
	void setCharacterPosition(int x, int y);
	void animate();
private:
	// Character position on x & y and their velocity
	Sprite* _cSprite;
	int _cPosX, _cPosY, _cVel;
};

