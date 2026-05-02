#pragma once
#include "../Engine/Entity.h"*
#include "RugbyMan.h"
#include "../RugbyUtils/Boudaries.h"
class Ball : public Entity
{
protected:
	int m_team_tag =-1;
	RugbyMan* m_ball_holder;
	Boudaries* m_boundaries;
public:

	RugbyMan* GetNpcWithBall()
	{ return m_ball_holder; }

	void SetNpcWithBall(RugbyMan* _npc) 
	{ m_ball_holder = _npc; }

	bool IsTaken() const;

	Boudaries* GetBoundaries()
	{return m_boundaries;}

	virtual void OnUpdate() override;
	virtual void OnCollision(Entity* _collidedWith) override;
	virtual void OnInitialize() override;
	virtual void OnDestroy() override{} //empty
};

