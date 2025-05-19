#include "World.h"
#include "Body.h"
#include "Utility/MathUtils.h"
#include "Physics/Gravitation.h"

World::~World()
{
	DestroyAll();
}

void World::Initialize(size_t poolSize, const Vector2& gravity)
{
	World::gravity = gravity;
	// Preallocate memory for bodies
	m_bodies.reserve(poolSize);
	/*for (size_t i = 0; i < poolSize; ++i)
	{
		m_bodies.push_back(new Body());
	}*/
}

Body* World::CreateBody(const Vector2& position, float size, const Color& color)
{
	Body* body = new Body(position, size, color);
	m_bodies.push_back(body);

    return body;
}

Body* World::CreateBody(Body::Type bodyType, const Vector2& position, float mass, float size, const Color& color)
{
	Body* body = new Body(bodyType, position, mass, size, color);
	m_bodies.push_back(body);

	return body;
}

void World::Step(float dt)
{
	if (!simulate) return;

	
	if (gravitation > 0) ApplyGravitation(m_bodies, gravitation);


	for (auto& body : m_bodies)
	{
		body->Step(dt);
		body->ClearForce();
	}
}

void World::Draw(const Scene& scene)
{
	for (auto& body : m_bodies)
	{
		body->Draw(scene);
	}
}

void World::DestroyAll()
{
	for (auto& body : m_bodies)
	{
		delete body;
	}
	m_bodies.clear();
}
