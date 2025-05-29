#include "SpringScene.h"
#include "Objects/Body.h"
#include "Utility/MathUtils.h"
#include "Physics/Gravitation.h"
#include "GUI/Gui.h"

#include "raymath.h"
#include "raygui.h"
#include <time.h>



void SpringScene::Initialize()
{
	srand(time(0));

	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();

	GUI::Initialize();
}

void SpringScene::Update()
{
	GUI::Update();

	float dt = GetFrameTime();

	if (IsKeyPressed(KEY_SPACE))
	{
		m_world->simulate = !m_world->simulate;
	}

	if (IsKeyPressed(KEY_BACKSPACE))
	{
		m_world->DestroyAll();
	}

	if (!GUI::mouseOverGUI)
	{
		// Place Body
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_CONTROL)))
		{
			Color color = ColorFromHSV(EMath::randomf(0, 360), 1.0f, 1.0f);

			Body* body = m_world->CreateBody(
				static_cast<Body::Type>(GUI::bodyTypeActive),
				m_camera->ScreenToWorld(GetMousePosition()),
				GUI::massValue,
				GUI::sizeValue,
				color
			);

			body->damping = GUI::dampingValue;
			body->gravityScale = GUI::gravityScaleValue;
			body->restitution = GUI::restitutionValue;

			//body->ApplyForce(EMath::randomOnUnitCircle() * EMath::randomf(0.5f, 1.0f) * 5.0f, Body::ForceMode::Velocity);
		}

		// Select Body
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			m_selectedBody = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
		}
		if (m_selectedBody)
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_LEFT_CONTROL))
			{
				if (m_selectedBody->type == Body::Type::Dynamic)
				{
					Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
					Spring::ApplyForce(position, *m_selectedBody, 0.2f, 20.0f);
				}
			}
			else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
				m_connectBody = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
			}
			else
			{
				if (m_selectedBody && m_connectBody)
				{
					float distance = Vector2Distance(m_selectedBody->position, m_connectBody->position);
					m_world->CreateSpring(m_selectedBody, m_connectBody, distance, GUI::stiffnessValue, GUI::dampingValue);
				}
				m_selectedBody = nullptr;
				m_connectBody = nullptr;
			}
		}
	}

	AABB worldAABB = m_camera->GetAABB();
	for (auto& body : m_world->GetBodies())
	{
		AABB aabb = body->GetAABB();

		if (aabb.min().y < worldAABB.min().y)
		{
			float overlap = worldAABB.min().y - aabb.min().y;
			body->position.y += 2 * overlap;
			body->velocity.y *= -body->restitution;
		}
		else if (aabb.max().y > worldAABB.max().y)
		{
			float overlap = worldAABB.max().y - aabb.max().y;
			body->position.y += 2 * overlap;
			body->velocity.y *= -body->restitution;
		}

		if (aabb.min().x < worldAABB.min().x)
		{
			float overlap = worldAABB.min().x - aabb.min().x;
			body->position.x += 2 * overlap;
			body->velocity.x *= -body->restitution;
		}
		else if (aabb.max().x > worldAABB.max().x)
		{
			float overlap = worldAABB.max().x - aabb.max().x;
			body->position.x += 2 * overlap;
			body->velocity.x *= -body->restitution;
		}
	}
}

void SpringScene::FixedUpdate()
{
	m_world->Step(fixedTimeStep);
}

void SpringScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGRAY);

	m_world->Draw(*this);
	if (m_selectedBody)
	{
		DrawCircleLine(m_selectedBody->position, m_selectedBody->size, YELLOW, 5);
		if (m_connectBody)
		{
			DrawCircleLine(m_connectBody->position, m_connectBody->size, YELLOW, 5);
			DrawLine(m_selectedBody->position, m_connectBody->position, 3, GREEN);
		}
		else
		{
			DrawLine(m_selectedBody->position, m_camera->ScreenToWorld(GetMousePosition()), 3, RED);
		}
	}

	m_camera->EndMode();
}

void SpringScene::DrawGUI()
{
	GUI::Draw();
}
