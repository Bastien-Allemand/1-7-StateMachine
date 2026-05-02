#pragma once

#include "Transition.h"

#include "Condition.h"

template<typename T>
template<typename U>
U* Transition<T>::AddCondition(bool expected)
{
	static_assert(std::is_base_of<Condition<T>, U>::value, "T must be derived from Condition");

	U* pCondition = new U();

	pCondition->expected = expected;

	mConditions.push_back(pCondition);

	return pCondition;
}

template<typename T>
bool Transition<T>::Try(T* owner)
{
	for (const auto& c : mConditions)
	{
		if (c->Test(owner) == false)
			return false;
	}

	return true;
}