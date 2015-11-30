#include "UIEntity.h"
#include "j1App.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1Module.h"
#include "j1Render.h"

UIEntity::UIEntity()
{}

// Destructor
UIEntity::~UIEntity()
{}

// Called before render is available
bool UIEntity::Update(float dt)
{
	return true;
}

bool UIEntity::CleanUp()
{
	return true;
}

void UIEntity::GUIEvents()
{
	SDL_Point mouse_position;
	App->input->GetMousePosition(mouse_position.x, mouse_position.y);

	if (gui_event != MOUSE_ENTER && gui_event != MOUSE_BUTTON_RIGHT_DOWN)
	{
		if (mouse_position.x > rect.x && mouse_position.y > rect.y && mouse_position.x < rect.x + rect.w &&  mouse_position.y < rect.y + rect.h)
		{
			
			gui_event = MOUSE_ENTER;
			if (listener != NULL)
				listener->OnGUI(this, gui_event);
		}
	}
	else
	{
		if (gui_event == MOUSE_ENTER || gui_event == MOUSE_BUTTON_RIGHT_DOWN)
		{
			if (mouse_position.x > rect.x && mouse_position.y > rect.y && mouse_position.x < rect.x + rect.w &&  mouse_position.y < rect.y + rect.h)
			{
				if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
				{
					gui_event = MOUSE_BUTTON_RIGHT_DOWN;
					if (listener != NULL)
						listener->OnGUI(this, gui_event);
				}
				else
				{
					if (App->input->GetMouseButtonDown(1) == KEY_UP)
					{
						gui_event = MOUSE_BUTTON_RIGHT_UP;
						if (listener != NULL)
							listener->OnGUI(this, gui_event);
					}
				}
			}	
			else
			{
				gui_event = MOUSE_EXIT;
				if (listener != NULL)
					listener->OnGUI(this, gui_event);
			}	
		}
	}
	
}

void UIEntity::Debug()
{
	App->render->DrawLine(rect.x, rect.y, rect.x + rect.w, rect.y, 0, 0, 255, 255);
	App->render->DrawLine(rect.x, rect.y, rect.x, rect.y + rect.h, 0, 0, 255, 255);
	App->render->DrawLine(rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h, 0, 0, 255, 255);
	App->render->DrawLine(rect.x, rect.y + rect.h, rect.x + rect.w, rect.y + rect.h, 0, 0, 255, 255);
}


void UIEntity::GetScreenPos(int &x, int &y)
{
	x = y = 0;
	if (parent != NULL)
		parent->GetScreenPos(x, y);
	x += rect.x;
	y += rect.y;
}


void UIEntity::SetParent(UIEntity* _parent)
{
	parent = _parent;

	int px, py;
	px = py = 0;
	parent->GetScreenPos(px, py);

	rect.x += px;
	rect.y += py;
}