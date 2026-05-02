#include "Ball.h"
#include "../Scene/SceneRugby.h"
#include <iostream>

bool Ball::IsTaken() const
{
	return m_ball_holder != nullptr;
}

void Ball::OnUpdate()
{
	if (IsTaken())
	{
		std::cout << "Ball is taken" << std::endl;
		//Ball must be Taken to execute this code
		SetDirection(0, 0);
		sf::Vector2f pos = m_ball_holder->GetPosition();
		SetPosition(pos.x, pos.y);
	}
	else {
		std::cout << "Ball is not taken" << std::endl;

	}
}
void Ball::OnCollision(Entity* _collidedWith)
{
	if (m_ball_holder != nullptr)
		return;

	SceneRugby* pscene = GetScene<SceneRugby>();
	if (_collidedWith->IsTag(SceneRugby::tag::ALLY) || _collidedWith->IsTag(SceneRugby::tag::ENEMY))
	{
		RugbyMan* npc = dynamic_cast<RugbyMan*>(_collidedWith);
	
		if (npc->mStateMachine.GetCurrentState() == RugbyMan::S_ShootingBall)
			return;
		pscene->GiveBall(npc);
		
	}
}
void Ball::OnInitialize()
{
	SetTag(SceneRugby::tag::BALL);
	m_boundaries = new Boudaries();
	m_boundaries->SetBoundaries(100, 100, 1100, 500);
	m_ball_holder = nullptr;
}