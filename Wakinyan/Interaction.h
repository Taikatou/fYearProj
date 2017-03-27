#pragma once
#include <string>
#include <SDL.h>
#include <vector>
#include "Sprite.h"

struct DialogPair
{
	int type;
	std::string text;
};

class Interaction
{
public:
	Interaction();
	~Interaction();
	void free();
	void setDialog(int _type,std::string _dialog);
	void setDialog(std::string dialog);
	void setPath(std::string path);
	void setType(int type);
	void createDialogSprite();
	void resetType();
	Sprite* getInteractionSprite() const;
	bool hasRemainingDialong() const;
	std::string getDialog() const;
	std::string getPath() const;
	int getType() const;
	int getDialogType() const;
	int getXPos() const;
	int getYPos() const;
	SDL_Rect collider;
private:
	Sprite* _iDialog;
	std::vector<DialogPair> _dialogPairs;
	std::vector<std::string> _dialog;
	std::string _path;
	int _type;
	SDL_Color _blackTextColour, _whiteTextColour;
};
