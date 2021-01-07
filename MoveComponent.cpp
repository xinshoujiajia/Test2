#include"MoveComponent.h"
#include"Actor.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
    :Component(owner,updateOrder)
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltaTime)
{
    Vector2 vel=mToward*mVel;
    mOwner->AddPosition(vel);
}
