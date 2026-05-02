#pragma once

#include "../Engine//Entity.h"
#include "../StateMachine//StateMachine.h"
#include "../RugbyUtils/Boudaries.h"
#include "../Engine/Debug.h"

#include <iostream>


class RugbyMan : public Entity 
{
	Boudaries m_boundaries;
public:
	enum State
	{
		S_RunToBall,
		S_Scoreing,
		S_Support,
		S_AttackBall,
		S_ShootingBall,
		S_Escape,

		Count
	};

	bool debugMode = false;
	StateMachine<RugbyMan> mStateMachine;

private:

	int mAreaIndex;
	bool m_invincible;
	float m_pass_delay;
	float m_inv_delay;
	float velocity;
	float maxVelocity;
	bool m_has_passed;

	void SetAreaIndex(int index) { mAreaIndex = index; }
	const char* GetStateName(State state) const;

protected:
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
	virtual void OnInitialize() override;
	virtual void OnDestroy() override;
public:


	RugbyMan();
	void InitStateMachine();
	void DebugLine();
	void SetSpeed(float _speed) { velocity = _speed; }
	float GetSpeed() { return velocity; }
	void SetInvincible(bool _invincible);

	bool GetIfInvincible() { return m_invincible; }
	bool GetIfHasPassed() { return m_has_passed; }
	void SetIfHasPassed(bool _haspassed) 
	{
		Debug::DrawText(1300, 600, "ball passed", sf::Color::White);
		m_pass_delay = 0.0f;
		m_has_passed = _haspassed; 
	}
	Boudaries& GetBoundaries() { return m_boundaries; }
	void SetBoundaries(int _left, int _top, int _width, int _height);

};










