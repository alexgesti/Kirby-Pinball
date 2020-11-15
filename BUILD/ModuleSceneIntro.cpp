#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	kirby = NULL;

	//Mr Shine
	SmovingR.PushBack({ 224, 0, 112, 112 });
	SmovingR.PushBack({ 112, 0, 112, 112 });
	SmovingR.loop = true;
	SmovingR.speed = 0.05f;

	SHitR.PushBack({ 448, 0, 112, 112 });
	SHitR.PushBack({ 560, 0, 112, 112 });
	SHitR.loop = true;
	SHitR.speed = 0.1f;

	//Mr Bright
	BmovingR.PushBack({ 2, 2, 76, 80 });
	BmovingR.PushBack({ 78, 2, 76, 80 });
	BmovingR.loop = true;
	BmovingR.speed = 0.05f;

	BHitR.PushBack({ 154, 2, 76, 80 });

	//Spark Hit
	SparksHit.PushBack({ 0, 0, 160, 160 });
	SparksHit.PushBack({ 160, 0, 160, 160 });
	SparksHit.PushBack({ 320, 0, 160, 160 });
	SparksHit.PushBack({ 480, 0, 160, 160 });
	SparksHit.PushBack({ 640, 0, 160, 160 });
	SparksHit.PushBack({ 800, 0, 160, 160 });
	SparksHit.loop = true;
	SparksHit.speed = 0.2f;

	//Kirby Win
	WinAnim1.PushBack({ 0, 0, 323, 220 }); // 1
	WinAnim1.PushBack({ 323, 0, 323, 220 }); // 2
	WinAnim2.PushBack({ 0, 0, 323, 220 }); // 3
	WinAnim2.PushBack({ 323, 0, 323, 220 }); // 4
	WinAnim3.PushBack({ 0, 0, 323, 220 }); // 5
	WinAnim3.PushBack({ 323, 0, 323, 220 }); // 6
	WinAnim4.PushBack({ 0, 0, 323, 220 }); // 7
	WinAnim4.PushBack({ 323, 0, 323, 220 }); // 8
	WinAnim5.PushBack({ 0, 0, 323, 220 }); // 9
	WinAnim5.PushBack({ 323, 0, 323, 220 }); // 10
	WinAnim6.PushBack({ 0, 0, 323, 220 }); // 11
	WinAnim6.PushBack({ 323, 0, 323, 220 }); // 12
	WinAnim7.PushBack({ 0, 0, 323, 220 }); // 13
	WinAnim7.PushBack({ 323, 0, 323, 220 }); // 14
	WinAnim8.PushBack({ 0, 0, 323, 220 }); // 15
	WinAnim8.PushBack({ 323, 0, 323, 220 }); // 16
	WinAnim9.PushBack({ 0, 0, 323, 220 }); // 17
	WinAnim9.PushBack({ 323, 0, 323, 220 }); // 18
	WinAnim10.PushBack({ 0, 0, 323, 220 }); // 19
	WinAnim10.PushBack({ 323, 0, 323, 220 }); // 20
	WinAnim11.PushBack({ 0, 0, 323, 220 }); // 21
	WinAnim11.PushBack({ 323, 0, 323, 220 }); // 22
	WinAnim12.PushBack({ 0, 0, 323, 220 }); // 23
	WinAnim12.PushBack({ 323, 0, 323, 220 }); // 24
	WinAnim13.PushBack({ 0, 0, 323, 220 }); // 25
	WinAnim13.PushBack({ 323, 0, 323, 220 }); // 26
	WinAnim14.PushBack({ 0, 0, 323, 220 }); // 27
	WinAnim1.speed = 0.1f; 
	WinAnim2.speed = 0.1f;
	WinAnim3.speed = 0.1f;
	WinAnim4.speed = 0.1f;
	WinAnim5.speed = 0.1f;
	WinAnim6.speed = 0.1f;
	WinAnim7.speed = 0.1f;
	WinAnim8.speed = 0.1f;
	WinAnim9.speed = 0.1f;
	WinAnim10.speed = 0.1f;
	WinAnim11.speed = 0.1f;
	WinAnim12.speed = 0.1f;
	WinAnim13.speed = 0.1f;
	WinAnim14.speed = 0.1f;

	//cloudAnim.PushBack({80, 60, 4, 4});
	//cloudhit.PushBack({84, 86, 88, 4});

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	maptt = App->textures->Load("Assets/sprites/Fondo_Sprite.png");
	kirby = App->textures->Load("Assets/sprites/Kirby_64_ball.png");
	flipperl = App->textures->Load("Assets/sprites/Flippersl.png");
	flipperr = App->textures->Load("Assets/sprites/Flippersr.png");
	mrshine = App->textures->Load("Assets/sprites/MrShine.png");
	mrbright = App->textures->Load("Assets/sprites/MrBright.png");
	sparkhit = App->textures->Load("Assets/sprites/Star_KO.png");
	star = App->textures->Load("Assets/sprites/Star_1.png");
	cloud = App->textures->Load("Assets/sprites/Nube.png");
	mrbrightMap = App->textures->Load("Assets/sprites/MrBright_Fondo.png");
	mrshineMap = App->textures->Load("Assets/sprites/MrShine_Fondo.png");
	
	// Win textures call
	wintext1 = App->textures->Load("Assets/sprites/Win_Dance1.png");
	wintext2 = App->textures->Load("Assets/sprites/Win_Dance2.png");
	wintext3 = App->textures->Load("Assets/sprites/Win_Dance3.png");
	wintext4 = App->textures->Load("Assets/sprites/Win_Dance4.png");
	wintext5 = App->textures->Load("Assets/sprites/Win_Dance5.png");
	wintext6 = App->textures->Load("Assets/sprites/Win_Dance6.png");
	wintext7 = App->textures->Load("Assets/sprites/Win_Dance7.png");
	wintext8 = App->textures->Load("Assets/sprites/Win_Dance8.png");
	wintext9 = App->textures->Load("Assets/sprites/Win_Dance9.png");
	wintext10 = App->textures->Load("Assets/sprites/Win_Dance10.png");
	wintext11 = App->textures->Load("Assets/sprites/Win_Dance11.png");
	wintext12 = App->textures->Load("Assets/sprites/Win_Dance12.png");
	wintext13 = App->textures->Load("Assets/sprites/Win_Dance13.png");
	wintext14 = App->textures->Load("Assets/sprites/Win_Dance14.png");

	bonus_fx = App->audio->LoadFx("Assets/audio/bonus.wav");

	App->audio->PlayMusic("Assets/audio/Bubly.ogg", 0);

	MrBrightAppear = false;
	YouWin = false;
	debug = false;

	// Mr Shine parameters
	mrshinecurrentAnim = &SmovingR;

	hitboss = 0;
	SHitTemp = 60;
	BHitTemp = 60;
	klives = 3;

	wincurrentAnim = &WinAnim1;

	//Flapper left
	int Flapperlc[16]
	{
		110, 41,
		110, 50,
		105, 55,
		21, 45,
		1, 35,
		1, 11,
		11, 1,
		35, 1,
	};

	flapperl.add(App->physics->CreateDynamicPolygon(257, 592, Flapperlc, 16));
	holderl.add(App->physics->CreateStaticCircle(257, 592, 6));
	
	b2RevoluteJointDef Left;
	Left.bodyA = flapperl.getLast()->data->body;
	Left.bodyB = holderl.getLast()->data->body;
	Left.collideConnected = false;
	Left.upperAngle = 50 * DEGTORAD;
	Left.lowerAngle = 0 * DEGTORAD;
	Left.enableLimit = true;
	Left.localAnchorA.Set(PIXEL_TO_METERS(23), PIXEL_TO_METERS(23));
	Jleft = (b2RevoluteJoint*)App->physics->world->CreateJoint(&Left);
	
	//Flapper Right
	int Flapperrc[16]
	{
		1, 41,
		1, 50,
		6, 55,
		90, 45,
		110, 35,
		110, 11,
		100, 1,
		76, 1,
	};

	flapperr.add(App->physics->CreateDynamicPolygon(350, 592, Flapperrc, 16));
	holderr.add(App->physics->CreateStaticCircle(511, 592, 6));
	
	b2RevoluteJointDef Right;
	Right.bodyA = flapperr.getLast()->data->body;
	Right.bodyB = holderr.getLast()->data->body;
	Right.collideConnected = false;
	Right.referenceAngle = -50 * DEGTORAD;
	Right.upperAngle = 50 * DEGTORAD;
	Right.lowerAngle = 0 * DEGTORAD;
	Right.enableLimit = true;
	Right.localAnchorA.Set(PIXEL_TO_METERS(88), PIXEL_TO_METERS(23));
	Jright = (b2RevoluteJoint*)App->physics->world->CreateJoint(&Right);

	int Maptc[78]
	{
		298, 728,
		298, 714,
		77, 604,
		68, 594,
		58, 575,
		58, 418,
		68, 394,
		82, 379,
		106, 370,
		106, 350,
		77, 349,
		53, 340,
		44, 330,
		34, 306,
		34, 77,
		44, 53,
		53, 44,
		77, 34,
		691, 34,
		715, 44,
		724, 53,
		734, 77,
		734, 306,
		724, 330,
		715, 340,
		691, 350,
		662, 351,
		662, 370,
		686, 379,
		700, 394,
		710, 418,
		710, 575,
		700, 594,
		470, 714,
		470, 728,
		767, 728,
		767, 0,
		0, 0,
		0, 728,
	};

	mapt.add(App->physics->CreateStaticChain(0, 0, Maptc, 78));

	int Tubolc[14]
	{
		124, 431,
		130, 431,
		130, 508,
		144, 521,
		231, 565,
		225, 586,
		124, 533,
	};

	tubol.add(App->physics->CreateStaticChain(0, 0, Tubolc, 14));

	int Tuborc[14]
	{
		644, 431,
		638, 431,
		638, 508,
		623, 522,
		537, 565,
		552, 581,
		644, 533,
	};

	tubor.add(App->physics->CreateStaticChain(0, 0, Tuborc, 14));

	int Trianlc[6]
	{
		191, 436,
		231, 494,
		191, 474,
	};

	trianl.add(App->physics->CreateStaticChain(0, 0, Trianlc, 6, 1));

	int Trianrc[6]
	{
		576, 436,
		537, 494,
		576, 474,
	};

	trianr.add(App->physics->CreateStaticChain(0, 0, Trianrc, 6, 1));

	mrshines.add(App->physics->CreateStaticCircle(135, 140, 30));
	mrshines.getLast()->data->listener = this;

	kirbys.add(App->physics->CreateDynamicCircle(610, 60, 28));
	kirbys.getLast()->data->listener = this;

	return ret;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		kirbys.add(App->physics->CreateDynamicCircle(App->input->GetMouseX(), App->input->GetMouseY(), 28));
		kirbys.getLast()->data->listener = this;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) YouWin = true;

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		if (debug)
		{
			debug = false;
		}
		else if (debug == false)
		{
			debug = true;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		flapperl.getLast()->data->body->ApplyForce({ 0, 200 }, { 0, 0 }, true);
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_IDLE)
		flapperl.getLast()->data->body->ApplyForce({ 0, -30 }, { 0, 0 }, true);

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		flapperr.getLast()->data->body->ApplyForce({ 0, -200 }, { 6, 50 }, true);
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_IDLE)
		flapperr.getLast()->data->body->ApplyForce({ 0, 30 }, { 6, 50 }, true);

	p2List_item<PhysBody*>* c = kirbys.getLast();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		if (debug)
		{
			c->data->body->SetTransform(PIXEL_TO_METERS(b2Vec2(App->input->GetMouseX(), App->input->GetMouseY())), 0);
			c->data->body->SetLinearVelocity(b2Vec2(0, 0));
		}
		if (y > 1000) 
		{
			klives--;
			if (klives > 0)
			{
				kirbys.add(App->physics->CreateDynamicCircle(610, 60, 28));
				kirbys.getLast()->data->listener = this;
			}
		}
		c = c->next;
	}
	
	// Scenary Boss Background
	if (MrBrightAppear) App->renderer->Blit(mrbrightMap, 0, 0, NULL);
	else App->renderer->Blit(mrshineMap, 0, 0, NULL);

	// All draw functions ------------------------------------------------------
	c = mapt.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(maptt, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// Mr Shine & Mr Bright
	c = mrshines.getFirst();

	if (hitboss >= 5 && SHitTemp >= 60 && hitboss < 10)
	{
		MrBrightAppear = true;

		if (hitboss == 5) {
			mrshinecurrentAnim = &BmovingR;
		}

		while (c != NULL)
		{
			int x, y;
			SDL_Rect rect = mrshinecurrentAnim->GetCurrentFrame();

			c->data->GetPosition(x, y);
			App->renderer->Blit(mrbright, x - 10, y - 14, &rect);
			c = c->next;
		}

		BHitTemp++;
	}
	else if (hitboss >= 5 && SHitTemp < 60 || hitboss >= 10 && BHitTemp < 60)
	{
		mrshinecurrentAnim = &SparksHit;

		while (c != NULL)
		{
			int x, y;
			SDL_Rect rect = mrshinecurrentAnim->GetCurrentFrame();

			c->data->GetPosition(x, y);
			App->renderer->Blit(sparkhit, x - 40, y - 40, &rect);
			c = c->next;
		}

		if (hitboss >= 5 && SHitTemp < 60) SHitTemp++;
		else if (hitboss >= 10 && BHitTemp < 60) BHitTemp++;
	}
	else if (hitboss < 5)
	{
		while (c != NULL)
		{
			int x, y;
			SDL_Rect rect = mrshinecurrentAnim->GetCurrentFrame();

			c->data->GetPosition(x, y);
			App->renderer->Blit(mrshine, x - 32, y - 42, &rect);
			c = c->next;
		}

		SHitTemp++;
	}
	else
	{
		while (c != NULL)
		{
			int x, y;

			c->data->GetPosition(x, y);
			c->data->body->SetTransform(b2Vec2_zero, 0);
			c = c->next;
		}

		YouWin = true;
	}

	// Win Dance
	if (YouWin)
	{
		if (WinAnim1.FinishedAlready == true && WinAnim2.FinishedAlready == false) wincurrentAnim = &WinAnim2;
		else if (WinAnim2.FinishedAlready == true && WinAnim3.FinishedAlready == false) wincurrentAnim = &WinAnim3;
		else if (WinAnim3.FinishedAlready == true && WinAnim4.FinishedAlready == false) wincurrentAnim = &WinAnim4;
		else if (WinAnim4.FinishedAlready == true && WinAnim5.FinishedAlready == false) wincurrentAnim = &WinAnim5;
		else if (WinAnim5.FinishedAlready == true && WinAnim6.FinishedAlready == false) wincurrentAnim = &WinAnim6;
		else if (WinAnim6.FinishedAlready == true && WinAnim7.FinishedAlready == false) wincurrentAnim = &WinAnim7;
		else if (WinAnim7.FinishedAlready == true && WinAnim8.FinishedAlready == false) wincurrentAnim = &WinAnim8;
		else if (WinAnim8.FinishedAlready == true && WinAnim9.FinishedAlready == false) wincurrentAnim = &WinAnim9;
		else if (WinAnim9.FinishedAlready == true && WinAnim10.FinishedAlready == false) wincurrentAnim = &WinAnim10;
		else if (WinAnim10.FinishedAlready == true && WinAnim11.FinishedAlready == false) wincurrentAnim = &WinAnim11;
		else if (WinAnim11.FinishedAlready == true && WinAnim12.FinishedAlready == false) wincurrentAnim = &WinAnim12;
		else if (WinAnim12.FinishedAlready == true && WinAnim13.FinishedAlready == false) wincurrentAnim = &WinAnim13;
		else if (WinAnim13.FinishedAlready == true) wincurrentAnim = &WinAnim14;

		SDL_Rect rect = wincurrentAnim->GetCurrentFrame();

		// FAKE'IT UNTIL YOU MAKE'IT
		if (WinAnim1.FinishedAlready == false) App->renderer->Blit(wintext1, SCREEN_WIDTH / 2 - 161, SCREEN_HEIGHT / 2 - 110, &rect);
		else if (WinAnim1.FinishedAlready == true && WinAnim2.FinishedAlready == false) App->renderer->Blit(wintext2, SCREEN_WIDTH / 2 - 161, SCREEN_HEIGHT / 2 - 110, &rect);
		else if (WinAnim2.FinishedAlready == true && WinAnim3.FinishedAlready == false) App->renderer->Blit(wintext3, SCREEN_WIDTH / 2 - 161, SCREEN_HEIGHT / 2 - 110, &rect);
		else if (WinAnim3.FinishedAlready == true && WinAnim4.FinishedAlready == false) App->renderer->Blit(wintext4, SCREEN_WIDTH / 2 - 161, SCREEN_HEIGHT / 2 - 110, &rect);
		else if (WinAnim4.FinishedAlready == true && WinAnim5.FinishedAlready == false) App->renderer->Blit(wintext5, SCREEN_WIDTH / 2 - 161, SCREEN_HEIGHT / 2 - 110, &rect);
		else if (WinAnim5.FinishedAlready == true && WinAnim6.FinishedAlready == false) App->renderer->Blit(wintext6, SCREEN_WIDTH / 2 - 161, SCREEN_HEIGHT / 2 - 110, &rect);
		else if (WinAnim6.FinishedAlready == true && WinAnim7.FinishedAlready == false) App->renderer->Blit(wintext7, SCREEN_WIDTH / 2 - 161, SCREEN_HEIGHT / 2 - 110, &rect);
		else if (WinAnim7.FinishedAlready == true && WinAnim8.FinishedAlready == false) App->renderer->Blit(wintext8, SCREEN_WIDTH / 2 - 161, SCREEN_HEIGHT / 2 - 110, &rect);
		else if (WinAnim8.FinishedAlready == true && WinAnim9.FinishedAlready == false) App->renderer->Blit(wintext9, SCREEN_WIDTH / 2 - 161, SCREEN_HEIGHT / 2 - 110, &rect);
		else if (WinAnim9.FinishedAlready == true && WinAnim10.FinishedAlready == false) App->renderer->Blit(wintext10, SCREEN_WIDTH / 2 - 161, SCREEN_HEIGHT / 2 - 110, &rect);
		else if (WinAnim10.FinishedAlready == true && WinAnim11.FinishedAlready == false) App->renderer->Blit(wintext11, SCREEN_WIDTH / 2 - 161, SCREEN_HEIGHT / 2 - 110, &rect);
		else if (WinAnim11.FinishedAlready == true && WinAnim12.FinishedAlready == false) App->renderer->Blit(wintext12, SCREEN_WIDTH / 2 - 161, SCREEN_HEIGHT / 2 - 110, &rect);
		else if (WinAnim12.FinishedAlready == true && WinAnim13.FinishedAlready == false) App->renderer->Blit(wintext13, SCREEN_WIDTH / 2 - 161, SCREEN_HEIGHT / 2 - 110, &rect);
		else if (WinAnim13.FinishedAlready == true) App->renderer->Blit(wintext14, SCREEN_WIDTH / 2 - 161, SCREEN_HEIGHT / 2 - 110, &rect);


		wincurrentAnim->Update();
	}

	// Flapper Left
	c = flapperl.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(flipperl, x, y, NULL, 1.0f, c->data->GetRotation(), -1, -1);
		c = c->next;
	}

	// Flapper Right
	c = flapperr.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(flipperr, x, y, NULL, 1.0f, c->data->GetRotation(), -1, -1);
		c = c->next;
	}

	// Kirby
	c = kirbys.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(kirby, x - 5, y - 5, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	mrshinecurrentAnim->Update();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	if (hitboss >= 5 && SHitTemp >= 60)
	{
		if (bodyA->body == kirbys.getLast()->data->body && bodyB->body == mrshines.getLast()->data->body)
		{
			mrshinecurrentAnim = &BHitR;
			BHitTemp = 0;
			if (hitOnce == false) 
			{
				hitboss++;
				hitOnce = true;
				LOG("%d", hitboss)
			}
		}
		else if (BHitTemp >= 60 && hitboss < 10)
		{
			mrshinecurrentAnim = &BmovingR;
		}

		if (bodyA->body == kirbys.getLast()->data->body && bodyB->body == mapt.getLast()->data->body && hitboss < 10)
		{
			hitOnce = false;
		}
		if (bodyA->body == kirbys.getLast()->data->body && bodyB->body == flapperl.getLast()->data->body && hitboss < 10)
		{
			hitOnce = false;
		}
		if (bodyA->body == kirbys.getLast()->data->body && bodyB->body == flapperr.getLast()->data->body && hitboss < 10)
		{
			hitOnce = false;
		}
	}
	else
	{
		if (bodyA->body == kirbys.getLast()->data->body && bodyB->body == mrshines.getLast()->data->body)
		{
			mrshinecurrentAnim = &SHitR;
			SHitTemp = 0;
			if (hitOnce == false)
			{
				hitboss++;
				hitOnce = true;
				LOG("%d", hitboss)
			}
		}
		else if (SHitTemp >= 60 && hitboss < 5)
		{
			mrshinecurrentAnim = &SmovingR;	
		}

		if (bodyA->body == kirbys.getLast()->data->body && bodyB->body == mapt.getLast()->data->body && hitboss < 5)
		{
			hitOnce = false;
		}
		if (bodyA->body == kirbys.getLast()->data->body && bodyB->body == flapperl.getLast()->data->body && hitboss < 5)
		{
			hitOnce = false;
		}
		if (bodyA->body == kirbys.getLast()->data->body && bodyB->body == flapperr.getLast()->data->body && hitboss < 5)
		{
			hitOnce = false;
		}
	}
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}
