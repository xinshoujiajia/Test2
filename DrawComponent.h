#pragma once

#include"Component.h"
#include<SDL2/SDL.h>

class DrawComponent:public Component
{
public:
    struct Color{int R;int G;int B;int A;};
    DrawComponent(class Actor *owner,class Game *game,int updateOrder=100);
    ~DrawComponent();
    void Update(float deltaTime)override{}
    void Draw(SDL_Renderer *Renderer);
    void SetColor(Color color){mColor=color;};
    void SetColor(int r,int g,int b,int a){mColor={r,g,b,a};};
    void SetSize(int size){mSize=size;}
private:
    int mSize;
    Color mColor;
};