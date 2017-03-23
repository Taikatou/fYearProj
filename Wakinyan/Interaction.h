#pragma once
#include <string>
#include <SDL.h>

class Interaction
{
public:
	Interaction();
	~Interaction();
	void free();
	void setDialog(std::string dialog);
	void setPath(std::string path);
	void setType(int type);
	std::string getDialog() const;
	std::string getPath() const;
	int getType() const;
	SDL_Rect collider;
private:
	std::string _dialog;
	std::string _path;
	int _type;
};