#pragma once
#include <SDL_image.h>
#include <string>

const int WALKING_FRAMES = 4;
class Sprite
{
public:
	Sprite();
	~Sprite();
	//bool loadFromFile(std::string path);
	bool loadFromFile(std::string path, bool animiate = false);
	void free();
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	int getHeight() const;
	int getWidth() const;
	int getXPos();
	int getYPos();
	void setName(std::string name);
	std::string getName();
	void animate();
private:
	bool _animation;
	SDL_Rect _gSpriteClips[WALKING_FRAMES];
	SDL_Texture* _spriteTexture;
	std::string _name;
	int _sHeight, _sWidth, _xPos, _yPos;
};

