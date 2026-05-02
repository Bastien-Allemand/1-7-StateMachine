#pragma once
#include "../StateMachine/Condition.h"
#include "../Entity/RugbyMan.h"

class AllyHaveBall : public Condition<RugbyMan>
{
public:
	bool OnTest(RugbyMan* owner) override;
};


