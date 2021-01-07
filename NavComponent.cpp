#include"NavComponent.h"
#include"Actor.h"
#include<SDL2/SDL.h>

NavComponent::NavComponent(Actor* owner, int updateOrder)
    :MoveComponent(owner,updateOrder)
{
    mTarget = nullptr;
}

NavComponent::NavComponent(Actor* owner, NavPoint* target, int updateOrder)
    :MoveComponent(owner,updateOrder)
    ,mTarget(target)
{
    SetToward(mTarget->Toward);
}

NavComponent::~NavComponent()
{
}

void NavComponent::Update(float deltaTime)
{
    if (mTarget!=nullptr)
    {
        mOwner->AddPosition(GetVel() * GetTowarw());
        float len = (mOwner->GetPosition() - mTarget->Position).Length();
        if (len<10.0f)
        {
            SetToward(mTarget->Toward);
            mTarget = mTarget->next;
        }
    }
}