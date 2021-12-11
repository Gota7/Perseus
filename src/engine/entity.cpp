#include "entity.h"
#include "kcl.h"

using namespace std;

map<u32, StateInitFunction> Entity::behaviorInits;
map<u32, pair<u32, EntityState*>> Entity::behaviorStates;
map<u32, InitCleanupFunction> Entity::inits;
map<u32, InitCleanupFunction> Entity::cleanups;

void Entity::CreateStates()
{
    for (u32 i = 0; i < BHV_COUNT; i++)
    {
        if (behaviorInits.find(i) != behaviorInits.end())
        {
            behaviorInits[i](i);
        }
    }
}

void Entity::DeleteStates()
{
    for (int i = 0; i < BHV_COUNT; i++)
    {
        if (behaviorStates.find(i) != behaviorStates.end())
        {
            delete[] behaviorStates[i].second;
        }
    }
}

void Entity::RegisterInit(u32 behaviorId, InitCleanupFunction init)
{
    inits[behaviorId] = init;
}

void Entity::RegisterCleanup(u32 behaviorId, InitCleanupFunction cleanup)
{
    cleanups[behaviorId] = cleanup;
}

void Entity::RegisterStateCount(u32 behaviorId, u32 numStates)
{
    behaviorStates[behaviorId].first = numStates;
    behaviorStates[behaviorId].second = new EntityState[numStates];
}

void Entity::RegisterState(u32 behaviorId, u32 stateId, StateFunction init, StateFunction main, StateFunction cleanup)
{
    EntityState* s = &behaviorStates[behaviorId].second[stateId];
    s->init = init;
    s->main = main;
    s->cleanup = cleanup;
}

bool Entity::HasState(int stateId)
{
    return stateId < behaviorStates[behaviorId].first && stateId > -2;
}

void Entity::ChangeState(int state)
{
    EntityState* states = behaviorStates[behaviorId].second;
    if (currState != -1 && states[currState].cleanup != NULL) { doCleanupFrame = true; cleanupStack.push_back(currState); }
    currState = state;
    if (currState != -1 && states[currState].init != NULL) { doInitFrame = true; }
}

int Entity::GetState()
{
    return currState;
}

void Entity::DoState()
{
    EntityState* states = behaviorStates[behaviorId].second;
    if (doCleanupFrame)
    {
        while (cleanupStack.size() > 0)
        {
            states[cleanupStack[cleanupStack.size() - 1]].cleanup(this);
            cleanupStack.pop_back();
        }
        doCleanupFrame = false;
    }
    if (doInitFrame)
    {
        states[currState].init(this);
        doInitFrame = false;
        return;
    }
    if (currState == -1 || states[currState].main == NULL)
        return;
    states[currState].main(this);
}

void Entity::LoadKcl(u32* tiles, u32 width, u32 height)
{
    kclBody.kclTiles = tiles;
    kclBody.kclWidth = width;
    kclBody.kclHeight = height;
}

EMU Entity::GetPositionX()
{
    return FLOAT_TO_EMU(kclBody.position.x);
}

EMU Entity::GetPositionY()
{
    return FLOAT_TO_EMU(kclBody.position.y);
}

EMU Entity::GetVelocityX()
{
    return FLOAT_TO_EMU(kclBody.velocity.x / FPS);
}

EMU Entity::GetVelocityY()
{
    return FLOAT_TO_EMU(kclBody.velocity.y / FPS);
}

EMU Entity::GetAccelerationX()
{
    return FLOAT_TO_EMU(kclBody.acceleration.x / FPS / FPS);
}

EMU Entity::GetAccelerationY()
{
    return FLOAT_TO_EMU(kclBody.acceleration.y / FPS / FPS);
}

void Entity::SetPositionX(EMU val)
{
    kclBody.position.x = EMU_TO_FLOAT(val);
}

void Entity::SetPositionY(EMU val)
{
    kclBody.position.y = EMU_TO_FLOAT(val);
}

void Entity::SetVelocityX(EMU val)
{
    kclBody.velocity.x = EMU_TO_FLOAT(val);
}

void Entity::SetVelocityY(EMU val)
{
    kclBody.velocity.y = EMU_TO_FLOAT(val);
}

void Entity::SetMaxVelocityX(EMU val)
{
    kclBody.maxVelocity.x = EMU_TO_FLOAT(val);
}

void Entity::SetMaxVelocityY(EMU val)
{
    kclBody.maxVelocity.y = EMU_TO_FLOAT(val);
}

void Entity::SetAccelerationX(EMU val)
{
    kclBody.acceleration.x = EMU_TO_FLOAT(val);
}

void Entity::SetAccelerationY(EMU val)
{
    kclBody.acceleration.y = EMU_TO_FLOAT(val);
}

void Entity::ApplyForceX(EMU val)
{
    kclBody.force.x += EMU_TO_FLOAT(val);
}

void Entity::ApplyForceY(EMU val)
{
    kclBody.force.y += EMU_TO_FLOAT(val);
}

void Entity::UpdatePhysics()
{

    // Update body.
    float dt = AGetFrameTime();
    kclBody.Update(dt);

}

void Entity::Spawn(MEntity* ent)
{
    behaviorId = BHV_PLAYER;
    id = behaviorId;
    if (inits.find(behaviorId) != inits.end())
    {
        inits[behaviorId](this);
    }
    if (HasState(0))
    {
        ChangeState(0);
    }
}

void Entity::Draw()
{

    // Draw KCL.
    if (DEBUG_KCL)
    {
        ADrawRectangle(
            kclBody.position.x + kclBody.boundsOffset.x,
            kclBody.position.y + kclBody.boundsOffset.y,
            kclBody.kclSize.x, kclBody.kclSize.y,
            AColor::ChangeAlpha(COL_YELLOW, (u8)(0.7f * 255)));
    }

}

void Entity::Update()
{
    DoState();
    UpdatePhysics();
}

void Entity::Kill()
{
    if (cleanups.find(id) != cleanups.end())
    {
        cleanups[id](this);
    }    
}