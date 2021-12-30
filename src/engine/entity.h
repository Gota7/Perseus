#pragma once

#include "types.h"

// Forward declare.
struct Entity;

// State functions.
typedef void (*StateInitFunction)(u32 behaviorId);
typedef void (*StateFunction)(Entity* ent);
typedef void (*InitCleanupFunction)(Entity* ent);

#include "backend.h"
#include "input.h"
#include "medusa.h"
#include "screenData.h"
#include "kcl.h"
#include "../game/entities.h"

// Entity state.
struct EntityState
{
    void (*kclInit)(Entity* ent) = nullptr;
    void (*init)(Entity* ent) = nullptr;
    void (*main)(Entity* ent) = nullptr;
    void (*cleanup)(Entity* ent) = nullptr;
};

// Entity.
struct Entity
{

    // State data.
private:
    u32 behaviorId;
    static std::map<u32, InitCleanupFunction> inits;
    static std::map<u32, InitCleanupFunction> cleanups;
    static std::map<u32, std::pair<u32, EntityState*>> behaviorStates;
    int currState = -1;
    std::vector<int> cleanupStack;
    bool doInitFrame = false;
    bool doCleanupFrame = false;
    void DoState();
public:
    static std::map<u32, StateInitFunction> behaviorInits;
    static void CreateStates(); 
    static void DeleteStates();
    static void RegisterInit(u32 behaviorId, InitCleanupFunction init);
    static void RegisterCleanup(u32 behaviorId, InitCleanupFunction cleanup);
    static void RegisterStateCount(u32 behaviorId, u32 numStates);
    static void RegisterState(u32 behaviorId, u32 stateId, StateFunction init = nullptr, StateFunction main = nullptr, StateFunction cleanup = nullptr);
    bool HasState(int stateId);
    void ChangeState(int newStateId);
    int GetState();

    // Body.
    KclBody kclBody;

    // Entity data.
    u32 id;
    u8 data[16];
    void* extData; // For individual entities to take advantage of storing extra data.

    // Physics functions.
private:
    void UpdatePhysics();
public:
    void LoadKcl(u32* tiles, u32 width, u32 height);
    EMU GetPositionX();
    EMU GetPositionY();
    EMU GetVelocityX();
    EMU GetVelocityY();
    EMU GetAccelerationX();
    EMU GetAccelerationY();
    void SetPositionX(EMU val);
    void SetPositionY(EMU val);
    void SetVelocityX(EMU val);
    void SetVelocityY(EMU val);
    void SetMaxVelocityX(EMU val);
    void SetMaxVelocityY(EMU val);
    void SetAccelerationX(EMU val);
    void SetAccelerationY(EMU val);
    void ApplyForceX(EMU val);
    void ApplyForceY(EMU val);

    // Main functions.
    void Spawn(MEntity* ent);
    void Draw();
    void Update();
    void Kill();

};