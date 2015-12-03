#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1UIManager.h"
#include "UILabel.h"
#include "UIImage.h"
#include "UIButton.h"
#include "j1Window.h"


j1UIManager::j1UIManager() : j1Module()
{
	name.create("UIManager");
	debug = false;
}

// Destructor
j1UIManager::~j1UIManager()
{}

// Called before render is available
bool j1UIManager::Awake(pugi::xml_node& conf)
{
	LOG("Loading UIManager atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1UIManager::Start()
{
	bool ret = true;

	atlas = App->tex->Load(atlas_file_name.GetString());

	return ret;
}

// Update all UIManagers
bool j1UIManager::PreUpdate()
{
	return true;
}

// Called after all Updates
bool j1UIManager::PostUpdate()
{
	return true;
}

bool j1UIManager::Update(float dt)
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_UP)
		debug = !debug;

	GetMouseInput();

	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
	{
		SetNextFocus();
	}

	p2List_item<UIEntity*>* item = gui_elements.start;
	while (item && ret == true)
	{
		ret = item->data->Update(dt);
		item->data->GUIEvents();
		if (debug)
			item->data->Debug();
		item = item->next;
	}

	return ret;

	return ret;
}

// Called before quitting
bool j1UIManager::CleanUp()
{
	LOG("Freeing UIManager");
	bool ret = true;

	p2List_item<UIEntity*>* item = gui_elements.start;
	while (item && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->next;
	}

	return ret;
}

// const getter for atlas
const SDL_Texture* j1UIManager::GetAtlas() const
{
	return atlas;
}

// class UIManager ---------------------------------------------------

UILabel* j1UIManager::CreateLabel(const char* text,const int x,const int y, j1Module* listener)
{
	UILabel* label = new UILabel(text, x, y);
	label->listener = listener;
	gui_elements.add(label);

	return label;
}

UIImage* j1UIManager::CreateImage(const char* path, const int x, const int y, j1Module* listener)
{
	UIImage* img = new UIImage(path, x, y);
	img->listener = listener;
	gui_elements.add(img);

	return img;
}

UIImage* j1UIManager::CreateImage(SDL_Texture* tex, const int x, const int y, j1Module* listener)
{
	UIImage* img = new UIImage(tex, x, y);
	img->listener = listener;
	gui_elements.add(img);

	return img;
}

UIButton* j1UIManager::CreateButton(const char* _text, const int x, const int y, const char* path_idle, const char* path_pressed, const char* path_hover, j1Module* listener)
{
	UIButton* button = new UIButton(_text, x, y, path_idle, path_pressed, path_hover);
	button->listener = listener;
	gui_elements.add(button);

	return button;
}

UIEntity* j1UIManager::GetMouseHover() const
{
	p2Point<int> mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);

	p2List_item<UIEntity*>* item = gui_elements.end;

	while (item)
	{
		SDL_Rect rect = item->data->GetScreenRect();
		if (mouse.PointInRect(rect.x, rect.y, rect.w, rect.h) == true)
		{
			return item->data;
		}
		item = item->prev;
	}
	return NULL;
}


//Utilities -------------------------------------------------------------------------------------------------------------------------------------
void j1UIManager::GetMouseInput()
{
	if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
	{
		gui_pressed = GetMouseHover();

		if (gui_pressed->focusable)
		{
			if (focus)
				focus->isFocus = false;
			focus = gui_pressed;
			gui_pressed->isFocus = true;
		}
	}

	if (gui_pressed)
		gui_pressed->Drag();

	if (App->input->GetMouseButtonDown(1) == KEY_UP)
	{
		gui_pressed = NULL;
	}
}

void j1UIManager::SetNextFocus()
{
	p2List_item<UIEntity*>* item = gui_elements.start;

	unsigned int min_x, min_y;
	App->win->GetWindowSize(min_x, min_y);
	int win_x = min_x;
	
	int focus_x, focus_y;
	if (focus != NULL)
		focus->GetScreenPos(focus_x, focus_y);
	else
		focus_x = focus_y = 0;

	UIEntity* best_match = NULL;
	while (item)
	{
		if (item->data->focusable && item->data != focus)
		{
			SDL_Rect pos = item->data->GetScreenRect();
			if (pos.y < min_y && pos.y > focus_y)
			{
				best_match = item->data;
				min_y = pos.y;
				min_x = win_x;
			}
			else
			{
				if (pos.x < min_x && pos.y == focus_y && focus_x < pos.x)
				{
					best_match = item->data;
					min_x = pos.x;
				}
			}
		}
		item = item->next;
	}

	if (best_match != NULL)
	{
		if (focus != NULL)
			focus->isFocus = false;
		focus = best_match;
		focus->isFocus = true;
	}
}

