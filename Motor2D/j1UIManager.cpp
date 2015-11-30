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

