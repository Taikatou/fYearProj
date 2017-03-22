#include "Sprite.h"
#include <string>
#include "main.h"

enum SpriteType
{
	SPRITE = 1,
	COLLISION_TRIGGER = 2,
	BACKGROUND = 3
};

int frameCount = 0;

Sprite::Sprite()
{
	_spriteTexture = nullptr;
	_name = "";
	_xPos = 0;
	_yPos = 0;
	_sHeight = 0;
	_sWidth = 0;
	_animation = false;
}
Sprite::~Sprite()
{
	free();
}

//possibly depricated
//bool Sprite::loadFromFile(std::string path)
//{
//	bool success = false;
//	_animation = false;
//	//the texture that will become the sprite
//	SDL_Texture* tempTexture = NULL;
//
//	//load the file into memory
//	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//	if (loadedSurface != NULL)
//	{
//		//consider how to handle wanted transparancy
//		//SDL_SetColorKey()
//
//		//converting the surface to a texture
//		tempTexture = SDL_CreateTextureFromSurface(g_renderer, loadedSurface);
//		if (tempTexture != NULL)
//		{
//			_sHeight = loadedSurface->h;
//			_sWidth = loadedSurface->w;
//			success = true;
//		}
//	}
//	
//	_spriteTexture = tempTexture;
//	return success;
//}

bool Sprite::loadFromFile(std::string path, bool animate)
{
	bool success = false;
	_animation = animate;
	
	//the texture that will become the sprite
	SDL_Texture* tempTexture = nullptr;

	//load the file into memory
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != nullptr)
	{
		//consider handling transperancy here
		//SDL_SetColorKey()

		//converting the surface to a texture
		tempTexture = SDL_CreateTextureFromSurface(g_renderer, loadedSurface);
		if (tempTexture != nullptr)
		{
			_sHeight = loadedSurface->h;
			_sWidth = loadedSurface->w;
			success = true;
		}
		if (animate)
		{
			//Set sprite clips
			_gSpriteClips[0].x = (_sWidth / WALKING_FRAMES )* 0;
			_gSpriteClips[0].y = 0;
			_gSpriteClips[0].w = (_sWidth / WALKING_FRAMES);
			_gSpriteClips[0].h = _sHeight;

			_gSpriteClips[1].x = (_sWidth / WALKING_FRAMES) * 1;
			_gSpriteClips[1].y = 0;
			_gSpriteClips[1].w = (_sWidth / WALKING_FRAMES);
			_gSpriteClips[1].h = _sHeight;

			_gSpriteClips[2].x = (_sWidth / WALKING_FRAMES) * 2;
			_gSpriteClips[2].y = 0;
			_gSpriteClips[2].w = (_sWidth / WALKING_FRAMES);
			_gSpriteClips[2].h = _sHeight;

			_gSpriteClips[3].x = (_sWidth / WALKING_FRAMES) * 3;
			_gSpriteClips[3].y = 0;
			_gSpriteClips[3].w = (_sWidth / WALKING_FRAMES);
			_gSpriteClips[3].h = _sHeight;
		}
	}

	_spriteTexture = tempTexture;
	return success;
}

void Sprite::free()
{
	SDL_DestroyTexture(_spriteTexture);
	_sHeight = 0;
	_sWidth = 0;
}


void Sprite::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) const
{
	SDL_Rect renderQuad = { x, y, _sWidth, _sHeight };

	if (_animation)
	{
		renderQuad.w = _gSpriteClips[frameCount/WALKING_FRAMES].w;
		renderQuad.h = _gSpriteClips[frameCount/WALKING_FRAMES].h;
	}
	else if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	if (!_animation)
	{
		SDL_RenderCopyEx(g_renderer, _spriteTexture, clip, &renderQuad, angle, center, flip);
	}
	else
	{
		if (_flip)
		{
			SDL_RenderCopyEx(g_renderer, _spriteTexture, &_gSpriteClips[frameCount / WALKING_FRAMES], &renderQuad, angle, center, _sFlip);
		}
		else
		{
			SDL_RenderCopyEx(g_renderer, _spriteTexture, &_gSpriteClips[frameCount / WALKING_FRAMES], &renderQuad, angle, center, flip);
		}
		frameCount++;

		if (frameCount / WALKING_FRAMES >= WALKING_FRAMES)
		{
			frameCount = 0;
		}
	}
}

void Sprite::setXPos(int x)
{
	_xPos = x;
}

void Sprite::setYPos(int y)
{
	_yPos = y;
}

int Sprite::getHeight() const
{
	return _sHeight;
}

int Sprite::getWidth() const
{
	return _animation ? _sWidth / WALKING_FRAMES :_sWidth;
}

int Sprite::getXPos()
{
	return _xPos;
}

int Sprite::getYPos()
{
	return _yPos;
}

void Sprite::sFlip(bool flip)
{
	_flip = flip;
}

void Sprite::setName(std::string name)
{
	_name = name;
}

std::string Sprite::getName()
{
	return _name;
}

void Sprite::animate()
{
}
