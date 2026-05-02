#pragma once

#include "Condition.h"

template<typename T>
bool Condition<T>::Test(T* owner)
{
	return expected == OnTest(owner);
}