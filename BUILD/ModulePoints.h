/*#ifndef __MODULE_POINTS_H__
#define __MODULE_POINTS_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModulePoints : public Module
{
public:
	ModulePoints(Application* app, bool start_enabled = true);

	//Destructor
	~ModulePoints();
	bool Start() override;
	void returnPoints();
	update_status Update();
	bool CleanUp() override;

	//Fonts 
	int score = 00000;
	int scoreTotal = 50000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };
	char HighText[10] = { "\0" };
};
#endif // __ModulePoints_H*/
