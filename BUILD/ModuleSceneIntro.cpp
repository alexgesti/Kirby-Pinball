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
	circle = box = kirby = NULL;
	ray_on = false;
	sensed = false;
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
	circle = App->textures->Load("Assets/sprites/wheel.png"); 
	box = App->textures->Load("Assets/sprites/crate.png");
	kirby = App->textures->Load("Assets/sprites/Kirby_64_ball.png");
	flipperl = App->textures->Load("Assets/sprites/Flippersl.png");
	flipperr = App->textures->Load("Assets/sprites/Flippersr.png");

	bonus_fx = App->audio->LoadFx("Assets/wab/bonus.wav");

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

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
		77, 350,
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
		662, 350,
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

	trianl.add(App->physics->CreateStaticChain(0, 0, Trianlc, 6));

	int Trianrc[6]
	{
		576, 436,
		537, 494,
		576, 474,
	};

	trianr.add(App->physics->CreateStaticChain(0, 0, Trianrc, 6));

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateDynamicCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateDynamicRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		kirbys.add(App->physics->CreateDynamicCircle(App->input->GetMouseX(), App->input->GetMouseY(), 28));

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		flapperl.getLast()->data->body->ApplyForce({ 0, 100 }, { 0, 0 }, true);
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE)
		flapperl.getLast()->data->body->ApplyForce({ 0, -15 }, { 0, 0 }, true);

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		flapperr.getLast()->data->body->ApplyForce({ 0, -100 }, { 6, 50 }, true);
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
		flapperr.getLast()->data->body->ApplyForce({ 0, 15 }, { 6, 50 }, true);

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = mapt.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(maptt, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = kirbys.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(kirby, x -5 , y-5, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = flapperl.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(flipperl, x, y, NULL, 1.0f, c->data->GetRotation(), -1, -1);
		c = c->next;
	}

	c = flapperr.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(flipperr, x, y, NULL, 1.0f, c->data->GetRotation(), -1, -1);
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
