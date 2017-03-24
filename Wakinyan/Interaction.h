#pragma once
#include <string>
#include <SDL.h>
#include "Sprite.h"
#include <vector>

class Interaction
{
public:
	Interaction();
	~Interaction();
	void free();
	void setDialog(std::string dialog);
	void setPath(std::string path);
	void setType(int type);
	void createDialogSprite();
	Sprite* getDialogSprite() const;
	std::string getDialog() const;
	std::string getPath() const;
	int getType() const;
	int getXPos() const;
	int getYPos() const;
	SDL_Rect collider;
private:
	SDL_Color _textColour;
	Sprite* _iDialog;
	std::vector<std::string> _dialog;
	std::string _path;
	int _type, _dPosition;
};
