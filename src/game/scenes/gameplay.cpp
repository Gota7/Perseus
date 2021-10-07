#include "gameplay.h"

void Gameplay::Initialize()
{
    camera.offset = AVec2(0.0f);
    camera.rotation = 0;
    camera.target = AVec2(0.0f);
    camera.zoom = Screen::scale;

    Tilemap::LoadTilemap(mapName);
    map = Tilemap::GetTilemap(mapName);
    e.kclBody.position = AVec2(TILE_SIZE * 12.0f, TILE_SIZE * 9.0f);
    e.Spawn(NULL);
    e.LoadKcl(&map->layers[LAYER_KCL].tiles[0], map->width, map->height);
}

void Gameplay::Draw()
{
    for (u8 i = 0; i < 3; i++)
    {
        map->Draw(i);
    }
    if (DEBUG_KCL)
    {
        map->Draw(LAYER_KCL);
    }
    e.Draw();
}

void Gameplay::Update()
{

    // Update entity.
    e.Update();
    
}

void Gameplay::Uninitialize()
{
    Tilemap::UnloadTilemap(mapName);
}