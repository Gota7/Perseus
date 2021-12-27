#include <stdio.h>

#include "raylib.h"
#include "engine.h"
#include "game.h"

std::map<u32, StateInitFunction> AGameGetBehaviorInits()
{
	return
	{
    	{ BHV_PLAYER, PlayerInitStates }
	};
}

// Main method.
int main(void)
{

	// Window stuff.
	Screen::Init("Perseus: Wrath Of The Gorgons");

	// Scene setup.
	Entity::behaviorInits = AGameGetBehaviorInits();
	Entity::CreateStates();
	Gameplay gameplayScene;
	Scene::LoadScene("Gameplay", &gameplayScene);
	Scene::ChangeScene("Gameplay");
	//Shaders::LoadMShader("Crt");

	MFont fnt;
	Asset::Load(&fnt, "Perseus");

	MAudioStream stm;
	AInitAudioDevices();
	ASetAudioDefaultBufferSize(4096);
	Asset::Load(&stm, "Test");
	stm.Play();

	// Main loop.
	while (!WindowShouldClose())
	{

		// Drawing.
		BeginDrawing();
		BeginMode2D(*(Camera2D*)&Scene::GetCamera());
		//Shaders::BeginMShader("Crt");
		ClearBackground(BLACK);
		Scene::DoDraw();
		fnt.DrawString("Hello, this is Gota7!", 15, 15, COL_WHITE);
		//Shaders::StopMShader();
		EndMode2D();
		if (DEBUG_MODE)
			DrawFPS(5, 5);
		EndDrawing();

		// Updating.
		Scene::DoUpdate();
		stm.Update();

	}
	
	// Done.
	//Shaders::UnloadMShader("Crt");
	Scene::ChangeScene("");
	Entity::DeleteStates();
	CloseWindow();
	ACloseAudioDevices();
	return 0;

}