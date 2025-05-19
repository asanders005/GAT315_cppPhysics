#include "Gui.h"

#define GUI_DATA(data) TextFormat("%0.2f", data)

void Gui::Update()
{
	mouseOverGUI = PhysicsWindowActive && CheckCollisionPointRec(GetMousePosition(), Rectangle{ 48, 48, 280, 576 });
	if (IsKeyPressed(KEY_TAB)) PhysicsWindowActive = !PhysicsWindowActive;
}

void Gui::Draw()
{
	if (TypeDropdownEditMode) GuiLock();

	if (PhysicsWindowActive)
	{
		PhysicsWindowActive = !GuiWindowBox(Rectangle{ 48, 48, 296, 576 }, "Physics Settings");

		GuiGroupBox(Rectangle{ 64, 88, 264, 80 }, "World");
		GuiSlider(Rectangle{ 160, 104, 120, 16 }, "Gravity", GUI_DATA(World::gravity.y), &World::gravity.y, -20, 20);
		GuiSlider(Rectangle{ 160, 136, 120, 16 }, "Gravitation", GUI_DATA(World::gravitation), &World::gravitation, 0, 20);
		GuiGroupBox(Rectangle{ 64, 184, 264, 216 }, "Bodies");
		GuiLabel(Rectangle{ 128, 200, 32, 24 }, "Type");
		GuiSlider(Rectangle{ 160, 240, 120, 16 }, "Size", GUI_DATA(bodySize), &bodySize, 0.05f, 2.0f);
		GuiSlider(Rectangle{ 160, 272, 120, 16 }, "Mass", GUI_DATA(bodyMass), &bodyMass, 0, 10);
		GuiSlider(Rectangle{ 160, 304, 120, 16 }, "Gravity Scale", GUI_DATA(bodyGravityScale), &bodyGravityScale, 0.1f, 5);
		GuiSlider(Rectangle{ 160, 336, 120, 16 }, "Damping", GUI_DATA(bodyDamping), &bodyDamping, 0, 1);
		GuiSlider(Rectangle{ 160, 368, 120, 16 }, "Restitution", GUI_DATA(bodyRestitution), &bodyRestitution, 0, 1);
		if (GuiDropdownBox(Rectangle{ 160, 200, 120, 24 }, "DYNAMIC;KINEMATIC;STATIC", &bodyType, TypeDropdownEditMode)) TypeDropdownEditMode = !TypeDropdownEditMode;
	}

	GuiUnlock();
}

Body* Gui::GetBodyIntersect(const Vector2& position, bodies_t& bodies, const SceneCamera& camera)
{
	for (auto& body : bodies)
	{
		if (CheckCollisionPointCircle(position, body->position, body->size))
		{
			return body;
		}
	}

	return nullptr;
}
