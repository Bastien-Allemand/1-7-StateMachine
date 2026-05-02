#pragma once
#include "../StateMachine/Condition.h"
#include "../Entity/RugbyMan.h"

class HaveBall : public Condition<RugbyMan>
{
public:
	bool OnTest(RugbyMan* owner) override;
};


