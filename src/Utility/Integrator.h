#pragma once
#include "Objects/Body.h"
#include "raymath.h"


inline void ExplicitIntegrator(Body& body, float timeStep)
{
	body.position += body.velocity * timeStep;
	body.velocity += body.acceleration * timeStep;
	body.velocity *= 1 / (1.0f + (body.damping * timeStep));
}

inline void SemiImplicitIntegrator(Body& body, float timeStep)
{
	body.velocity += body.acceleration * timeStep;
	body.position += body.velocity * timeStep;
	body.velocity *= 1 / (1.0f + (body.damping * timeStep));
}