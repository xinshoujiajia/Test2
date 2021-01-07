#include "Tower.h"
#include"Bullect.h"
#include"Game.h"
#include"DrawComponent.h"
#include"Enery.h"

Tower::Tower(Game* game, int damage, float rad)
	:Actor(game)
	,mDamage(damage)
	,mRad(rad)
	,mTarget(nullptr)
	,mCurrentCD(0.0f)
	,mMaxCD(1.0f)
{
	mName = ETower;
	GetGame()->AddActor(this);

	DrawComponent* dc = new DrawComponent(this, this->GetGame());
	dc->SetSize(15);
	dc->SetColor(255, 0, 0, 255);
}

Tower::~Tower()
{
}

void Tower::SetTarget(Enery* target)
{
	mTarget = target;
}

void Tower::UpdateActor(float deltaTime)
{
	if (mTarget == nullptr)
	{
		for(auto enery:GetGame()->GetEnery())
		{
			float Len=(GetPosition()-enery->GetPosition()).LengthSq();
			if(GetRad()*GetRad()-Len>=0)
			{
				SetTarget(enery);
				enery->AddTower(this);
				break;
			}
		}
	}
	else
	{
		if(mTarget->GetState()==Actor::EActive)
		{
			if (mCurrentCD <= 0.0f)
			{
				float Len=(GetPosition()-mTarget->GetPosition()).LengthSq();
				if(GetRad()*GetRad()-Len>=0)
				{
					Bullect* b = new Bullect(GetGame(), mDamage, mTarget);
					b->SetPosition(GetPosition());
					mCurrentCD = mMaxCD;
				}
				else
					SetTarget(nullptr);
			}
			else { mCurrentCD -= deltaTime; }
		}
		else
		{
			mTarget->RemoveTower(this);
			SetTarget(nullptr);
		}
	}
}

void Tower::ForeFire(Enery* e)
{
  Vector2 dis=e->GetPosition()-GetPosition();
  float a=(e->GetMoveComponent()->GetVel()-Vel)
    *(e->GetMoveComponent()->GetVel()+Vel);
  float b=2.0f*e->GetMoveComponent()->GetVel();
    *(dis*e->GetToward());
  float c=dis.LengthSq();
  float t;
  float disc=b*b-4.0f*a*c;
  if(disc>0.0f)
  {
    disc=Math::Sqrt(disc);
    t=(-b-disc)/(2.0f*a);
    if(t>0.0f)
    {
      Vector2 toward=dis+e->GetToward()*t*e->GetMoveComponent()->GetVel();
      toward.Normalize();
      Bullect* bullet=new Bullet(GetGame());
      bullet->SetToward(toward);
      bullet->SetLife(t);
    }
  }
}