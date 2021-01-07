#include"DrawComponent.h"
#include"Actor.h"
#include"Game.h"
DrawComponent::DrawComponent(Actor *owner,Game *game,int updateOrder)
    :Component(owner,updateOrder)
{
    game->AddDrawComponent(this);
    mSize=0;
    mColor={0,0,0,0};
}

DrawComponent::~DrawComponent()
{
    mOwner->GetGame()->RemoveDrawComponent(this);
}

void DrawComponent::Draw(SDL_Renderer *Renderer)
{
    if (mOwner->GetState() == Actor::EActive)
    {
        SDL_SetRenderDrawColor(
            Renderer,
            mColor.R,//R
            mColor.G,//G
            mColor.B,//B
            mColor.A//A
        );

        SDL_Rect wall{
            static_cast<int>(mOwner->GetPosition().x),//x
            static_cast<int>(mOwner->GetPosition().y),//y
            mSize,//
            mSize//
        };
        SDL_RenderFillRect(Renderer, &wall);
    }
}