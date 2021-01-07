#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include <vector>

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddDrawComponent(class DrawComponent* draw);
	void RemoveDrawComponent(class DrawComponent* draw);

	std::vector<class Enery*> GetEnery(){return mEnerys;}
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
	
	// Map of textures loaded
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// All the actors in the game
	std::vector<class Actor*> mActors;
	// Any pending actors
	std::vector<class Actor*> mPendingActors;

	std::vector<class DrawComponent*>mDrawComponents;

	std::vector<class Enery*> mEnerys;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	// Track if we're updating actors right now
	bool mUpdatingActors;

	struct NavPoint* n1;
	struct NavPoint* n2;
	struct NavPoint* n3;
	struct NavPoint* n4;

	float CD;

};
