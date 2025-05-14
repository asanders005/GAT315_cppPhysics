#pragma once
#include "raylib.h"

struct Body
{
public:
	enum class Type
	{
		Static,
		Kinematic,
		Dynamic,
	};

public:
	Body() = default;

	Body(const Vector2& pos, float s, const Color& c) :
		position{ pos }, size{ s }, color{ c }
	{
	}

	Body(const Vector2& pos, const Vector2& vel, float s, const Color& c) : 
		position{pos}, velocity{vel}, size{s}, color{c} 
	{}

	Body(Type type, const Vector2& pos, float mass, float s, const Color& c) :
		type{ type }, position{pos}, mass{mass}, size{s}, color{c}
	{
		invMass = (type == Type::Dynamic && mass != 0) ? 1.0f / mass : 0.0f;
	}

	void Step(float dt);
	void Draw(const class Scene& scene);

	void ApplyForce(const Vector2& force);
	void ClearForce() { force = { 0, 0 }; }

public:
	Vector2 position{ 0, 0 };

	Vector2 acceleration{ 0, 0 };
	Vector2 force{ 0, 0 };
	Vector2 velocity{ 0,0 };
	float damping{ 0.2f }; // Damping factor to slow down the body over time

	float mass{ 1 };
	float invMass{ 1 };

	float gravityScale{ 1 };
	float restitution{ 0.5f }; 

	float size{ 1 };
	Color color{ WHITE };

	Type type{ Type::Dynamic };
};