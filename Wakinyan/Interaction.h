#pragma once
#include <string>
#include <SDL.h>
#include <vector>
#include "Sprite.h"

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
	Sprite* getInteractionSprite() const;
	std::string getDialog() const;
	std::string getPath() const;
	int getType() const;
	int getXPos() const;
	int getYPos() const;
	SDL_Rect collider;
private:
	Sprite* _iDialog;
	std::vector<std::string> _dialog;
	std::string _path;
	int _type, _dPosition;
	SDL_Color _blackTextColour, _whiteTextColour;
};
