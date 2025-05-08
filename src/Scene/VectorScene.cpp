#include "VectorScene.h"
#include "Objects/Body.h"
#include "Utility/MathUtils.h"

#include "raymath.h"
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
	float dt = GetFrameTime();

	float theta = EMath::randomf(EMath::DegToRad(360));
	if (IsMouseButtonPressed(0))
	{
		for (int i = 0; i < 100; i++)
		{
			Body* body = m_world->CreateBody(
				m_camera->ScreenToWorld(GetMousePosition()),
				EMath::randomf(0.005f, 0.15f),
				ColorFromHSV(EMath::randomf(0, 360), 1.0f, 1.0f)
			);

			float offset = EMath::DegToRad(EMath::randomf(-45, 45));
			float x = cosf(theta + offset);
			float y = sinf(theta + offset);
			body->velocity = Vector2{ x, y } * EMath::randomf(2.0f, 10.0f);
		}
	}

	m_world->Step(dt);
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
}
