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
}

void SpringScene::Update()
{
	Gui::Update();

	float dt = GetFrameTime();

	if (IsKeyPressed(KEY_SPACE))
	{
		m_world->simulate = !m_world->simulate;
	}

	if (IsKeyPressed(KEY_BACKSPACE))
	{
		m_world->DestroyAll();
	}

	if (!Gui::mouseOverGUI)
	{
		// Place Body
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Color color = ColorFromHSV(EMath::randomf(0, 360), 1.0f, 1.0f);

			Body* body = m_world->CreateBody(
				static_cast<Body::Type>(Gui::bodyType),
				m_camera->ScreenToWorld(GetMousePosition()),
				Gui::bodyMass,
				Gui::bodySize,
				color
			);

			body->damping = Gui::bodyDamping;
			body->gravityScale = Gui::bodyGravityScale;
			body->restitution = Gui::bodyRestitution;
		}

		// Select Body
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			m_selectedBody = Gui::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
		}
	}

	for (auto& body : m_world->GetBodies())
	{
		if (body->position.y < -5)
		{
			body->position.y = -5;
			body->velocity.y *= -body->restitution;
		}
		if (body->position.x < -9)
		{
			body->position.x = -9;
			body->velocity.x *= -body->restitution;
		}
		if (body->position.x > 9)
		{
			body->position.x = 9;
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
	}

	m_camera->EndMode();
}

void SpringScene::DrawGUI()
{
	Gui::Draw();
}
