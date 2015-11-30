#ifndef __UILABEL_H__
#define __UILABEL_H__

#include "UIEntity.h"
#include "p2SString.h"

struct _TTF_Font;
struct SDL_Texture;

class UILabel : public UIEntity
{
public:

	UILabel();

	UILabel(const char* txt,const int x, const int y);

	// Destructor
	virtual ~UILabel();

	bool Update(float dt);

	void Print(p2SString _text);

	// Called before quitting
	bool CleanUp();

private:

	p2SString	text;
public:
	SDL_Texture* texture;

};

#endif