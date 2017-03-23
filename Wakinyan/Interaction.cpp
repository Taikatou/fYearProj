#include "Interaction.h"


Interaction::Interaction()
{
	_type = 0;
}


Interaction::~Interaction()
{
	free();
}

void Interaction::free()
{
	SDL_free(&collider);
	_type = 0;
	_path = "";
}

void Interaction::setDialog(std::string dialog)
{
	_dialog = dialog;
}

void Interaction::setPath(std::string path)
{
	_path = path;
}

void Interaction::setType(int type)
{
	_type = type;
}

std::string Interaction::getDialog() const
{
	return _dialog;
}

std::string Interaction::getPath() const
{
	return _path;
}

int Interaction::getType() const
{
	return _type;
}
