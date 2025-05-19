#include "VectorScene.h"
#include "Objects/Body.h"
#include "Utility/MathUtils.h"
#include "Physics/Gravitation.h"
#include "GUI/Gui.h"

#include "raymath.h"
#include "raygui.h"
#include <time.h>



void VectorScene::Initialize()
{
	srand(time(0));

	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();
}

void VectorScene::Update()
{
	Gui::Update();

	if (IsKeyPressed(KEY_X))
	{
		m_isPaused = !m_isPaused;
	}

	if (m_isPaused) return;

	float dt = GetFrameTime();

	if (IsKeyPressed(KEY_SPACE))
	{
		m_world->DestroyAll();
	}

	if (IsKeyPressed(KEY_C))
	{
		m_colorType = static_cast<ColorType>(((int)m_colorType + 1) % (int)ColorType::End);
	}

	if (IsKeyPressed(KEY_V))
	{
		m_fireworkType = static_cast<FireworkType>(((int)m_fireworkType + 1) % (int)FireworkType::End);
	}

	float theta = EMath::randomf(EMath::DegToRad(360));
	if (!Gui::mouseOverGUI && (IsMouseButtonPressed(0) || IsMouseButtonDown(1)))
	{
		Color color = ColorFromHSV(EMath::randomf(0, 360), 1.0f, 1.0f);
		for (int i = 0; i < 100; i++)
		{
			if (m_colorType == ColorType::Gradient)
			{
				color = ColorFromHSV(ColorToHSV(color).x + 1, 1.0f, 1.0f);
			}
			else if (m_colorType == ColorType::Multi)
			{
				color = ColorFromHSV(EMath::randomf(0, 360), 1.0f, 1.0f);
			}

			Body* body = m_world->CreateBody(
				static_cast<Body::Type>(Gui::bodyType),
				m_camera->ScreenToWorld(GetMousePosition()),
				Gui::bodyMass,
				Gui::bodySize,
				color
			);

			float offset = (m_fireworkType == FireworkType::Cone) ? EMath::DegToRad(EMath::randomf(-45, 45)) : EMath::DegToRad(EMath::randomf(-180, 180));
			float x = cosf(theta + offset);
			float y = sinf(theta + offset);

			body->velocity = Vector2{ x, y } *EMath::randomf(2.0f, 10.0f);
			body->damping = Gui::bodyDamping;

			body->gravityScale = Gui::bodyGravityScale;
			body->restitution = Gui::bodyRestitution;
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

void VectorScene::FixedUpdate()
{
	if (m_isPaused) return;
	m_world->Step(fixedTimeStep);
}

void VectorScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGRAY);

	m_world->Draw(*this);

	m_camera->EndMode();
}

void VectorScene::DrawGUI()
{
	Gui::Draw();
}
