#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -14.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateDynamicCircle(int x, int y, int radius);
	PhysBody* CreateStaticCircle(int x, int y, int radius);
	PhysBody* CreateDynamicRectangle(int x, int y, int width, int height);
	PhysBody* CreateStaticRectangle(int x, int y, int width, int height);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreateDynamicChain(int x, int y, int* points, int size);
	PhysBody* CreateStaticChain(int x, int y, int* points, int size, float restitution = 0);
	PhysBody* CreateDynamicPolygon(int x, int y, int* points, int size);
	PhysBody* CreateStaticPolygon(int x, int y, int* points, int size);

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

	b2World* world;

private:

	bool debug;
	b2MouseJoint* mouse_joint;
	b2Body* ground;
};