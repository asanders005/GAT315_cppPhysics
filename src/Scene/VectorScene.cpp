#include "VectorScene.h"
#include "Objects/Body.h"
#include "Utility/MathUtils.h"
#include "Physics/Gravitation.h"

#include "raymath.h"
#include "raygui.h"
#include <time.h>

#define GUI_DATA(data) TextFormat("%0.2f", data)

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
	if (!mouseOverGUI && (IsMouseButtonPressed(0) || IsMouseButtonDown(1)))
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

			body->velocity = Vector2{ x, y } *EMath::randomf(2.0f, 10.0f);
			body->damping = m_bodyDamping;

			body->gravityScale = m_bodyGravityScale;
			body->restitution = m_bodyRestitution;
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
	ApplyGravitation(m_world->GetBodies(), m_gravitation);
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
	mouseOverGUI = PhysicsWindowActive && CheckCollisionPointRec(GetMousePosition(), Rectangle{ 48, 48, 280, 576 });

	if (TypeDropdownEditMode) GuiLock();

	if (PhysicsWindowActive)
	{
		PhysicsWindowActive = !GuiWindowBox(Rectangle{ 48, 48, 296, 576 }, "Physics Settings");

		GuiGroupBox(Rectangle{ 64, 88, 264, 80 }, "World");
		GuiSlider(Rectangle{ 160, 104, 120, 16 }, "Gravity", GUI_DATA(World::gravity.y), &World::gravity.y, -20, 20);
		GuiSlider(Rectangle{ 160, 136, 120, 16 }, "Gravitation", GUI_DATA(m_gravitation), &m_gravitation, 0, 20);
		GuiGroupBox(Rectangle{ 64, 184, 264, 216 }, "Bodies");
		GuiLabel(Rectangle{ 128, 200, 32, 24 }, "Type");
		GuiSlider(Rectangle{ 160, 240, 120, 16 }, "Size", GUI_DATA(m_bodySize), &m_bodySize, 0.05f, 0.5f);
		GuiSlider(Rectangle{ 160, 272, 120, 16 }, "Mass", GUI_DATA(m_bodyMass), &m_bodyMass, 0, 10);
		GuiSlider(Rectangle{ 160, 304, 120, 16 }, "Gravity Scale", GUI_DATA(m_bodyGravityScale), &m_bodyGravityScale, 0.1f, 5);
		GuiSlider(Rectangle{ 160, 336, 120, 16 }, "Damping", GUI_DATA(m_bodyDamping), &m_bodyDamping, 0, 1);
		GuiSlider(Rectangle{ 160, 368, 120, 16 }, "Restitution", GUI_DATA(m_bodyRestitution), &m_bodyRestitution, 0, 1);
		if (GuiDropdownBox(Rectangle{ 160, 200, 120, 24 }, "STATIC;KINEMATIC;DYNAMIC", &m_bodyType, TypeDropdownEditMode)) TypeDropdownEditMode = !TypeDropdownEditMode;
	}

	GuiUnlock();
}
