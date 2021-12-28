#include <stdio.h>

#include "raylib.h"
#include "engine.h"
#include "game.h"

// Behaviors.
enum Behaviors : u32
{
    BHV_DRAW_ONLY,
    BHV_DRAW_AND_COLLIDE,
    BHV_COLLIDE_ONLY,
    BHV_PLAYER,
    BHV_PLAYER_SPAWNPOINT,
    BHV_WARP,
    BHV_COUNT,
    BHV_NONE = 0xFFFFFFFF
};

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

	AInitAudioDevices();
	ASetAudioDefaultBufferSize(MAudioStream::BLOCK_SIZE);
	MAudioWave wav;
	Asset::Load(&wav, "GotaEh");

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
		wav.Update();
		if (AButtonPressed(AInputButton::BUTTON_ATTACK)) wav.Play();

	}
	
	// Done.
	//Shaders::UnloadMShader("Crt");
	Scene::ChangeScene("");
	Entity::DeleteStates();
	CloseWindow();
	ACloseAudioDevices();
	return 0;

}