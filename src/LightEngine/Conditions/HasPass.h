#pragma once
#include "../StateMachine/Condition.h"
#include "../Entity/RugbyMan.h"


class HasPass : public Condition<RugbyMan>
{
public:
	bool OnTest(RugbyMan* owner) override;
};

