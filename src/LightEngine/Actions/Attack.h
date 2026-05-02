#pragma once
#include "../StateMachine/Action.h"
#include "../Entity/RugbyMan.h"

class Attack : public Action<RugbyMan>
{
public:
	void Start(RugbyMan* _npc) override;
	void Update(RugbyMan* _npc) override;
	void End(RugbyMan* _npc) override;

	friend RugbyMan;
};