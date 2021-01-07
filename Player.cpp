#include"Player.h"
#include"DrawComponent.h"
#include"MoveComponent.h"

Player::Player(Game* game)
    :Actor(game)
{
    mMove=new MoveComponent(this);
    mMove->SetVel(50.0f);
    mMove->SetToward(Vector2(1,0));
    DrawComponent *dc=new DrawComponent(this,this->GetGame());
    dc->SetSize(15);
    dc->SetColor(255,0,0,255);
}

Player::~Player()
{
}
