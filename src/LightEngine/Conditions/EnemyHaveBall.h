#pragma once
#include "../StateMachine/Condition.h"
#include "../Entity/RugbyMan.h"

class EnemyHaveBall : public Condition<RugbyMan>
{
public:
	bool OnTest(RugbyMan* owner) override;
};
