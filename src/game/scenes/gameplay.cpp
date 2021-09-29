#include "gameplay.h"

void Gameplay::Initialize()
{
    camera.offset = { 0, 0 };
    camera.rotation = 0;
    camera.target = { 0, 0 };
    camera.zoom = Screen::scale;

    Tilemap::LoadTilemap(mapName);
    map = Tilemap::GetTilemap(mapName);
    e.kclBody.position = { TILE_SIZE * 12, TILE_SIZE * 9 };
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