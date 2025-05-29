#include "Collision.h"
#include "Contact.h"
#include "Utility/MathUtils.h"
#include "raymath.h"

bool Intersects(Body* bodyA, Body* bodyB);

void CreateContacts(const bodies_t& bodies, contacts_t& contacts)
{
	for (int i = 0; i < bodies.size(); i++)
	{
		Body* bodyA = bodies[i];
		for (int j = i + 1; j < bodies.size(); j++)
		{
			Body* bodyB = bodies[j];
			if (bodyA->type != Body::Type::Dynamic && bodyB->type != Body::Type::Dynamic)
			{
				continue; // Only create contacts for dynamic bodies
			}

			if (Intersects(bodyA, bodyB))
			{
				Contact* contact = new Contact;
				contact->bodyA = bodyA;
				contact->bodyB = bodyB;

				Vector2 direction = bodyA->position - bodyB->position;
				float distanceSqr = Vector2LengthSqr(direction);
				if (distanceSqr <= EPSILON)
				{
					direction = Vector2{ EMath::randomf(-0.05f, 0.05f), EMath::randomf(-0.05f, 0.05f) };
					distanceSqr = Vector2LengthSqr(direction);
				}

				float distance = sqrtf(distanceSqr);
				float radius = bodyA->size + bodyB->size;
				contact->depth = radius - distance;
				contact->normal = Vector2Normalize(direction);
				contact->restitution = (bodyA->restitution + bodyB->restitution) * 0.5f;
				contacts.push_back(contact);
			}
		}
	}
}

void SeparateContacts(contacts_t& contacts)
{
	for (auto contact : contacts)
	{
		float totalInverseMass = contact->bodyA->invMass + contact->bodyB->invMass;
		Vector2 separation = contact->normal * (contact->depth / totalInverseMass);
		contact->bodyA->position += separation * contact->bodyA->invMass;
		contact->bodyB->position -= separation * contact->bodyB->invMass;
	}
}

bool Intersects(Body* bodyA, Body* bodyB)
{
	float distance = Vector2Distance(bodyA->position, bodyB->position);
	float radius = bodyA->size + bodyB->size;

	return distance <= radius;
}