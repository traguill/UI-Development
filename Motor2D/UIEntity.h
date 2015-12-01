#ifndef __UIENTITY_H__
#define __UIENTITY_H__

#include "p2Point.h"
#include "SDL/include/SDL.h"
#include "p2List.h"

class j1Module;

enum GUI_TYPE
{
	LABEL,
	IMAGE,
	BUTTON
};

enum GUI_EVENTS
{
	NONE,
	MOUSE_ENTER,
	MOUSE_EXIT,
	MOUSE_BUTTON_RIGHT_DOWN,
	MOUSE_BUTTON_RIGHT_UP
};

class UIEntity
{
public:

	UIEntity();

	// Destructor
	virtual ~UIEntity();

	virtual bool Update(float dt);
	// Called before quitting

	virtual bool CleanUp();

	void GUIEvents();

	void GetScreenPos(int &x, int &y)const;
	void GetLocalPos(int &x, int &y)const;
	SDL_Rect GetScreenRect()const;
	SDL_Rect GetLocalRect()const;
	void SetLocalPos(int x, int y);
	
	void SetParent(UIEntity* parent);

	void Debug();

	void Drag();

public:

	GUI_TYPE			type;
	GUI_EVENTS			gui_event;
	bool				isVisible;
	j1Module*			listener;
	UIEntity*			parent = NULL;
	bool				interactable = false;
	bool				focusable = true;
	bool				isFocus = false;

protected:
	SDL_Rect rect; //Local


};

#endif