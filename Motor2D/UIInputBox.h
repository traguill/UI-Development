#ifndef __UIINPUTBOX_H__
#define __UIINPUTBOX_H__

#include "UIEntity.h"
#include "UILabel.h"
#include "UIImage.h"

#define DELAY_INPUT 5

class UIInputBox : public UIEntity
{
public:

	UIInputBox();

	UIInputBox(const char* txt, const int x, const int y, const char* path = NULL);

	// Destructor
	virtual ~UIInputBox();

	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

private:

	UILabel* text;
	UIImage* background;

};

#endif