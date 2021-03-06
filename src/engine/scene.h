#pragma once

#include "backend.h"
#include "camera.h"
#include <map>
#include <string>

// Game scene.
struct Scene
{

    // Private data.
private:
	static Scene* currentScene;
	static std::map<std::string, Scene*> loadedScenes;


	// Public members.
public:
	static AVec2 BGPos;
	ACam camera;
    
    // Initialize scene.
    virtual void Initialize() {}

    // Draw scene.
    virtual void Draw() {}

    // Update scene. Runs 60 times every second.
    virtual void Update() {}

    // Uninitialize.
    virtual void Uninitialize() {}

    // To execute.
	static void ChangeScene(const std::string& name);
	static void DoDraw();
	static void DoUpdate();
	static void LoadScene(const std::string& name, Scene *scene);
	static Scene* CurrentScene();
	static ACam &GetCamera();

};