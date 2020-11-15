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
	p2List<PhysBody*> cloudstar1;
	p2List<PhysBody*> cloudstar2;
	p2List<PhysBody*> cloudstar3;
	p2List<PhysBody*> cloudstar4;
	p2List<PhysBody*> cloudstar5;
	
	// Counter GameOver Sound
	float MusicGOStop = 0;

	// Bosses Live & End
	bool Hit1;
	bool Hit2;
	bool Hit3;
	bool Hit4;
	bool Hit5;
	int counthit1;
	int counthit2;
	int counthit3;
	int counthit4;
	int counthit5;
	int Chitt1;
	int Chitt2;
	
	bool MrBrightAppear;
	bool hitOnce;
	bool YouWin;
	bool YouLost;
	bool ChangeMusic;
	bool debug;
	bool createdonce;
	int hitboss;
	int klives;

	b2RevoluteJoint* Jleft;
	b2RevoluteJoint* Jright;

	SDL_Texture* kirby;
	SDL_Texture* flipperl;
	SDL_Texture* flipperr;
	SDL_Texture* maptt;
	SDL_Texture* mrshine;
	SDL_Texture* mrbright;
	SDL_Texture* sparkhit;
	SDL_Texture* star;
	SDL_Texture* cloud;
	SDL_Texture* mrbrightMap;
	SDL_Texture* mrshineMap;
	SDL_Texture* GameOver;
	SDL_Texture* Life;

	// Win Texture set
	SDL_Texture* wintext1;
	SDL_Texture* wintext2;
	SDL_Texture* wintext3;
	SDL_Texture* wintext4;
	SDL_Texture* wintext5;
	SDL_Texture* wintext6;
	SDL_Texture* wintext7;
	SDL_Texture* wintext8;
	SDL_Texture* wintext9;
	SDL_Texture* wintext10;
	SDL_Texture* wintext11;
	SDL_Texture* wintext12;
	SDL_Texture* wintext13;
	SDL_Texture* wintext14;

	// A set of animations
	Animation* mrshinecurrentAnim;
	Animation* wincurrentAnim;
	Animation* cloudcurrentAnim1;
	Animation* cloudcurrentAnim2;
	Animation* gamecurrentAnim;

	Animation SmovingR;
	Animation SHitR;

	Animation BmovingR;
	Animation BHitR;

	Animation SparksHit;

	Animation cloudAnim;
	Animation cloudhit;

	Animation GameOverAnim;

	// Win Anim Set
	Animation WinAnim1;
	Animation WinAnim2;
	Animation WinAnim3;
	Animation WinAnim4;
	Animation WinAnim5;
	Animation WinAnim6;
	Animation WinAnim7;
	Animation WinAnim8;
	Animation WinAnim9;
	Animation WinAnim10;
	Animation WinAnim11;
	Animation WinAnim12;
	Animation WinAnim13;
	Animation WinAnim14;

	// MrShine parameters
	float SHitTemp;
	float BHitTemp;

	uint bonus_fx;
};
