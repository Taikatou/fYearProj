#pragma once
#include <SDL_image.h>
#include <string>
#include "main.h"

const int WALKING_FRAMES = 4;
const int SPRITE_SHEET_COUNT = 7;
class Sprite
{
public:
	int type = 1;
	Sprite();
	~Sprite();
	void free();
	void animate() const;
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void setXPos(int x);
	void setYPos(int y);
	void setWidth(int w);
	void setHeight(int h);
	void sFlip(bool flip);
	void setName(std::string name);
	void setSpriteSheetOffset(int offset);
	void setSpriteTexture(SDL_Texture* texture);
	bool loadFromFile(std::string path, bool animiate = false);
	std::string getName() const;
	int getHeight() const;
	int getWidth() const;
	int getXPos() const;
	int getYPos() const;
private:
	bool _flip;
	std::string _name;
	int _sHeight, _sWidth, _xPos, _yPos, _spriteSheetOffset;
	SDL_Rect _gSpriteClips[WALKING_FRAMES * SPRITE_SHEET_COUNT];
	SDL_Texture* _spriteTexture;
	SDL_RendererFlip _sFlip = SDL_FLIP_HORIZONTAL;
};

