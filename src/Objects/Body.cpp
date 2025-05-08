#include "Body.h"
#include "raymath.h"
#include "Scene/scene.h"

void Body::Step(float dt)
{
	position += velocity * dt;
	velocity *= 1 / (1.0f + (damping * dt));
}

void Body::Draw(const Scene& scene)
{
	scene.DrawCircle(position, size, color);
}
