#pragma once
#include "raylib.h"
#include <vector>

class World
{
public:
	~World();

	void Initialize(size_t poolSize = 30, const Vector2& gravity = { 0, -9.81f });

	struct Body* CreateBody(const Vector2& position, float size, const Color& color);
	void Step(float dt);
	void Draw(const class Scene& scene);

	void DestroyAll();

private:
	Vector2 m_gravity;
	std::vector<struct Body*> m_bodies;
};