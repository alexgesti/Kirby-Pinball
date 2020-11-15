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
	WinAnim.PushBack({ 0, 0, 768, 729 }); // 1
	WinAnim.PushBack({ 768, 0, 768, 729 }); // 2
	WinAnim.PushBack({ 1536, 0, 768, 729 }); // 3
	WinAnim.PushBack({ 2304, 0, 768, 729 }); // 4
	WinAnim.PushBack({ 3072, 0, 768, 729 }); // 5
	WinAnim.PushBack({ 3840, 0, 768, 729 }); // 6
	WinAnim.PushBack({ 4608, 0, 768, 729 }); // 7
	WinAnim.PushBack({ 5376, 0, 768, 729 }); // 8
	WinAnim.PushBack({ 6144, 0, 768, 729 }); // 9
	WinAnim.PushBack({ 6912, 0, 768, 729 }); // 10
	WinAnim.PushBack({ 7680, 0, 768, 729 }); // 11
	WinAnim.PushBack({ 8448, 0, 768, 729 }); // 12
	WinAnim.PushBack({ 9216, 0, 768, 729 }); // 13
	WinAnim.PushBack({ 9984, 0, 768, 729 }); // 14
	WinAnim.PushBack({ 10752, 0, 768, 729 }); // 15
	WinAnim.PushBack({ 11520, 0, 768, 729 }); // 16
	WinAnim.PushBack({ 12288, 0, 768, 729 }); // 17
	WinAnim.PushBack({ 13056, 0, 768, 729 }); // 18
	WinAnim.PushBack({ 13824, 0, 768, 729 }); // 19
	WinAnim.PushBack({ 14592, 0, 768, 729 }); // 20
	WinAnim.PushBack({ 15360, 0, 768, 729 }); // 21
	WinAnim.PushBack({ 16128, 0, 768, 729 }); // 22
	WinAnim.PushBack({ 16896, 0, 768, 729 }); // 23
	WinAnim.PushBack({ 17664, 0, 768, 729 }); // 24
	WinAnim.PushBack({ 18432, 0, 768, 729 }); // 25
	WinAnim.PushBack({ 19200, 0, 768, 729 }); // 26
	WinAnim.PushBack({ 19968, 0, 768, 729 }); // 27
	WinAnim.loop = false;
	WinAnim.speed = 0.1f;
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
	wintext = App->textures->Load("Assets/sprites/Win_Dance.png");
	mrbrightMap = App->textures->Load("Assets/sprites/MrBright_Fondo.png");
	mrshineMap = App->textures->Load("Assets/sprites/MrShine_Fondo.png");

	bonus_fx = App->audio->LoadFx("Assets/audio/bonus.wav");

	App->audio->PlayMusic("Assets/audio/Bubly.ogg", 0);

	MrBrightAppear = false;
	YouWin = false;

	// Mr Shine parameters
	mrshinecurrentAnim = &SmovingR;

	hitboss = 0;
	SHitTemp = 60;
	BHitTemp = 60;

	// Win parameters
	wincurrentAnim = &WinAnim;

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
		662, 349,
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

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		flapperl.getLast()->data->body->ApplyForce({ 0, 200 }, { 0, 0 }, true);
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_IDLE)
		flapperl.getLast()->data->body->ApplyForce({ 0, -30 }, { 0, 0 }, true);

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		flapperr.getLast()->data->body->ApplyForce({ 0, -200 }, { 6, 50 }, true);
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_IDLE)
		flapperr.getLast()->data->body->ApplyForce({ 0, 30 }, { 6, 50 }, true);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = mapt.getFirst();

	// Scenary Boss Background

	if (MrBrightAppear) App->renderer->Blit(mrbrightMap, 0, 0, NULL);
	else App->renderer->Blit(mrshineMap, 0, 0, NULL);

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
	else if (hitboss >= 5 && SHitTemp < 60
		|| hitboss >= 10 && BHitTemp < 60)
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
		SDL_Rect rect = wincurrentAnim->GetCurrentFrame();
		App->renderer->Blit(wintext, 0, 0, &rect);
		wincurrentAnim->Update();
	}

	// Kirby

	c = kirbys.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(kirby, x - 5 , y - 5, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
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
