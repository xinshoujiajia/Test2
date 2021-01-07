#pragma once

#include"MoveComponent.h"
#include"Math.h"

struct NavPoint
{
    NavPoint *next;
    Vector2 Position;
    Vector2 Toward;
};

class NavComponent:public MoveComponent
{
private:
    NavPoint *mTarget;
public:
    NavComponent(class Actor* owner, int updateOrder=100);
    NavComponent(class Actor* owner,NavPoint* target,int updateOrder=100);
    ~NavComponent();

    void Update(float deltaTime)override;
};

