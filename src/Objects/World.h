#pragma once
#include "raylib.h"
#include <vector>

class World
{
public:
	~World();

	void Initialize(size_t poolSize = 30, const Vector2& gravity = { 0, -9.81f });

	struct Body* CreateBody(const Vector2& position, float size, const Color& color);
	struct Body* CreateBody(int bodyType, const Vector2& position, float mass, float size, const Color& color);
	void Step(float dt);
	void Draw(const class Scene& scene);

	void DestroyAll();

	std::vector<struct Body*>& GetBodies() { return m_bodies; }

	static Vector2 gravity;

private:
	std::vector<struct Body*> m_bodies;
};