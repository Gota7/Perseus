#include "shaders.h"

using namespace std;

map<string, Shader> Shaders::loadedShaders;

// Load shader.
void Shaders::LoadMShader(const string& shaderName, bool useVertexShader, bool useFragmentShader)
{
    string vertexPath = "";
    string fragmentPath = "";
    if (useVertexShader)
    {
        vertexPath = Asset::assetFolder + "Shd/" + shaderName + ".mshv";
    }
    if (useFragmentShader)
    {
        fragmentPath = Asset::assetFolder + "Shd/" + shaderName + ".mshf";
    }
    loadedShaders[shaderName] = LoadShader(useVertexShader ? vertexPath.c_str() : NULL, useFragmentShader ? fragmentPath.c_str() : NULL);
}

// Begin using shader.
void Shaders::BeginMShader(const string& shaderName)
{
    BeginShaderMode(loadedShaders[shaderName]);
}

// Stop using shader.
void Shaders::StopMShader()
{
    EndShaderMode();
}

// Unload shader.
void Shaders::UnloadMShader(const string& shaderName)
{
    UnloadShader(loadedShaders[shaderName]);
    loadedShaders.erase(shaderName);
}