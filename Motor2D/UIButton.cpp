#include "UIButton.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "UILabel.h"

UIButton::UIButton() : UIEntity()
{
	type = BUTTON;
	state = IDLE;
}

UIButton::UIButton(const char* _text, const int x, const int y, const char* path_idle, const char* path_pressed, const char* path_hover) : UIEntity()
{
	type = IMAGE;
	state = IDLE;
	text.Print(_text);

	int px, py;
	px = py = 0;
	if (parent != NULL)
		parent->GetScreenPos(px, py);

	rect.x = px + x;
	rect.y = py + y;

	idle = App->tex->Load(path_idle);

	if (path_pressed)
		pressed = App->tex->Load(path_pressed);
	if (path_hover)
		hover = App->tex->Load(path_hover);
	text.parent = this;
	SDL_QueryTexture(idle, NULL, NULL, &rect.w, &rect.h);

}


// Destructor
UIButton::~UIButton()
{}

// Called before render is available
bool UIButton::Update(float dt)
{
	bool ret = true;

	GetState();

	iPoint cam_pos(App->render->camera.x, App->render->camera.y);

	int x, y;
	GetScreenPos(x, y);
	
	if (state == IDLE)
		App->render->Blit(idle, x - cam_pos.x, y - cam_pos.y);
	if (state == PRESSED)
		App->render->Blit(pressed, x - cam_pos.x, y - cam_pos.y);
	if (state == HOVER)
		App->render->Blit(hover, x - cam_pos.x, y - cam_pos.y);

	
	x = rect.x + (rect.w / 2 - text.rect.w / 2);
	y = rect.y + (rect.h / 2 - text.rect.h / 2);
	App->render->Blit(text.texture, x - cam_pos.x, y - cam_pos.y);


	return ret;
}

bool UIButton::CleanUp()
{
	bool ret = true;

	if (idle)
		App->tex->UnLoad(idle);
	if (pressed)
		App->tex->UnLoad(pressed);
	if (hover)
		App->tex->UnLoad(hover);


	return ret;
}

void UIButton::GetState()
{
	if (gui_event == MOUSE_ENTER)
		state = HOVER;
	if (gui_event == MOUSE_EXIT)
		state = IDLE;
	if (gui_event == MOUSE_BUTTON_RIGHT_DOWN)
		state = PRESSED;
}
