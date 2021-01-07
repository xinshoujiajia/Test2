#pragma once

#include"Component.h"
#include"Math.h"

class MoveComponent:public Component
{
private:
    float mVel;
    Vector2 mToward;
public:
    MoveComponent(class Actor* owner, int updateOrder = 100);
    ~MoveComponent();
    void Update(float deltaTime)override;

    float GetVel()const{return mVel;}
    Vector2 GetTowarw()const{return mToward;}

    void SetVel(const float v){mVel=v;}
    void SetToward(const Vector2 t){mToward=t;}
};