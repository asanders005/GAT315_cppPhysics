#include "Body.h"
#include "Scene/scene.h"
#include "Utility/Integrator.h"

#include "raymath.h"

void Body::Step(float dt)
{
	if (type != Type::Dynamic) return;

	force += (World::gravity * gravityScale) * mass;
	acceleration = force * invMass;

	SemiImplicitIntegrator(*this, dt);

	
}

void Body::Draw(const Scene& scene)
{
	scene.DrawCircle(position, size, color);
}

void Body::ApplyForce(const Vector2& force)
{
	this->force += force;
}
