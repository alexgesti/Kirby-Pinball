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

	circle = App->textures->Load("Assets/sprites/wheel.png"); 
	box = App->textures->Load("Assets/sprites/crate.png");
	kirby = App->textures->Load("Assets/sprites/Kirby_64.png");
	flipperl = App->textures->Load("Assets/sprites/Flippersl.png");
	flipperr = App->textures->Load("Assets/sprites/Flippersr.png");

	bonus_fx = App->audio->LoadFx("Assets/wab/bonus.wav");

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

	{
		int Flapperlc[16] = {
			110, 41,
			110, 50,
			105, 55,
			21, 45,
			1, 35,
			1, 11,
			11, 1,
			35, 1,
		};
		flapperl.add(App->physics->CreateChain(0, 0, Flapperlc, 16));
		holderl.add(App->physics->CreateRectangle(((SCREEN_WIDTH / 2) - 112 - (90 / 2)), (SCREEN_HEIGHT - (70 / 2) - 110), 11, 11));
	
		b2RevoluteJointDef Left;
		Left.bodyA = flapperl.getLast()->data->body;
		Left.bodyB = holderl.getLast()->data->body;
		Left.collideConnected = false;
		Left.upperAngle = 25 * DEGTORAD;
		Left.lowerAngle = -25 * DEGTORAD;
		Left.enableLimit = true;
		Left.localAnchorA.Set(PIXEL_TO_METERS(23), PIXEL_TO_METERS(23));
		App->physics->Jleft = (b2RevoluteJoint*)App->physics->world->CreateJoint(&Left);
	}
	{
		int Flapperrc[16] = {
			1, 41,
			1, 50,
			6, 55,
			90, 45,
			110, 35,
			110, 11,
			100, 1,
			76, 1,
		};
		flapperr.add(App->physics->CreateChain( 0, 0, Flapperrc, 16));
		holderr.add(App->physics->CreateRectangle(((SCREEN_WIDTH / 2) + 112 + (90 / 2)), (SCREEN_HEIGHT - (70 / 2) - 110), 11, 11));
	
		b2RevoluteJointDef Right;
		Right.bodyA = flapperr.getLast()->data->body;
		Right.bodyB = holderr.getLast()->data->body;
		Right.collideConnected = false;
		Right.upperAngle = 25 * DEGTORAD;
		Right.lowerAngle = -25 * DEGTORAD;
		Right.enableLimit = true;
		Right.localAnchorA.Set(PIXEL_TO_METERS(88), PIXEL_TO_METERS(23));
		App->physics->Jleft = (b2RevoluteJoint*)App->physics->world->CreateJoint(&Right);
	}

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
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		kirbys.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
		flapperl.getLast()->data->body->ApplyForce({ 0, -500 }, { 110, 41 }, true);

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
		flapperr.getLast()->data->body->ApplyForce({ 0, -500 }, { 1, 41 }, true);

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
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
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

	c = kirbys.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(kirby, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = flapperl.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(flipperl, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = flapperr.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(flipperr, x, y, NULL, 1.0f, c->data->GetRotation());
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
