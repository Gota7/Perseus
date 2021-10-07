#include "scene.h"

using namespace std;

Scene *Scene::currentScene = nullptr;
map<string, Scene *> Scene::loadedScenes;

// BG Position.
AVec2 Scene::BGPos = AVec2(0.0f);

void Scene::ChangeScene(const string& name)
{
    if (currentScene != nullptr)
    {
        currentScene->Uninitialize();
    }
    if (name == "")
        return;
    currentScene = loadedScenes[name];
    currentScene->Initialize();
}

void Scene::DoDraw()
{
    if (currentScene == nullptr)
        return;
    currentScene->Draw();
}

void Scene::DoUpdate()
{
    if (currentScene == nullptr)
        return;
    currentScene->Update();
}

void Scene::LoadScene(const string& name, Scene *scene)
{
    loadedScenes[name] = scene;
}

Scene* Scene::CurrentScene()
{
    return currentScene;
}

ACam &Scene::GetCamera()
{
    return currentScene->camera;
}