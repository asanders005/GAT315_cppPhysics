#include "VectorScene.h"
#include "Objects/Body.h"
#include "Utility/MathUtils.h"

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
	if (IsMouseButtonPressed(0) || IsMouseButtonDown(1))
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
				m_bodyType,
				m_camera->ScreenToWorld(GetMousePosition()),
				m_bodyMass,
				m_bodySize,
				color
			);

			float offset = (m_fireworkType == FireworkType::Cone) ? EMath::DegToRad(EMath::randomf(-45, 45)) : EMath::DegToRad(EMath::randomf(-180, 180));
			float x = cosf(theta + offset);
			float y = sinf(theta + offset);

			body->velocity = Vector2{ x, y } * EMath::randomf(2.0f, 10.0f);
			body->damping = m_bodyDamping;

			body->gravityScale = m_bodyGravityScale;
			body->restitution = EMath::randomf(0.5f, 1.0f);
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
	if (TypeDropdownEditMode) GuiLock();

	if (PhysicsWindowActive)
	{
		PhysicsWindowActive = !GuiWindowBox(Rectangle{ 48, 48, 264, 576 }, "Physics Settings");
	}
	GuiGroupBox(Rectangle{ 64, 88, 232, 48 }, "World");
	GuiSlider(Rectangle{ 160, 104, 120, 16 }, "Gravity", NULL, &World::gravity.y, -20, 20);
	GuiGroupBox(Rectangle{ 64, 152, 232, 184 }, "Bodies");
	GuiLabel(Rectangle{ 128, 168, 32, 24 }, "Type");
	GuiSlider(Rectangle{ 160, 208, 120, 16 }, "Size", NULL, &m_bodySize, 0, 0.5f);
	GuiSlider(Rectangle{ 160, 240, 120, 16 }, "Mass", NULL, &m_bodyMass, 0, 100);
	GuiSlider(Rectangle{ 160, 272, 120, 16 }, "Gravity Scale", NULL, &m_bodyGravityScale, 0.1f, 10);
	GuiSlider(Rectangle{ 160, 304, 120, 16 }, "Damping", NULL, &m_bodyDamping, 0, 1);
	if (GuiDropdownBox(Rectangle{ 160, 168, 120, 24 }, "STATIC;KINEMATIC;DYNAMIC", &m_bodyType, TypeDropdownEditMode)) TypeDropdownEditMode = !TypeDropdownEditMode;

	GuiUnlock();
}
