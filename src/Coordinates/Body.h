#pragma once
#include "raylib.h"

struct Body
{
	Body() = default;

	Body(const Vector2& pos, const Vector2& vel, float s, const Color& c) : 
		position(pos), velocity(vel), size(s), color(c) 
	{}

	void Step(float dt);
	void Draw(const class Scene& scene);

public:
	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };

	float size{ 0 };
	Color color{ WHITE };
};