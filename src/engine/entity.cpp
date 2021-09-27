#include "entity.h"
#include "kcl.h"

using namespace std;

map<u32, StateInitFunction> Entity::behaviorInits = 
{
    { BHV_PLAYER, PlayerInitStates }
};

map<u32, pair<u32, EntityState*>> Entity::behaviorStates;

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
    kclTiles = tiles;
    kclWidth = width;
    kclHeight = height;
}

EMU Entity::GetPositionX()
{
    return FLOAT_TO_EMU(position.x);
}

EMU Entity::GetPositionY()
{
    return FLOAT_TO_EMU(position.y);
}

EMU Entity::GetVelocityX()
{
    return FLOAT_TO_EMU(velocity.x / FPS);
}

EMU Entity::GetVelocityY()
{
    return FLOAT_TO_EMU(velocity.y / FPS);
}

EMU Entity::GetAccelerationX()
{
    return FLOAT_TO_EMU(acceleration.x / FPS / FPS);
}

EMU Entity::GetAccelerationY()
{
    return FLOAT_TO_EMU(acceleration.y / FPS / FPS);
}

void Entity::SetPositionX(EMU val)
{
    position.x = EMU_TO_FLOAT(val);
}

void Entity::SetPositionY(EMU val)
{
    position.y = EMU_TO_FLOAT(val);
}

void Entity::SetVelocityX(EMU val)
{
    velocity.x = EMU_TO_FLOAT(val);
}

void Entity::SetVelocityY(EMU val)
{
    velocity.y = EMU_TO_FLOAT(val);
}

void Entity::SetMaxVelocityX(EMU val)
{
    maxVelocity.x = EMU_TO_FLOAT(val);
}

void Entity::SetMaxVelocityY(EMU val)
{
    maxVelocity.y = EMU_TO_FLOAT(val);
}

void Entity::SetAccelerationX(EMU val)
{
    acceleration.x = EMU_TO_FLOAT(val);
}

void Entity::SetAccelerationY(EMU val)
{
    acceleration.y = EMU_TO_FLOAT(val);
}

void Entity::ApplyForceX(EMU val)
{
    force.x += EMU_TO_FLOAT(val);
}

void Entity::ApplyForceY(EMU val)
{
    force.y += EMU_TO_FLOAT(val);
}

void Entity::UpdatePhysics()
{

    // Delta time.
    float dt = (float)1 / FPS;

    // Velocity.
    acceleration.x = force.x / mass;
    acceleration.y = force.y / mass;
    velocity.x += acceleration.x * dt;
    velocity.y += acceleration.y * dt;
    if (velocity.x >= maxVelocity.x)
    {
        velocity.x = maxVelocity.x;
    }
    if (velocity.x <= -maxVelocity.x)
    {
        velocity.x = -maxVelocity.x;
    }
    if (velocity.y >= maxVelocity.y)
    {
        velocity.y = maxVelocity.y;
    }
    if (velocity.y <= -maxVelocity.y)
    {
        velocity.y = -maxVelocity.y;
    }

    // To move.
    float toMoveX = velocity.x * dt;
    float toMoveY = velocity.y * dt;
    bool doMoveX = true;
    bool doMoveY = true;

    // KCL collision.
    if (canCollideWithTiles && kclTiles != nullptr)
    {

        // Get tiles to check.
        int minX, minY, maxX, maxY;
        bool checkX = true;
        bool checkY = true;
        bool movingLeft = toMoveX < 0;
        bool movingRight = toMoveX > 0;
        bool movingUp = toMoveY < 0;
        bool movingDown = toMoveY > 0;
        if (movingLeft)
        {
            minX = (int)((position.x + toMoveX) / TILE_SIZE) - 1;
            maxX = (int)(position.x / TILE_SIZE);
        }
        else if (movingRight)
        {
            minX = (int)(position.x / TILE_SIZE);
            maxX = (int)((position.x + toMoveX + boundingBox.width) / TILE_SIZE) + 1;
        }
        else
        {
            checkX = false;
        }
        if (movingUp)
        {
            minY = (int)((position.y + toMoveY) / TILE_SIZE) - 1;
            maxY = (int)(position.y / TILE_SIZE);
        }
        else if (movingDown)
        {
            minY = (int)(position.y / TILE_SIZE);
            maxY = (int)((position.y + toMoveY + boundingBox.height) / TILE_SIZE) + 1;
        }
        else
        {
            checkY = false;
        }
        
        // Check for collision.
        if (checkX)
        {
            if (movingLeft)
            {
                Ray r1, r2;
                r1.position = { position.x, position.y, 0 };
                r2.position = { position.x, position.y + boundingBox.height, 0 };
                r1.direction = { -1, 0, 0 };
                r2.direction = { -1, 0, 0 };
                for (int i = maxX - 1; i >= minX; i--)
                {
                    if (i >= 0 && i < kclWidth)
                    {
                        int tileX = i;
                        int tileY = (int)(position.y / TILE_SIZE);
                        KclResponse res1 = RaycastTile((KclTypes)((kclTiles[i + tileY * kclWidth] & 0xFFFF) - 1), tileX, tileY, r1);
                        KclResponse res2 = RaycastTile((KclTypes)((kclTiles[i + tileY * kclWidth] & 0xFFFF) - 1), tileX, tileY, r2);
                        if (res1.hit || res2.hit)
                        {
                            toMoveX = false;
                            position.x -= min(res1.dist, res2.dist);
                            break;
                        }
                    }
                }
            }
            else
            {

            }
        }
        if (checkY)
        {

        }

    }

    // Position.
    if (doMoveX)
        position.x += toMoveX;
    if (doMoveY)
        position.y += toMoveY;
    force.x = 0;
    force.y = 0;

}

void Entity::Spawn(MEntity* ent)
{
    behaviorId = BHV_PLAYER;
    if (HasState(0))
    {
        ChangeState(0);
    }
}

void Entity::Draw()
{
    DrawRectangleV(position, { TILE_SIZE, TILE_SIZE * 2 }, YELLOW);
}

void Entity::Update()
{
    DoState();
    UpdatePhysics();
}