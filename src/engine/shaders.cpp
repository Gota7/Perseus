#include "shaders.h"

using namespace std;

map<string, AShader> Shaders::loadedShaders;

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
    loadedShaders[shaderName] = ALoadShader(useVertexShader ? vertexPath : "", useFragmentShader ? fragmentPath : "");
}

// Begin using shader.
void Shaders::BeginMShader(const string& shaderName)
{
    ABeginShaderMode(loadedShaders[shaderName]);
}

// Stop using shader.
void Shaders::StopMShader()
{
    AEndShaderMode();
}

// Unload shader.
void Shaders::UnloadMShader(const string& shaderName)
{
    AUnloadShader(loadedShaders[shaderName]);
    loadedShaders.erase(shaderName);
}