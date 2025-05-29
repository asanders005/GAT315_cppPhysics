#pragma once
#include "raylib.h"

struct Contact
{
	struct Body* bodyA;
	struct Body* bodyB;

	float restitution;
	float depth;
	Vector2 normal;
};