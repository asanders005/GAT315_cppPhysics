/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "Scene/TrigScene.h"
#include "Scene/PolarScene.h"
#include "Scene/VectorScene.h"
#include "Scene/SpringScene.h"

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	int screenWidth = 1280;
	int screenHeight = 720;
	InitWindow(screenWidth, screenHeight, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	//Scene* scene = new TrigScene("Trig Scene", screenWidth, screenHeight);
	//Scene* scene = new PolarScene("Polar Scene", screenWidth, screenHeight);
	//Scene* scene = new VectorScene("Vector Scene", screenWidth, screenHeight);
	Scene* scene = new SpringScene("Spring Scene", screenWidth, screenHeight);
	scene->Initialize();

	SetTargetFPS(60);

	float timeAccum = 0;
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		scene->Update();
		timeAccum += std::min(GetFrameTime(), 0.5f);
		while (timeAccum >= Scene::fixedTimeStep)
		{
			scene->FixedUpdate();
			timeAccum -= Scene::fixedTimeStep;
		}
		scene->BeginDraw();
		scene->Draw();
		scene->DrawGUI();
		scene->EndDraw();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
