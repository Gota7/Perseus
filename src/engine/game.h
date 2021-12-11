#pragma once
#include "entity.h"
#include <map>

/*

    Declares all the functions that must be implemented by the game using Athens Engine.

*/

// Pre-defined functions.
void AGameInit(std::string title);
void AGameRun();

// To implement.
void AGameOnInit();
void AGameOnDraw();
void AGameOnUpdate();
std::map<u32, StateInitFunction> AGameGetBehaviorInits();