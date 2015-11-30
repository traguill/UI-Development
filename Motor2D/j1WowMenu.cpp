#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1WowMenu.h"
#include "j1UIManager.h"
#include "UILabel.h"
#include "UIImage.h"
#include "UIButton.h"

j1WowMenu::j1WowMenu() : j1Module()
{
	name.create("scene");
}

// Destructor
j1WowMenu::~j1WowMenu()
{}

// Called before render is available
bool j1WowMenu::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1WowMenu::Start()
{
	
	App->ui->CreateImage("wow/background.jpg", 0, 0);
	window = App->ui->CreateImage("wow/window.png", 500, 600);
	login = App->ui->CreateButton("Login", 20, 10, "wow/button.png", "wow/button_pressed.png", "wow/button_hover.png");
	login->SetParent(window);
	App->ui->CreateButton("Manage Account", 20, 800, "wow/button.png", "wow/button_pressed.png", "wow/button_hover.png");
	App->ui->CreateButton("Community Site", 20, 825, "wow/button.png", "wow/button_pressed.png", "wow/button_hover.png");
	App->ui->CreateButton("Cinematics", 1110, 775, "wow/button.png", "wow/button_pressed.png", "wow/button_hover.png");
	App->ui->CreateButton("Credits", 1110, 800, "wow/button.png", "wow/button_pressed.png", "wow/button_hover.png");
	App->ui->CreateButton("Terms of Use", 1110, 825, "wow/button.png", "wow/button_pressed.png", "wow/button_hover.png");


	return true;
}

// Called each loop iteration
bool j1WowMenu::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool j1WowMenu::Update(float dt)
{
	// Gui ---

	// -------
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += floor(200.0f * dt);

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= floor(200.0f * dt);

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += floor(200.0f * dt);

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= floor(200.0f * dt);

	return true;
}

// Called each loop iteration
bool j1WowMenu::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1WowMenu::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1WowMenu::OnGUI(UIEntity* gui, GUI_EVENTS event)
{
	if (gui->type == LABEL)
	{
		UILabel* label = (UILabel*)gui;
		if ( label == label_test)
		{
			if (event == MOUSE_ENTER)
				label->Print("Enter");

			if (event == MOUSE_EXIT)
				label->Print("Exit");

			if (event == MOUSE_BUTTON_RIGHT_DOWN)
				label->Print("ClickRight");
			if (event == MOUSE_BUTTON_RIGHT_UP)
				label->Print("ClickRight up");
		}
	}
}
