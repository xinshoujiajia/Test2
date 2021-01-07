#pragma once
#include"Actor.h"
class Player:public Actor
{
private:
    class MoveComponent* mMove;
public:
    Player(class Game* game);
    ~Player();
};