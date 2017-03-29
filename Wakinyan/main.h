#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
extern SDL_Renderer* g_renderer;
extern TTF_Font* g_font;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int BACKGROUND_WIDTH;
extern int sceneWidth;
extern int sceneHeight;

enum SpriteType
{
	CHARACTER,
	SPRITE,
	COLLISION_TRIGGER,
	BACKGROUND,
	CAMERA,
	INTERACTION_TRIGGER,
	SCENELINK
};
enum SpriteSheetOffset
{
	IDLE = 0,
	PUNCH = 4,
	WALK = 8,
	TALK = 12,
	KICK = 16,
	JUMP = 20,
	TURN = 24
};
enum InteractionType
{
	CHANGESCENE,
	AUTOCHANGESCENE,
	CONVERSATION,
	ENDEDCONVERSATION,
	ONSCREEN_INTERACTION
};