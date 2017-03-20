#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "main.h"
#include "Character.h"
#include "Sprite.h"
#include "Scene.h"


//functions
//starts SDL window, rendere and image processing
bool init();

//globals
int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;
SDL_Renderer* g_renderer = NULL;

//locals
SDL_Window* g_window = NULL;
Character ryu;
Scene scene;

//functions
bool init()
{
	bool success = true;
	//initialise SDL
	// SDL_Init() returns -1 if it fails
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		success = false;
	}
	else
	{
		//create the window
		g_window = SDL_CreateWindow("Wakinyan", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); 
		if (g_window == NULL)
		{
			success = false;
		}
		else
		{

			//create rendered
			g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (g_renderer == NULL)
			{
				success = false;
			}
			else
			{
				//initialise image loading
				int imgFlag = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlag) & imgFlag))
				{
					success = false;
				}

				imgFlag = IMG_INIT_JPG;
				if (!(IMG_Init(imgFlag) & imgFlag))
				{
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//here is where the first scene needs to be created
	return scene.loadFromFile("Assets/Other/ryuIdlingSpritesheet.png");
	return ryu.setSprite("Assets/Other/ryuIdlingSpritesheet.png", true);
}


void close()
{
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	scene.free();
	g_renderer = NULL;
	g_renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char* args[])
{
	if (!init())
	{
		printf("Failed to initialise SDL");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to laod media");
		}
		else
		{
			bool quit = false;
			SDL_Event e;

//			ryu.setCharacterPosition(40, 600);

			//application loop
			while (!quit)
			{
				//handle events in the queue
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//consider checking for colision with scene change trigger here

//					ryu.handleEvent(e);
					scene.update(e);
				}

//				ryu.move();

				//clear screen
				SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(g_renderer);

//				ryu.render();
				scene.render();

				//draws what is in the renderer to the window
				SDL_RenderPresent(g_renderer);
			}
		}
	}
	close();

	return 0;
}
