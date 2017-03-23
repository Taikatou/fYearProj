#pragma once
#include <string>
#include <SDL.h>

class Interaction
{
public:
	Interaction();
	~Interaction();
	void free();
	void setPath(std::string path);
	void setType(int type);
	std::string getPath();
	int getType();
	SDL_Rect collider;
private:
	std::string _path;
	int _type;
};

