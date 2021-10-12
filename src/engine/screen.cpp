#include "screen.h"

// Defaults.
int Screen::width = (int)(SCREEN_WIDTH * DEFAULT_SCREEN_SCALE);
int Screen::height = (int)(SCREEN_HEIGHT * DEFAULT_SCREEN_SCALE);
float Screen::scale = DEFAULT_SCREEN_SCALE;
bool Screen::fullscreen = false;

void Screen::Init(std::string title)
{
    // TODO: SETTINGS!!!
    AInitWindow(width, height, title);
	ASetFPS(FPS);
}

void Screen::SetSizeW(int w)
{
    int h = (int)((float)w / SCREEN_WIDTH_TILES * SCREEN_HEIGHT_TILES);
    scale = (float)w / SCREEN_WIDTH;
    ASetWindowSize(w, h);
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
    ASetWindowSize(w, h);
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
        ASetWindowSize(width, height);
        scale = (float)width / SCREEN_WIDTH;
        Scene* s = Scene::CurrentScene();
        if (s != nullptr)
            Scene::CurrentScene()->camera.zoom = scale;
    }
    else
    {
        ASetWindowSize(AGetMonitorWidth(0), (float)AGetMonitorWidth(0) / SCREEN_WIDTH_TILES * SCREEN_HEIGHT_TILES);
        scale = (float)AGetMonitorWidth(0) / SCREEN_WIDTH;
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