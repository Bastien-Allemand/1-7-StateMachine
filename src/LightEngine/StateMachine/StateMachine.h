#pragma once

#include <vector>

template<typename T>
class Behaviour;

template<typename T>
class StateMachine
{
	std::vector<Behaviour<T>*> mBehaviours;
	int mCurrentState;

	T* mOwner;
public:
	bool activate = true;

	StateMachine(T* owner, int stateCount);
	~StateMachine();

	void Update();
	void SetState(int state);
	int GetCurrentState() const { return mCurrentState; }

	Behaviour<T>* CreateBehaviour(int state);
};

#include "StateMachine.inl"

