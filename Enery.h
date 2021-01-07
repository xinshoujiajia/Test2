#pragma once
#include"Actor.h"
class Enery:public Actor
{
private:
    class NavComponent* mMove;
    int Health;

    std::vector<class Tower*> mTarTower;

public:
    Enery(class Game* game);
    Enery(class Game* game,struct NavPoint* target);

    void Damage(int damage);
    void AddTower(class Tower* tower){mTarTower.emplace_back(tower);}
    void RemoveTower(class Tower* tower);
    class NavComponent* GetMoveComponent(){return mMove;}

    ~Enery();
};