#pragma once
#include "Actor.h"
class Tower :
    public Actor
{
public:
    Tower(class Game* game, int damage = 0, float rad = 0.0f);
    ~Tower();
    
    float GetRad()const { return mRad; }
    void SetRad(const float r) { mRad = r; }

    const class Enery* GetTarget()const { return mTarget; }
    void SetTarget(class Enery* target);
    void UpdateActor(float deltaTime)override;
private:
    class Enery* mTarget;
    int mDamage;
    float mRad;

    float mCurrentCD;
    float mMaxCD;
    void ForeFire(Enery* e);
    float Vel;
};

