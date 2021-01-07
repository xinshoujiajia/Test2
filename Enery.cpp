#include"Enery.h"
#include"DrawComponent.h"
#include"NavComponent.h"
#include"Game.h"
#include"Tower.h"
#include <algorithm>

Enery::Enery(Game* game)
    :Actor(game)
    ,Health(5)
{
    mName = EEnery;
    GetGame()->AddActor(this);

    mMove=new NavComponent(this,new NavPoint{nullptr,GetPosition()});
    mMove->SetVel(1.0f);
    mMove->SetToward(Vector2(1.0f,0.0f));
    DrawComponent *dc=new DrawComponent(this,this->GetGame());
    dc->SetSize(15);
    dc->SetColor(255,0,0,255);
}

Enery::Enery(Game* game,NavPoint* target)
    :Actor(game)
    , Health(5)
{
    mName = EEnery;
    GetGame()->AddActor(this);

    mMove=new NavComponent(this,target);
    mMove->SetVel(1.0f);
    //mMove->SetToward(Vector2(1.0f,0.0f));
    DrawComponent *dc=new DrawComponent(this,this->GetGame());
    dc->SetSize(15);
    dc->SetColor(255,0,0,255);
}

void Enery::Damage(int damage)
{
    Health -= damage;
    if (Health <= 0)
        SetState(EDead);
}

Enery::~Enery()
{
    for(auto tower:mTarTower)
    {
        tower->SetTarget(nullptr);
    }
}

void Enery::RemoveTower(Tower* tower)
{
    auto iter = std::find(mTarTower.begin(), mTarTower.end(), tower);
	if (iter != mTarTower.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mTarTower.end() - 1);
		mTarTower.pop_back();
	}
}