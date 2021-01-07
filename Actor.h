#pragma once
#include <vector>
#include "Math.h"
class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	enum Name
	{
		ETower,
		EEnery,
		EActor
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);

	// Getters/setters
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	void AddPosition(const Vector2& pos){mPosition+=pos;}
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame(){ return mGame; }


	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	Name mName=EActor;

private:
	// Actor's state
	State mState;

	// Transform
	Vector2 mPosition;
	float mScale;

	std::vector<class Component*> mComponents;
	class Game* mGame;
};
