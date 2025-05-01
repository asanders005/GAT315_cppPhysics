#include "trig_scene.h"

void TrigScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
}

void TrigScene::Update()
{
}

void TrigScene::Draw()
{
	m_camera->BeginMode();

	DrawCircleGradient(0, 0, 250, PINK, PURPLE);

	m_camera->EndMode();
}

void TrigScene::DrawGUI()
{
}