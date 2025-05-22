#pragma once
#include "raylib.h"
#include "Body.h"
#include "Spring.h"
#include <vector>

using bodies_t = std::vector<Body*>;
using springs_t = std::vector<Spring*>;

class World
{
public:
	~World();

	void Initialize(size_t poolSize = 30, const Vector2& gravity = { 0, -9.81f });
	void DestroyAll();

	void Step(float dt);
	void Draw(const class Scene& scene);

	// Body
	Body* CreateBody(const Vector2& position, float size, const Color& color);
	Body* CreateBody(Body::Type bodyType, const Vector2& position, float mass, float size, const Color& color);
	bodies_t& GetBodies() { return m_bodies; }

	//Spring
	Spring* CreateSpring(Body* bodyA, Body* bodyB, float restLength, float stiffness);

	inline static Vector2 gravity{ 0, -9.81f };
	inline static float gravitation{ 0.0f };
	inline static float springStiffness{ 1.0f };
	inline static bool simulate{ true };

private:
	bodies_t m_bodies;
	springs_t m_strings;
};