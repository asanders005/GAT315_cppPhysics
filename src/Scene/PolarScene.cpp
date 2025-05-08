#include "PolarScene.h"
#include "Coordinates/Polar.h"

void PolarScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
}

void PolarScene::Update()
{
	// Update the polar type
	if (IsKeyPressed(KEY_ONE)) m_currentPolarType = polarType::ARCHIMEDEAN_SPIRAL;
	if (IsKeyPressed(KEY_TWO)) m_currentPolarType = polarType::CARDIOID;
	if (IsKeyPressed(KEY_THREE)) m_currentPolarType = polarType::LIMACON;
	if (IsKeyPressed(KEY_FOUR)) m_currentPolarType = polarType::ROSE;
	if (IsKeyPressed(KEY_FIVE)) m_currentPolarType = polarType::USER_DEFINED;
	// Update the size and unique value
	if (IsKeyDown(KEY_UP)) m_size += 0.1f;
	if (IsKeyDown(KEY_DOWN)) m_size -= 0.1f;
	if (IsKeyDown(KEY_RIGHT)) m_unique += 0.05f;
	if (IsKeyDown(KEY_LEFT)) m_unique -= 0.05f;
	// Update the theta value
	if (IsKeyDown(KEY_W)) m_theta += 0.1f;
	if (IsKeyDown(KEY_S)) m_theta -= 0.1f;
	// Update the rate value
	if (IsKeyDown(KEY_D)) m_rate += 0.1f;
	if (IsKeyDown(KEY_A)) m_rate -= 0.1f;
}

void PolarScene::Draw()
{
	m_camera->BeginMode();

	switch (m_currentPolarType)
	{
	case PolarScene::polarType::ARCHIMEDEAN_SPIRAL:
		DrawArchimedeanSpiral(m_size, m_unique, m_theta);
		break;
	case PolarScene::polarType::CARDIOID:
		DrawCardioid(m_size, m_theta);
		break;
	case PolarScene::polarType::LIMACON:
		DrawLimacon(m_size, m_unique, m_theta);
		break;
	case PolarScene::polarType::ROSE:
		DrawRose(m_size, (int)m_unique, m_theta);
		break;
	case PolarScene::polarType::USER_DEFINED:
		DrawLemniscate(m_size, m_theta);
		break;
	default:
		break;
	}

	m_camera->EndMode();
}

void PolarScene::DrawGUI()
{
	m_camera->BeginMode();

	std::string polarTypeName;
	std::string sizeName;
	std::string uniqueName;

	switch (m_currentPolarType)
	{
	case PolarScene::polarType::ARCHIMEDEAN_SPIRAL:
		polarTypeName = "Archimedean Spiral";
		sizeName = "Start Radius: ";
		uniqueName = "Spacing: ";
		break;
	case PolarScene::polarType::CARDIOID:
		polarTypeName = "Cardioid";
		sizeName = "Size: ";
		uniqueName = "";
		break;
	case PolarScene::polarType::LIMACON:
		polarTypeName = "Limacon";
		sizeName = "Loop: ";
		uniqueName = "Dimple: ";
		break;
	case PolarScene::polarType::ROSE:
		polarTypeName = "Rose Curve";
		sizeName = "Size: ";
		uniqueName = "Petal Count: ";
		break;
	case PolarScene::polarType::USER_DEFINED:
		polarTypeName = "Lemniscate";
		sizeName = "Size: ";
		uniqueName = "";
		break;
	default:
		break;
	}
	
	Scene::DrawText("Type: " + polarTypeName, Vector2{ -8.75f, 4.95f }, 40, WHITE);
	Scene::DrawText(sizeName + std::to_string(m_size), Vector2{ -8.75f, 4.45f }, 40, WHITE);
	if (uniqueName != "") Scene::DrawText(uniqueName + std::to_string(m_unique), Vector2{-8.75f, 3.95f}, 40, WHITE);
	Scene::DrawText("Theta: " + std::to_string(m_theta), Vector2{ -8.75f, 3.45f }, 40, WHITE);
	Scene::DrawText("Speed: " + std::to_string(m_rate), Vector2{ -8.75f, 2.95f }, 40, WHITE);

	m_camera->EndMode();
}

void PolarScene::DrawArchimedeanSpiral(float startRadius, float spacing, float theta)
{
	int currentColor = 0;
	for (float i = 0; i < theta; i += 0.2f)
	{
		float r = startRadius + (spacing * i);
		Polar p{ i /** ((float)GetTime() * m_rate)*/, r};

		Scene::DrawCircle((Vector2)p, 0.1f, m_colors[currentColor]);
		currentColor = ++currentColor % m_colors.size();
	}
}

void PolarScene::DrawCardioid(float size, float theta)
{
	int currentColor = 0;
	for (float i = -theta; i < theta; i += 0.2f)
	{
		float r = size * (1 + cosf(i));
		Polar p{ i, r };

		Scene::DrawCircle((Vector2)p, 0.1f, m_colors[currentColor]);
		currentColor = ++currentColor % m_colors.size();
	}
}

void PolarScene::DrawLimacon(float loop, float dimple, float theta)
{
	int currentColor = 0;
	for (float i = -theta; i < theta; i += 0.2f)
	{
		float r = loop + (dimple * cosf(i));
		Polar p{ i, r };

		Scene::DrawCircle((Vector2)p, 0.1f, m_colors[currentColor]);
		currentColor = ++currentColor % m_colors.size();
	}
}

void PolarScene::DrawRose(float size, int petalCount, float theta)
{
	int currentColor = 0;
	for (float i = -theta; i < theta; i += 0.2f)
	{
		float r = size * cosf(petalCount * i);
		Polar p{ i, r };

		Scene::DrawCircle((Vector2)p, 0.1f, m_colors[currentColor]);
		currentColor = ++currentColor % m_colors.size();
	}
}

void PolarScene::DrawLemniscate(float size, float theta)
{
	int currentColor = 0;
	for (float i = -theta; i < theta; i += 0.2f)
	{
		float r = size * sqrtf(sinf(2 * i));
		Polar p{ i, r };

		Scene::DrawCircle((Vector2)p, 0.1f, m_colors[currentColor]);
		currentColor = ++currentColor % m_colors.size();
	}
}
