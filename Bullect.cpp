#include "Bullect.h"
#include"MoveComponent.h"
#include"Enery.h"
#include"DrawComponent.h"

Bullect::Bullect(Game* game, int damage,Enery* target)
	:Actor(game)
	,mDamage(damage)
	,mTarget(target)
{
	//SDL_Log("bullect");

	mMove = new MoveComponent(this);
	mMove->SetVel(20.0f);

	DrawComponent* dc = new DrawComponent(this, this->GetGame());
	dc->SetSize(5);
	dc->SetColor(255, 255, 255, 255);
}

Bullect::~Bullect()
{
}

void Bullect::UpdateActor(float deltaTime)
{
	if (mTarget->GetState() == EActive)
	{
		Vector2 Toward = mTarget->GetPosition() - GetPosition();
		if (Toward.LengthSq()<25)
		{
			mTarget->Damage(mDamage);
			this->SetState(EDead);
		}
		else
		{
			Toward.Normalize();
			mMove->SetToward(Toward);
		}
	}else{ this->SetState(EDead); }
}