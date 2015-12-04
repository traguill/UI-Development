#include "UIInputBox.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1Textures.h"
#include "UILabel.h"

UIInputBox::UIInputBox() : UIEntity()
{}

UIInputBox::UIInputBox(const char* txt, const int x, const int y, const char* path) : UIEntity()
{

	type = INPUT_BOX;
	interactable = true;
	
	text = new UILabel(txt, 0, 0);
	background = new UIImage(path, 0 - DELAY_INPUT, 0 - DELAY_INPUT);

	text->parent = this;
	background->parent = this;

	rect.x = x;
	rect.y = y;
	rect.w = text->GetScreenRect().w;
	rect.h = text->GetScreenRect().h;

}



// Destructor
UIInputBox::~UIInputBox()
{}

// Called before render is available
bool UIInputBox::Update(float dt)
{
	bool ret = true;

	background->Update(dt);
	text->Update(dt);

	return ret;
}

bool UIInputBox::CleanUp()
{
	bool ret = true;

	text->CleanUp();
	background->CleanUp();

	delete text;
	delete background;

	return ret;
}

