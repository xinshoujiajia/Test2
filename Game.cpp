#include "Game.h"
#include <algorithm>
#include "Actor.h"
#include"DrawComponent.h"
#include"Player.h"
#include"NavComponent.h"
#include"Enery.h"
#include"Bullect.h"
#include"Tower.h"

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mIsRunning(true)
,mUpdatingActors(false)
{
	
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 2)", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicks();

	CD = 0.0f;
	
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

}

void Game::UpdateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	CD -= deltaTime;
	if (CD <= 0)
	{
		CD = 2.0f;
		Enery* e = new Enery(this, n1);
		e->SetPosition(Vector2(0.0f, 100.0f));
		e->SetScale(1.0f);
	}

	// Update all actors
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	

	// Move any pending actors to mActors
	for (auto pending : mPendingActors)
	{
		switch (pending->mName)
		{
		case Actor::ETower:
			break;
		case Actor::EEnery:
			mEnerys.emplace_back(dynamic_cast<Enery*>(pending));
			break;
		case Actor::EActor:
			mActors.emplace_back(pending);
			break;
		}
	}
	mPendingActors.clear();

	// Add any dead actors to a temp vector
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// Delete dead actors (which removes them from mActors)
	for (auto actor : deadActors)
	{
		delete actor;
		//actor = NULL;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
	for(auto draw:mDrawComponents)
        draw->Draw(mRenderer);
	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown()
{
	UnloadData();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::LoadData()
{
	n1 = new NavPoint;
	n2 = new NavPoint;
	n3 = new NavPoint;
	n4 = new NavPoint;
	*n1 = { n2,Vector2(100.0f,100.0f),Vector2(1.0f,0.0f) };
	*n2 = { n3,Vector2(400.0f,100.0f),Vector2(0.0f,1.0f) };
	*n3 = { n4,Vector2(400.0f,400.0f),Vector2(-1.0f,0.0f) };
	*n4 = { n1,Vector2(100.0f,400.0f),Vector2(0.0f,-1.0f) };

	Tower* t1 = new Tower(this, 1, 200.0f);
	t1->SetPosition(Vector2(200.0f, 200.0f));
	t1->SetScale(1.0f);
	Tower* t2 = new Tower(this, 2, 200.0f);
	t2->SetPosition(Vector2(300.0f, 200.0f));
	t2->SetScale(1.0f);
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	mEnerys.clear();
	while (!mActors.empty())
	{
		delete mActors.back();
	}
}

void Game::AddActor(Actor* actor)
{
	// If we're updating actors, need to add to pending
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		switch (actor->mName)
		{
		case Actor::ETower:
			break;
		case Actor::EEnery:
			mEnerys.emplace_back(dynamic_cast<Enery*>(actor));
			break;
		case Actor::EActor:
			mActors.emplace_back(actor);
			break;
		}
	}
}

void Game::RemoveActor(Actor* actor)
{
	// Is it in pending actors?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}

	switch (actor->mName)
	{
	case Actor::ETower: {
		break;
	}
	case Actor::EEnery: {
		auto item = std::find(mEnerys.begin(), mEnerys.end(), actor);
		if (item != mEnerys.end())
		{
			// Swap to end of vector and pop off (avoid erase copies)
			std::iter_swap(item, mEnerys.end() - 1);
			mEnerys.pop_back();
		}
		break;
	}
	}

}

void Game::AddDrawComponent(DrawComponent* draw)
{
	int myOrder = draw->GetUpdateOrder();
	auto iter = mDrawComponents.begin();
	for (;
		iter != mDrawComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	mDrawComponents.insert(iter, draw);
}

void Game::RemoveDrawComponent(DrawComponent* draw)
{
	auto iter = std::find(mDrawComponents.begin(), mDrawComponents.end(), draw);
	if (iter != mDrawComponents.end())
	{
		mDrawComponents.erase(iter);
	}
}