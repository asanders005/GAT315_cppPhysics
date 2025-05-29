#include "World.h"
#include "Utility/MathUtils.h"
#include "Physics/Gravitation.h"
#include "GUI/Gui.h"
#include "Collision/Collision.h"

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

Spring* World::CreateSpring(Body* bodyA, Body* bodyB, float restLength, float stiffness, float damping = 0)
{
	Spring* spring = new Spring(bodyA, bodyB, restLength, stiffness, damping);
	m_springs.push_back(spring);

	return spring;
}

void World::Step(float dt)
{
	if (!simulate) return;

	if (gravitation > 0) ApplyGravitation(m_bodies, gravitation);

	for (auto& spring : m_springs)
	{
		spring->ApplyForce(springStiffness);
	}

	for (auto& body : m_bodies)
	{
		body->Step(dt);
		body->ClearForce();
	}

	for (int i = 0; i < 5; i++)
	{
		CreateContacts(m_bodies, m_contacts);
		SeparateContacts(m_contacts);
		ResolveContacts(m_contacts);
		m_contacts.clear();
	}
}

void World::Draw(const Scene& scene)
{
	for (auto& spring : m_springs)
	{
		spring->Draw(scene);
	}
	for (auto& body : m_bodies)
	{
		body->Draw(scene);
	}
}

void World::DestroyAll()
{
	for (auto& spring : m_springs)
	{
		delete spring;
	}

	for (auto& body : m_bodies)
	{
		delete body;
	}

	m_springs.clear();
	m_bodies.clear();
}
