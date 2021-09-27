#include "screen.h"

// Defaults.
int Screen::width = (int)(SCREEN_WIDTH * DEFAULT_SCREEN_SCALE);
int Screen::height = (int)(SCREEN_HEIGHT * DEFAULT_SCREEN_SCALE);
float Screen::scale = DEFAULT_SCREEN_SCALE;
bool Screen::fullscreen = false;

void Screen::Init()
{
    // TODO: SETTINGS!!!
    InitWindow(width, height, "Perseus: Wrath Of The Gorgons");
	SetTargetFPS(FPS);
}

void Screen::SetSizeW(int w)
{
    int h = (int)((float)w / SCREEN_WIDTH_TILES * SCREEN_HEIGHT_TILES);
    scale = (float)w / SCREEN_WIDTH;
    SetWindowSize(w, h);
    width = w;
    height = h;
    Scene* s = Scene::CurrentScene();
    if (s != nullptr)
        Scene::CurrentScene()->camera.zoom = scale;
}

void Screen::SetSizeH(int h)
{
    int w = (int)((float)h / SCREEN_HEIGHT_TILES * SCREEN_WIDTH_TILES);
    scale = (float)w / SCREEN_WIDTH;
    SetWindowSize(w, h);
    width = w;
    height = h;
    Scene* s = Scene::CurrentScene();
    if (s != nullptr)
        Scene::CurrentScene()->camera.zoom = scale;
}

void Screen::Fullscreen()
{
    if (fullscreen)
    {
        Fullscreen();
        SetWindowSize(width, height);
        scale = (float)width / SCREEN_WIDTH;
        Scene* s = Scene::CurrentScene();
        if (s != nullptr)
            Scene::CurrentScene()->camera.zoom = scale;
    }
    else
    {
        SetWindowSize(GetMonitorWidth(0), (float)GetMonitorWidth(0) / SCREEN_WIDTH_TILES * SCREEN_HEIGHT_TILES);
        scale = (float)GetMonitorWidth(0) / SCREEN_WIDTH;
        Fullscreen();
        Scene* s = Scene::CurrentScene();
        if (s != nullptr)
            Scene::CurrentScene()->camera.zoom = scale;
    }
}

void Screen::Save()
{
    // TODO!!!
}