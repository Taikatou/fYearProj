#pragma once
#include <SDL_image.h>
#include <string>

const int WALKING_FRAMES = 4;
class Sprite
{
public:
	int type = 1;
	Sprite();
	~Sprite();
	//bool loadFromFile(std::string path);
	bool loadFromFile(std::string path, bool animiate = false);
	void free();
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void setXPos(int x);
	void setYPos(int y);
	int getHeight() const;
	int getWidth() const;
	int getXPos();
	int getYPos();
	void sFlip(bool flip);
	void setName(std::string name);
	std::string getName();
	void animate();
private:
	bool _animation;
	bool _flip;
	SDL_Rect _gSpriteClips[WALKING_FRAMES];
	SDL_Texture* _spriteTexture;
	SDL_RendererFlip _sFlip = SDL_FLIP_HORIZONTAL;
	std::string _name;
	int _sHeight, _sWidth, _xPos, _yPos;
};

