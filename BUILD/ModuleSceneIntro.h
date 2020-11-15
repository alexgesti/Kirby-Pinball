#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModulePhysics.h"
#include "Animation.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> mapt;
	p2List<PhysBody*> kirbys;
	p2List<PhysBody*> flapperl;
	p2List<PhysBody*> flapperr;
	p2List<PhysBody*> holderl;
	p2List<PhysBody*> holderr;
	p2List<PhysBody*> tubol; 
	p2List<PhysBody*> tubor;
	p2List<PhysBody*> trianl;
	p2List<PhysBody*> trianr;
	p2List<PhysBody*> mrshines;

	// Bosses Live & End
	bool MrBrightAppear;
	bool hitOnce;
	int hitboss;
	bool YouWin;

	b2RevoluteJoint* Jleft;
	b2RevoluteJoint* Jright;

	SDL_Texture* kirby;
	SDL_Texture* flipperl;
	SDL_Texture* flipperr;
	SDL_Texture* maptt;
	SDL_Texture* mrshine;
	SDL_Texture* mrbright;
	SDL_Texture* sparkhit;
	SDL_Texture* wintext;
	SDL_Texture* mrbrightMap;
	SDL_Texture* mrshineMap;

	// A set of animations
	Animation* mrshinecurrentAnim;
	Animation* wincurrentAnim;

	Animation SmovingR;
	Animation SHitR;

	Animation BmovingR;
	Animation BHitR;

	Animation SparksHit;

	Animation WinAnim;

	// MrShine parameters
	float SHitTemp;
	float BHitTemp;

	uint bonus_fx;
};
