#pragma once
#include "raylib.h"

struct Body
{
	Body() = default;

	Body(const Vector2& pos, float s, const Color& c) :
		position(pos), size(s), color(c)
	{
	}

	Body(const Vector2& pos, const Vector2& vel, float s, const Color& c) : 
		position(pos), velocity(vel), size(s), color(c) 
	{}

	void Step(float dt);
	void Draw(const class Scene& scene);

public:
	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0,0 };
	float damping{ 0.2f }; // Damping factor to slow down the body over time

	float size{ 1 };
	Color color{ WHITE };

	Body* next{ nullptr };
	Body* prev{ nullptr };
};