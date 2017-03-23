#include "Sprite.h"
#include <string>
#include "main.h"

int frameCount = 0;
int spriteOffsets[] = {IDLE, PUNCH, WALK, TALK, KICK, JUMP, BACK};

Sprite::Sprite()
{
	_spriteTexture = nullptr;
	_name = "";
	_xPos = 0;
	_yPos = 0;
	_sHeight = 0;
	_sWidth = 0;
	_spriteSheetOffset = 0;
	_flip = false;
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
	
	//the texture that will become the sprite
	SDL_Texture* tempTexture = nullptr;

	//load the file into memory
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != nullptr)
	{
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
			_sWidth = _sWidth / WALKING_FRAMES;
			_sHeight = _sHeight / SPRITE_SHEET_COUNT;

			//Set sprite clips

			for (int i = 0; i < 7; i++)
			{
				_gSpriteClips[0 + spriteOffsets[i]].x = _sWidth * 0;
				_gSpriteClips[0 + spriteOffsets[i]].y = _sHeight * i;
				_gSpriteClips[0 + spriteOffsets[i]].w = _sWidth;
				_gSpriteClips[0 + spriteOffsets[i]].h = _sHeight;

				_gSpriteClips[1 + spriteOffsets[i]].x = _sWidth * 1;
				_gSpriteClips[1 + spriteOffsets[i]].y = _sHeight * i;
				_gSpriteClips[1 + spriteOffsets[i]].w = _sWidth;
				_gSpriteClips[1 + spriteOffsets[i]].h = _sHeight;

				_gSpriteClips[2 + spriteOffsets[i]].x = _sWidth * 2;
				_gSpriteClips[2 + spriteOffsets[i]].y = _sHeight * i;
				_gSpriteClips[2 + spriteOffsets[i]].w = _sWidth;
				_gSpriteClips[2 + spriteOffsets[i]].h = _sHeight;

				_gSpriteClips[3 + spriteOffsets[i]].x = _sWidth * 3;
				_gSpriteClips[3 + spriteOffsets[i]].y = _sHeight * i;
				_gSpriteClips[3 + spriteOffsets[i]].w = _sWidth;
				_gSpriteClips[3 + spriteOffsets[i]].h = _sHeight;
			}
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

	if (type == 0)
	{
		renderQuad.w = _gSpriteClips[frameCount/WALKING_FRAMES].w;
		renderQuad.h = _gSpriteClips[frameCount/WALKING_FRAMES].h;
	}
	else if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	if (type > 0)
	{
		SDL_RenderCopyEx(g_renderer, _spriteTexture, clip, &renderQuad, angle, center, flip);
	}
	else
	{
		if (_flip)
		{
			SDL_RenderCopyEx(g_renderer, _spriteTexture, &_gSpriteClips[(frameCount / WALKING_FRAMES) + _spriteSheetOffset], &renderQuad, angle, center, _sFlip);
		}
		else
		{
			SDL_RenderCopyEx(g_renderer, _spriteTexture, &_gSpriteClips[(frameCount / WALKING_FRAMES) + _spriteSheetOffset], &renderQuad, angle, center, flip);
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
	return (type == 0) ? _sWidth / WALKING_FRAMES :_sWidth;
}

int Sprite::getXPos() const
{
	return _xPos;
}

int Sprite::getYPos() const
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

void Sprite::setSpriteSheetOffset(int offset)
{
	_spriteSheetOffset = offset;
}

std::string Sprite::getName() const
{
	return _name;
}

void Sprite::animate() const
{
}
