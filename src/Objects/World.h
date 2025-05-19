#pragma once
#include "raylib.h"
#include "Body.h"
#include <vector>

using bodies_t = std::vector<struct Body*>;

class World
{
public:
	~World();

	void Initialize(size_t poolSize = 30, const Vector2& gravity = { 0, -9.81f });

	struct Body* CreateBody(const Vector2& position, float size, const Color& color);
	struct Body* CreateBody(Body::Type bodyType, const Vector2& position, float mass, float size, const Color& color);
	void Step(float dt);
	void Draw(const class Scene& scene);

	void DestroyAll();

	bodies_t& GetBodies() { return m_bodies; }

	inline static Vector2 gravity{ 0, -9.81f };
	inline static float gravitation{ 0.0f };
	inline static float springStiffness{ 1.0f };
	inline static bool simulate{ true };

private:
	bodies_t m_bodies;
};