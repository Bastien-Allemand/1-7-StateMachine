#pragma once

#include "Action.h"

#include "Transition.h"

template<typename T>
Action<T>::~Action()
{
    for (auto it : mTransitions)
    {
        delete it;
    }
}

template<typename T>
Transition<T>* Action<T>::CreateTransition(int state)
{
    Transition<T>* pTransition = new Transition<T>(state);
    mTransitions.push_back(pTransition);

    return pTransition;
}

template<typename T>
int Action<T>::Update(T* pOwner)
{
    OnUpdate(pOwner);

    for (const auto& t : mTransitions)
    {
        if (t->Try(pOwner))
        {
            return t->GetTransitionState();
        }
    }

    return -1;
}
