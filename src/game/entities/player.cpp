#include "player.h"

enum PlayerStates
{
    PLAYER_ST_IDLE,
    PLAYER_ST_MOVE,
    PLAYER_ST_FALL
};

void PlayerInitStates(u32 behaviorId)
{
    Entity::RegisterKCLInit(behaviorId, PlayerInitKCL);
    Entity::RegisterStateCount(behaviorId, 3);
    Entity::RegisterState(behaviorId, PLAYER_ST_IDLE, PlayerIdleInit, PlayerIdleMain);
    Entity::RegisterState(behaviorId, PLAYER_ST_MOVE, PlayerMoveInit, PlayerMoveMain);
    Entity::RegisterState(behaviorId, PLAYER_ST_FALL, PlayerFallInit, PlayerFallMain, PlayerFallCleanup);
}

void PlayerInitKCL(Entity* ent)
{
    ent->kclBody.InitBounds({ 0, 0 }, { TILE_SIZE, TILE_SIZE * 2 });
}

void PlayerIdleInit(Entity* ent)
{
    ent->SetMaxVelocityX(0);
    ent->SetMaxVelocityY(0);
}

void PlayerIdleMain(Entity* ent)
{

    // Jump.
    if (Input::Pressed(BUTTON_JUMP))
    {
        ent->SetMaxVelocityY(abs(PLAYER_JUMP));
        ent->SetVelocityY(PLAYER_JUMP);
        ent->ChangeState(PLAYER_ST_FALL);
        return;
    }

    // Move.
    if (Input::Down(BUTTON_LEFT) || Input::Down(BUTTON_RIGHT))
    {
        ent->ChangeState(PLAYER_ST_MOVE);
    }
    
}

void PlayerMoveInit(Entity* ent)
{
    ent->SetMaxVelocityX(PLAYER_MOVE_SPEED);
    ent->SetMaxVelocityY(0);
}

void PlayerMoveMain(Entity* ent)
{

    // Jump.
    if (Input::Pressed(BUTTON_JUMP))
    {
        ent->SetMaxVelocityY(abs(PLAYER_JUMP));
        ent->SetVelocityY(PLAYER_JUMP);
        ent->ChangeState(PLAYER_ST_FALL);
        return;
    }

    // Movement direction.
    int moveDir = 0;
    if (ent->kclBody.velocity.x < 0)
        moveDir = 1;
    if (ent->kclBody.velocity.x > 0)
        moveDir = 2;
        
    // Get input.
    EMU input = 0;
    if (Input::Down(BUTTON_LEFT))
        input -= PLAYER_MOVE_ACCEL;
    if (Input::Down(BUTTON_RIGHT))
        input += PLAYER_MOVE_ACCEL;

    // Use input.
    if (input == 0)
    {

        // Not moving with no direction.
        if (moveDir == 0)
        {
            ent->ChangeState(PLAYER_ST_IDLE);
        }

        // Going left but need to slow down to stop.
        else if (moveDir == 1)
        {
            if (ent->kclBody.velocity.x > EMU_TO_FLOAT(-0x500))
            {
                ent->SetVelocityX(0);
            }
            else
            {
                ent->ApplyForceX(PLAYER_MOVE_DEACCEL);
            }
        }

        // Going right but need to slow down to stop.
        else
        {
            if (ent->kclBody.velocity.x < EMU_TO_FLOAT(0x500))
            {
                ent->SetVelocityX(0);
            }
            else
            {
                ent->ApplyForceX(-PLAYER_MOVE_DEACCEL);
            }
        }

    }
    else if (input < 0)
    {

        // Start moving left.
        if (moveDir == 0)
        {
            ent->ApplyForceX(input);
        }

        // Maintain speed.
        else if (moveDir == 1)
        {
            ent->ApplyForceX(-PLAYER_MOVE_ACCEL);
        }

        // Slow down.
        else if (moveDir == 2)
        {
            ent->ApplyForceX(-PLAYER_MOVE_DEACCEL);
        }

    }
    else if (input > 0)
    {

        // Start moving left.
        if (moveDir == 0)
        {
            ent->ApplyForceX(input);
        }

        // Slow down.
        else if (moveDir == 1)
        {
            ent->ApplyForceX(PLAYER_MOVE_DEACCEL);
        }

        // Maintain speed.
        else if (moveDir == 2)
        {
            ent->ApplyForceX(PLAYER_MOVE_ACCEL);
        }

    }

}

void PlayerFallInit(Entity* ent)
{
    ent->SetMaxVelocityY(PLAYER_MAX_FALL);
    ent->SetMaxVelocityX(PLAYER_MOVE_SPEED);
}

void PlayerFallMain(Entity* ent)
{

    // Gravity.
    if (Input::Down(BUTTON_JUMP))
    {
        ent->ApplyForceY(PLAYER_GRAVITY_JUMP);
    }
    else
    {
        ent->ApplyForceY(PLAYER_GRAVITY);
    }

    // Movement direction.
    int moveDir = 0;
    if (ent->kclBody.velocity.x < 0)
        moveDir = 1;
    if (ent->kclBody.velocity.x > 0)
        moveDir = 2;
        
    // Get input.
    EMU input = 0;
    if (Input::Down(BUTTON_LEFT))
        input -= PLAYER_ACCEL_AIR;
    if (Input::Down(BUTTON_RIGHT))
        input += PLAYER_ACCEL_AIR;

    // Use input.
    if (input < 0)
    {

        // Start moving left.
        if (moveDir == 0)
        {
            ent->ApplyForceX(input);
        }

        // Maintain speed.
        else if (moveDir == 1)
        {
            ent->ApplyForceX(-PLAYER_ACCEL_AIR);
        }

        // Slow down.
        else if (moveDir == 2)
        {
            ent->ApplyForceX(-PLAYER_DEACCEL_AIR);
        }

    }
    else if (input > 0)
    {

        // Start moving left.
        if (moveDir == 0)
        {
            ent->ApplyForceX(input);
        }

        // Slow down.
        else if (moveDir == 1)
        {
            ent->ApplyForceX(PLAYER_DEACCEL_AIR);
        }

        // Maintain speed.
        else if (moveDir == 2)
        {
            ent->ApplyForceX(PLAYER_ACCEL_AIR);
        }

    }

    // TODO: REPLACE WITH TRUE FLOOR COLLISION.
    if (ent->kclBody.position.y >= FLOOR)
    {
        ent->kclBody.position.y = FLOOR;
        ent->SetVelocityY(0);
        ent->ChangeState(PLAYER_ST_MOVE);
    }

}

void PlayerFallCleanup(Entity* ent)
{
    ent->SetVelocityY(0);
}