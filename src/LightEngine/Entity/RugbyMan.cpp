#include "RugbyMan.h"
#include <string>
#include <iostream>

#include "../Scene/SceneRugby.h"
#include "ball.h"

#include "../Actions/Attack.h"
#include "../Actions/RunToBall.h"
#include "../Actions/Scoreing.h"
#include "../Actions/ShootingBall.h"
#include "../Actions/Support.h"
#include "../Actions/Escape.h"

#include "../Conditions/AllyHaveBall.h"
#include "../Conditions/EnemyHaveBall.h"
#include "../Conditions/EnemyInArea.h"
#include "../Conditions/HaveBall.h"
#include "../Conditions/EnemyInSmallArea.h"
#include "../Conditions/HasPass.h"
#include "../Conditions/IsInvincible.h"

#include "../Engine/Utils.h"
#include "../Engine/Debug.h"
#include <random>

void RugbyMan::OnInitialize()
{
	m_boundaries = Boudaries();
	SetRigidBody(true);
	m_invincible = false;
	m_inv_delay = 0.0f;
	maxVelocity = 40+(rand()%20 );
	velocity = maxVelocity;
	mAreaIndex = -1;

	InitStateMachine();
}

void RugbyMan::OnDestroy()
{

}

RugbyMan::RugbyMan() :	mStateMachine(this, State::Count)
{}

void RugbyMan::InitStateMachine()
{
	// -----------> RunToBall
	{
		Behaviour<RugbyMan>* pRunToBall = mStateMachine.CreateBehaviour(State::S_RunToBall);
		pRunToBall->AddAction<RunToBall>();

		// ------> Transitions
		// ----------> Attack	
		{
			auto transition = pRunToBall->CreateTransition(State::S_AttackBall);
			transition->AddCondition<EnemyHaveBall>(true);
		}
		// ----------> Support
		{
			auto transition = pRunToBall->CreateTransition(State::S_Support);
			transition->AddCondition<AllyHaveBall>(true);
		}
		// ----------> Scoreing
		{
			auto transition = pRunToBall->CreateTransition(State::S_Scoreing);
			transition->AddCondition<HaveBall>(true);
		}
	}
	// -----------> Scoreing
	{
		Behaviour<RugbyMan>* pScoreing = mStateMachine.CreateBehaviour(State::S_Scoreing);
		pScoreing->AddAction<Scoreing>();

		// ------> Transitions
		// ----------> Escape
		{
			auto transition = pScoreing->CreateTransition(State::S_Escape);
			transition->AddCondition<HaveBall>(true);
			transition->AddCondition<EnemyInSmallArea>(true);
		}
		// ----------> ShootingBall
		{
			auto transition = pScoreing->CreateTransition(State::S_ShootingBall);
			transition->AddCondition<HaveBall>(true);
			transition->AddCondition<EnemyInSmallArea>(false);
			transition->AddCondition<EnemyInArea>(true);
			transition->AddCondition<IsInvincible>(false);

		}
		// ----------> Attack
		{
			auto transition = pScoreing->CreateTransition(State::S_AttackBall);
			transition->AddCondition<HaveBall>(false);
			transition->AddCondition<EnemyHaveBall>(true);
		}
		// ----------> Support
		{
			auto transition = pScoreing->CreateTransition(State::S_Support);
			transition->AddCondition<AllyHaveBall>(true);
			transition->AddCondition<HaveBall>(false);
		}
		// ----------> RunToBall
		{
			auto transition = pScoreing->CreateTransition(State::S_RunToBall);
			transition->AddCondition<HasPass>(false);
			transition->AddCondition<HaveBall>(false);
			transition->AddCondition<EnemyHaveBall>(false);
			transition->AddCondition<AllyHaveBall>(false);
		}


	}
	// -----------> Support
	{
		Behaviour<RugbyMan>* pSupport = mStateMachine.CreateBehaviour(State::S_Support);
		pSupport->AddAction<Support>();

		// ------> Transitions
		// ----------> Scoreing
		{
			auto transition = pSupport->CreateTransition(State::S_Scoreing);

			transition->AddCondition<HaveBall>(true);
		}
		// ----------> Attack
		{
			auto transition = pSupport->CreateTransition(State::S_AttackBall);

			transition->AddCondition<EnemyHaveBall>(true);
			transition->AddCondition<HaveBall>(false);
		}
		// ----------> RunToBall
		{
			auto transition = pSupport->CreateTransition(State::S_RunToBall);
			transition->AddCondition<HasPass>(false);
			transition->AddCondition<EnemyHaveBall>(false);
			transition->AddCondition<AllyHaveBall>(false);
			transition->AddCondition<HaveBall>(false);
		}
	}
	// -----------> Attack
	{
		Behaviour<RugbyMan>* pAttack = mStateMachine.CreateBehaviour(State::S_AttackBall);
		pAttack->AddAction<Attack>();

		// ------> Transitions
		// ----------> Scoreing
		{
			auto transition = pAttack->CreateTransition(State::S_Scoreing);

			transition->AddCondition<HaveBall>(true);
		}
		// ----------> Support
		{
			auto transition = pAttack->CreateTransition(State::S_Support);

			transition->AddCondition<AllyHaveBall>(true);
			transition->AddCondition<HaveBall>(false);
		}
		// ----------> RunToBall
		{
			auto transition = pAttack->CreateTransition(State::S_RunToBall);
			transition->AddCondition<HasPass>(false);
			transition->AddCondition<EnemyHaveBall>(false);
			transition->AddCondition<AllyHaveBall>(false);
			transition->AddCondition<HaveBall>(false);
		}
	}
	// -----------> Pass
	{
		Behaviour<RugbyMan>* pShooting = mStateMachine.CreateBehaviour(State::S_ShootingBall);
		pShooting->AddAction<ShootingBall>();

		// ------> Transitions
		// ----------> Support
		{
			auto transition = pShooting->CreateTransition(State::S_Support);

			transition->AddCondition<AllyHaveBall>(true);
			transition->AddCondition<HaveBall>(false);
		}
		// ----------> Attack
		{
			auto transition = pShooting->CreateTransition(State::S_AttackBall);

			transition->AddCondition<EnemyHaveBall>(true);
			transition->AddCondition<HaveBall>(false);
		}
		// ----------> RunToBall
		{
			auto transition = pShooting->CreateTransition(State::S_RunToBall);
			transition->AddCondition<HasPass>(false);
			transition->AddCondition<EnemyHaveBall>(false);
			transition->AddCondition<AllyHaveBall>(false);
			transition->AddCondition<HaveBall>(false);
		}
	}
	// -----------> Escape
	{
		Behaviour<RugbyMan>* pEscaping = mStateMachine.CreateBehaviour(State::S_Escape);
		pEscaping->AddAction<Escape>();

		// ------> Transitions
		// ----------> ShootingBall
		{
			auto transition = pEscaping->CreateTransition(State::S_ShootingBall);
			transition->AddCondition<EnemyInSmallArea>(false);
			transition->AddCondition<EnemyInArea>(true);
			transition->AddCondition<HaveBall>(true);
		}
		// ----------> Scoreing
		{
			auto transition = pEscaping->CreateTransition(State::S_Scoreing);
			transition->AddCondition<EnemyInSmallArea>(false);
			transition->AddCondition<HaveBall>(true);
		}
		// ----------> Attack
		{
			auto transition = pEscaping->CreateTransition(State::S_AttackBall);
			transition->AddCondition<EnemyHaveBall>(true);
			transition->AddCondition<HaveBall>(false);
		}
		// ----------> Support
		{
			auto transition = pEscaping->CreateTransition(State::S_Support);
			transition->AddCondition<AllyHaveBall>(true);
			transition->AddCondition<HaveBall>(false);
		}
		// ----------> RunToBall
		{
			auto transition = pEscaping->CreateTransition(State::S_RunToBall);
			transition->AddCondition<HasPass>(true);
			transition->AddCondition<EnemyHaveBall>(false);
			transition->AddCondition<AllyHaveBall>(false);
			transition->AddCondition<HaveBall>(false);
		}
	}
	mStateMachine.SetState(State::S_RunToBall);
}

void RugbyMan::DebugLine()
{


	sf::Vector2f p2 = GetPosition();
	SceneRugby* scene = GetScene<SceneRugby>();
	sf::Vector2f ptemp = scene->m_npcs[0]->GetPosition();

	float dist = NULL;

	RugbyMan* NPCToShoot = scene->m_npcs[0];

	for (RugbyMan* npc : scene->m_npcs)
	{
		if (npc != this && npc->IsTag(scene->GetTag(this)))
		{

			sf::Vector2f p1 = npc->GetPosition();

			if (Utils::GetDistance(p1.x, p1.y, p2.x, p2.y) <= dist || dist == NULL)
			{
				dist = Utils::GetDistance(p1.x, p1.y, p2.x, p2.y);
				NPCToShoot = npc;

			}

		}
		if (this == scene->m_ball->GetNpcWithBall())
		{
			Debug::DrawCircleZone(p2.x, p2.y, 150, sf::Color::Yellow);
			Debug::DrawLine(p2.x, p2.y-150, p2.x, p2.y + 150, sf::Color::Blue);
		}

	}

	sf::Vector2f p3 = NPCToShoot->GetPosition();
	Debug::DrawLine(p2.x, p2.y, p3.x, p3.y, sf::Color::Green);

}

void RugbyMan::SetInvincible(bool _invincible)
{

	m_invincible = _invincible;
}

void RugbyMan::SetBoundaries(int _left, int _top, int _width, int _height)
{
	m_boundaries.SetBoundaries(_left, _top, _width, _height);
}

const char* RugbyMan::GetStateName(State state) const
{
	switch (state)
	{
	case S_RunToBall: return "Getball";
	case S_Scoreing: return "Score";
	case S_ShootingBall: return "Pass";
	case S_Support: return "Support";
	case S_AttackBall: return "Attack";
	case S_Escape: return "Escape";

	default: return "Unknown";
	}
}

void RugbyMan::OnUpdate()
{
	const sf::Vector2f thisposition = GetPosition();
	const char* stateName = GetStateName((RugbyMan::State)mStateMachine.GetCurrentState());

	if (m_boundaries.CheckBoundaries(GetPosition()))
	{
		sf::Vector2f pos = m_boundaries.GetDistanceOutside();

		this->SetPosition(thisposition.x + pos.x, thisposition.y + pos.y);
	}

	if (m_has_passed)
	{
		m_pass_delay += GetDeltaTime();
		if (m_pass_delay >= 0.5f)
		{
			m_has_passed = false;
			m_pass_delay = 0.0f;
		}
	}

	if (m_invincible)
	{

		m_inv_delay += GetDeltaTime();
		velocity = 120;
		if (m_inv_delay >= 1.5f)
		{
			velocity = maxVelocity;
			m_invincible = false;
			m_inv_delay = 0.0f;
		}
	}
	Debug::DrawText(thisposition.x, thisposition.y - 50, stateName, 0.5f, 0.5f, sf::Color::Red);

	mStateMachine.Update();
}

void RugbyMan::OnCollision(Entity* collidedWith)
{
	SceneRugby* pscene = GetScene<SceneRugby>();
	Ball* pball = pscene->m_ball;

	
	if (collidedWith->IsTag(pscene->GetOppositeTag(this)))
	{
		RugbyMan* prugbyman = dynamic_cast<RugbyMan*>(collidedWith);

		if (prugbyman->m_invincible || prugbyman->GetIfHasPassed())
			return;

		

		RugbyMan* ballholder = pscene->GetPlayerWithBall();
		if (collidedWith == ballholder)
		{
			pscene->GiveBall(this);
		}
	}

}
