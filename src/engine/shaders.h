#pragma once

#include "medusa.h"
#include <map>
#include <string>

// Shader utils.
struct Shaders
{

    // Data.
    static std::map<std::string, void*> loadedShaders;

    // Load shader.
    static void LoadMShader(const std::string& shaderName, bool useVertexShader = true, bool useFragmentShader = true);

    // Begin using shader.
    static void BeginMShader(const std::string& shaderName);

    // Stop using shader.
    static void StopMShader();

    // Unload shader.
    static void UnloadMShader(const std::string& shaderName);

};