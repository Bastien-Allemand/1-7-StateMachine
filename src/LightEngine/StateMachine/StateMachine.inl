#include "StateMachine.h"

#include "Behaviour.h"

template<typename T>
StateMachine<T>::StateMachine(T* owner, int stateCount)
{
	mOwner = owner;
	mCurrentState = -1;
	mBehaviours.resize(stateCount);
}

template<typename T>
StateMachine<T>::~StateMachine()
{
	for (Behaviour<T>* pBehaviour : mBehaviours)
		delete pBehaviour;
}


template<typename T>
void StateMachine<T>::SetState(int state)
{
	if (mCurrentState > 0 && mCurrentState < mBehaviours.size())
		mBehaviours[mCurrentState]->End();

	mCurrentState = state;

	mBehaviours[mCurrentState]->Start();
}

template<typename T>
void StateMachine<T>::Update()
{
	if (!activate)
	{
		return;
	}

	if (mCurrentState == -1)
		return;

	int transitionState = mBehaviours[mCurrentState]->Update();

	if (transitionState == -1)
		return;

	SetState(transitionState);
}

template<typename T>
Behaviour<T>* StateMachine<T>::CreateBehaviour(int state)
{
	_ASSERT(state >= 0 && state < mBehaviours.size());

	Behaviour<T>* pBehaviour = new Behaviour<T>(mOwner);
	mBehaviours[state] = pBehaviour;

	return pBehaviour;
}