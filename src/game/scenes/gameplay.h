#pragma once

#include "../../engine.h"
#include "../../types.h"

// Main game play.
struct Gameplay : public Scene
{

    std::string mapName = "TitleScreen";
    Tilemap* map;
    Entity e;

    // Scene stuff.
    void Initialize();
    void Draw();
    void Update();
    void Uninitialize();

};