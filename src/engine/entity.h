#pragma once

#include "input.h"
#include "medusa.h"
#include "screenData.h"
#include "../game/entities.h"

// Forward declare.
struct Entity;

// Forward declare.
struct Entity;

// State functions.
typedef void (*StateInitFunction)(u32 behaviorId);
typedef void (*StateFunction)(Entity* ent);

// Entity state.
struct EntityState
{
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
    static std::map<u32, StateInitFunction> behaviorInits;
    static std::map<u32, std::pair<u32, EntityState*>> behaviorStates;
    int currState = -1;
    std::vector<int> cleanupStack;
    bool doInitFrame = false;
    bool doCleanupFrame = false;
    void DoState();
public:
    static void CreateStates(); 
    static void DeleteStates();
    static void RegisterStateCount(u32 behaviorId, u32 numStates);
    static void RegisterState(u32 behaviorId, u32 stateId, StateFunction init = nullptr, StateFunction main = nullptr, StateFunction cleanup = nullptr);
    bool HasState(int stateId);
    void ChangeState(int newStateId);
    int GetState();

    // Movement info.
    Vector2 position = { 0, 0 };
    Vector2 velocity = { 0, 0 };
    Vector2 acceleration = { 0, 0 };
    Vector2 force = { 0, 0 };
    Vector2 maxVelocity = { 100, 100 };
    float mass = 1;

    // Entity data.
    u32 id;
    u64 data[2];

    // Physics functions.
private:
    u32* kclTiles = nullptr;
    u32 kclWidth = 0;
    u32 kclHeight = 0;
    void UpdatePhysics();
public:
    bool canCollideWithTiles = true;
    Rectangle boundingBox = { 0, 0, TILE_SIZE, TILE_SIZE };
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