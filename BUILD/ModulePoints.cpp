/*#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePoints.h"
#include "ModuleFonts.h"
#include <stdio.h>

ModulePoints::ModulePoints(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModulePoints::~ModulePoints()
{

}

bool ModulePoints::Start()
{
	bool ret = true;

	char lookupTable[] = { "0123456789" };
	scoreFont = App->fonts->Load("Assets/sprites/FontsGame.png", lookupTable, 1);

	return ret;
}
update_status ModulePoints::Update()
{

	if (score > scoreTotal)  scoreTotal = score;

	return update_status::UPDATE_CONTINUE;
}

void ModulePoints::returnPoints()
{
	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score); //mirar 
	sprintf_s(HighText, 10, "%7d", scoreTotal);
	App->fonts->BlitText(30, 5, scoreFont, scoreText); //mirar
	App->fonts->BlitText(150, 5, scoreFont, HighText);
}

bool ModulePoints::CleanUp()
{
	//App->textures->Unload(texture);
	App->fonts->UnLoad(scoreFont);

	return true;
}*/
