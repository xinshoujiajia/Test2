#pragma once
#include "Actor.h"
class Bullect :
    public Actor
{
public:
    Bullect(class Game* game, int damage=0,class Enery* target=nullptr);
    ~Bullect();
    void UpdateActor(float deltaTime)override;
private:
    class Enery* mTarget;
    class MoveComponent* mMove;
    int mDamage;
};

