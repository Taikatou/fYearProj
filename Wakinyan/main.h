#pragma once
#include <SDL.h>
extern SDL_Renderer* g_renderer;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
enum SpriteType
{
	CHARACTER = 0,
	SPRITE = 1,
	COLLISION_TRIGGER = 2,
	BACKGROUND = 3,
	CAMERA = 4
};
enum SpriteSheetOffset
{
	IDLE = 0,
	PUNCH = 4,
	WALK = 8,
	TALK = 12,
	KICK = 16,
	JUMP = 20,
	BACK = 24
};