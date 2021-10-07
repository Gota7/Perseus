#include <stdio.h>

#include "raylib.h"
#include "engine.h"
#include "game.h"

// Main method.
int main(void)
{

	// Window stuff.
	Screen::Init();
	int width = 1024;

	// Scene setup.
	Entity::CreateStates();
	Gameplay gameplayScene;
	Scene::LoadScene("Gameplay", &gameplayScene);
	Scene::ChangeScene("Gameplay");
	//Shaders::LoadMShader("Crt");

	// Main loop.
	while (!WindowShouldClose())
	{

		// Drawing.
		BeginDrawing();
		BeginMode2D(*(Camera2D*)&Scene::GetCamera());
		//Shaders::BeginMShader("Crt");
		ClearBackground(BLACK);
		Scene::DoDraw();	
		//Shaders::StopMShader();
		EndMode2D();
		if (DEBUG_MODE)
			DrawFPS(5, 5);
		EndDrawing();

		// Updating.
		Scene::DoUpdate();

	}
	
	// Done.
	//Shaders::UnloadMShader("Crt");
	Scene::ChangeScene("");
	Entity::DeleteStates();
	CloseWindow();
	return 0;

}