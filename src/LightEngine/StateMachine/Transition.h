#pragma once

#include <vector>

template<typename T>
class Condition;

template<typename T>
class Transition
{
protected:
    std::vector<Condition<T>*> mConditions;
	int mTransitionState;

public:
	Transition(int transitionState) : mTransitionState(transitionState) {}

	template<typename U>
	U* AddCondition(bool expected = true);
	
	bool Try(T* owner);
	int GetTransitionState() { return mTransitionState; }
};

#include "Transition.inl"