#include "SceneRugby.h"
//
#include "../Engine/GameManager.h"
#include "../Engine/Debug.h"
#include "../Engine/Utils.h"
//
#include "../Entity/RugbyMan.h"
#include "../Entity/Ball.h"
//
#include <random>
#include "../RugbyUtils/Boudaries.h"

void SceneRugby::OnInitialize()
{
	m_score = std::make_pair(0, 0);

	RugbyMan* m_Npc0 = CreateEntity<RugbyMan>(20, sf::Color::Green);
	m_Npc0->SetTag(ALLY);
	m_Npc0->SetBoundaries(100, 100, 1100, 250);

	RugbyMan* m_Npc1 = CreateEntity<RugbyMan>(20, sf::Color::Green);
	m_Npc1->SetTag(ALLY);
	m_Npc1->SetBoundaries(100, 225, 1100, 250);

	RugbyMan* m_Npc2 = CreateEntity<RugbyMan>(20, sf::Color::Green);
	m_Npc2->SetTag(ALLY);
	m_Npc2->SetBoundaries(100, 350, 1100, 250);


	RugbyMan* m_Npc6 = CreateEntity<RugbyMan>(20, sf::Color::Green);
	m_Npc6->SetTag(ALLY);
	m_Npc6->SetBoundaries(100, 100, 1100, 250);

	RugbyMan* m_Npc7 = CreateEntity<RugbyMan>(20, sf::Color::Green);
	m_Npc7->SetTag(ALLY);
	m_Npc7->SetBoundaries(100, 350, 1100, 250);

	RugbyMan* m_Npc3 = CreateEntity<RugbyMan>(20, sf::Color::Red);
	m_Npc3->SetTag(ENEMY);
	m_Npc3->SetBoundaries(100, 100, 1100, 250);


	RugbyMan* m_Npc4 = CreateEntity<RugbyMan>(20, sf::Color::Red);
	m_Npc4->SetTag(ENEMY);
	m_Npc4->SetBoundaries(100, 225, 1100, 250);

	RugbyMan* m_Npc5 = CreateEntity<RugbyMan>(20, sf::Color::Red);
	m_Npc5->SetTag(ENEMY);
	m_Npc5->SetBoundaries(100, 350, 1100, 250);

	

	RugbyMan* m_Npc8 = CreateEntity<RugbyMan>(20, sf::Color::Red);
	m_Npc8->SetTag(ENEMY);
	m_Npc8->SetBoundaries(100, 100, 1100, 250);

	RugbyMan* m_Npc9 = CreateEntity<RugbyMan>(20, sf::Color::Red);
	m_Npc9->SetTag(ENEMY);
	m_Npc9->SetBoundaries(100, 350, 1100, 250);

	m_ball = CreateEntity<Ball>(10, sf::Color::White);
	m_ball->SetTag(BALL);

	m_npcs.push_back(m_Npc0);
	m_npcs.push_back(m_Npc1);
	m_npcs.push_back(m_Npc2);
	m_npcs.push_back(m_Npc6);
	m_npcs.push_back(m_Npc7);
	m_npcs.push_back(m_Npc5);
	m_npcs.push_back(m_Npc3);
	m_npcs.push_back(m_Npc4);
	m_npcs.push_back(m_Npc8);
	m_npcs.push_back(m_Npc9);


	ResetPosition();
}

void SceneRugby::OnEvent(const sf::Event& event)
{

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		for (RugbyMan* npc : m_npcs)
		{
			TrySetSelectedEntity(npc, event.mouseButton.x, event.mouseButton.y);
		}
	}
	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (m_player_selected != nullptr)
		{
			m_player_selected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
		}
	}
	if (event.KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Space)
		{
			if (m_player_selected != nullptr)
			{
				GiveBall(m_player_selected);
			}
		}
	}
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::D)
		{
			for (int i = 0; i < m_npcs.size(); i++)
			{

				m_npcs[i]->debugMode = !m_npcs[i]->debugMode;
			}

		}

		if (event.key.code == sf::Keyboard::S)
		{
			for (int i = 0; i < m_npcs.size(); i++)
			{
				m_npcs[i]->mStateMachine.activate = !m_npcs[i]->mStateMachine.activate;

			}

		}
		if (event.key.code == sf::Keyboard::Enter)
		{
			DebugShoot();

		}
	}
}


void SceneRugby::TrySetSelectedEntity(RugbyMan* _npc, int _x, int _y)
{
	if (_npc->IsInside(_x, _y) == false)
		return;
	m_player_selected = _npc;
}

void SceneRugby::OnUpdate()
{
	Debugfield();
	DebugMessagebox();
	for (int i = 0; i < m_npcs.size(); i++)
	{
		if (m_npcs[i]->debugMode)
		{
			m_npcs[i]->DebugLine();
		}
	}
	if (m_ball->GetBoundaries()->CheckBoundaries(m_ball->GetPosition()))
	{
		ResetPosition();
	}
	if (m_ball->GetPosition().x < 180){m_score.second++;m_resetmatch = true;}
	if (m_ball->GetPosition().x > 1120){m_score.first++;m_resetmatch = true;}
	if (m_resetmatch == true){ResetPosition();m_resetmatch = false;}
}


void SceneRugby::DebugShoot() {

	RugbyMan* man = m_ball->GetNpcWithBall();
	if (man == nullptr)
		return;

	if (man->GetIfInvincible())
		return;

	
	sf::Vector2f pos = man->GetPosition();
	sf::Vector2f pos2 = m_player_selected->GetPosition();
	sf::Vector2f direction = sf::Vector2f(pos2.x - pos.x, pos2.y - pos.y);



	Debug::DrawLine(pos2.x, pos2.y, pos.x, pos.y, sf::Color::Yellow);

	sf::Vector2f ballpos =m_ball->GetPosition();

	man->SetIfHasPassed(true);
	m_ball->SetNpcWithBall(nullptr);

	m_ball->SetDirection(direction.x, direction.y, 100);
	man->mStateMachine.SetState(RugbyMan::S_ShootingBall);
		
}

void SceneRugby::Debugfield()
{
	//draw score
	Debug::DrawText(650, 25, std::to_string(m_score.first) + " |-| " + std::to_string(m_score.second), 0.5f, 0.5f, sf::Color::White);
	//draw field
	{
		Debug::DrawRectangle(100, 100, 1100, 500, sf::Color::White);
		Debug::DrawLine(650, 100, 650, 600, sf::Color::White);
		Debug::DrawLine(180, 100, 180, 600, sf::Color::Green);
		Debug::DrawLine(1120, 100, 1120, 600, sf::Color::Red);
		Debug::DrawLine(380, 100, 380, 600, sf::Color::White);
		Debug::DrawLine(920, 100, 920, 600, sf::Color::White);
	}
	//divise le terrain horizontalement en 3
	{
		Debug::DrawRectangle(100, 100, 1100, 250, sf::Color::Magenta);
		Debug::DrawRectangle(100, 350, 1100, 250, sf::Color::Magenta);
		Debug::DrawRectangle(100, 225, 1100, 250, sf::Color::Yellow);
	}
}

void SceneRugby::DebugMessagebox()
{
	for (int i = 0; i < m_npcs.size(); i++) {
		sf::Vector2f pos = m_npcs[i]->GetPosition();
		Debug::DrawText(1350 + 45 * i, 0  , std::to_string(i), sf::Color::White);
		Debug::DrawText(1350 + 45 * i, 50 , std::to_string((int)m_npcs[i]->GetSpeed()),sf::Color::White);
		Debug::DrawText(1350 + 45 * i, 100, std::to_string((int)pos.x), sf::Color::White);
		Debug::DrawText(1350 + 45 * i, 150, std::to_string((int)pos.y), sf::Color::White);
		Debug::DrawText(1350 + 45 * i, 200, std::to_string((int)m_npcs[i]->GetIfInvincible()), sf::Color::White);

		Debug::DrawText(pos.x, pos.y, std::to_string(i), 0.75f, 0.75f, sf::Color::White);
		//line de la direction du joueur
		Debug::DrawLine(pos.x, pos.y, pos.x + m_npcs[i]->GetDirection().x * 50, pos.y + m_npcs[i]->GetDirection().y * 50, sf::Color::Cyan);
	}

	Debug::DrawText(1300, 250, "BT:", sf::Color::White);
	Debug::DrawText(1345, 250,std::to_string(m_ball->IsTaken()), sf::Color::White);

	Debug::DrawText(1300, 0, "Id:", sf::Color::White);
	Debug::DrawText(1300, 50, "Vl:", sf::Color::White);
	Debug::DrawText(1300, 100, "X :", sf::Color::White);
	Debug::DrawText(1300, 150, "Y :", sf::Color::White);
	Debug::DrawText(1300, 200, "st:", sf::Color::White);

	Debug::DrawRectangle(1300, 0, 1799.9f, 699.9f, sf::Color::Blue);
}

void SceneRugby::ResetPosition(){
	m_npcs[0]->SetPosition(200, 130);
	m_npcs[1]->SetPosition(500, 350);
	m_npcs[2]->SetPosition(200, 520);

	m_npcs[3]->SetPosition(300, 180);
	m_npcs[4]->SetPosition(300, 450);


	m_npcs[6]->SetPosition(1100, 130);
	m_npcs[7]->SetPosition(1100, 520);
	m_npcs[5]->SetPosition(800, 350);


	m_npcs[8]->SetPosition(1000, 180);
	m_npcs[9]->SetPosition(1000, 450);
	if (m_ball->GetNpcWithBall() == nullptr)
	{

		m_ball->SetNpcWithBall(nullptr);
		m_ball->SetPosition(650 ,350);
		m_ball->SetDirection(0, 0);
		return;
	}

	if (GetOppositeTag(m_ball->GetNpcWithBall()) == tag::ENEMY)
	{
		int ran = 5 + rand()%4;
		sf::Vector2f pos= m_npcs[ran]->GetPosition();
		m_ball->SetPosition(pos.x, pos.y);
		m_ball->SetNpcWithBall(m_npcs[ran]);

	}
	else if (GetOppositeTag(m_ball->GetNpcWithBall()) == tag::ALLY){
		int ran =  rand() %4;
		sf::Vector2f pos = m_npcs[ran]->GetPosition();
		m_ball->SetPosition(pos.x, pos.y);
		m_ball->SetNpcWithBall(m_npcs[ran]);

	}
	

	m_ball->SetDirection(0, 0);
}

void SceneRugby::GiveBall(RugbyMan* _npc){

	_npc->SetInvincible(true);
	m_ball->SetNpcWithBall(_npc);
}

RugbyMan* SceneRugby::GetPlayerWithBall()
{
	return m_ball->GetNpcWithBall();
}

SceneRugby::tag SceneRugby::GetOppositeTag(RugbyMan* pEntity) const{return pEntity->IsTag(SceneRugby::tag::ALLY) ? SceneRugby::tag::ENEMY : SceneRugby::tag::ALLY;}
SceneRugby::tag SceneRugby::GetTag(RugbyMan* pEntity) const{return pEntity->IsTag(SceneRugby::tag::ALLY) ? SceneRugby::tag::ALLY : SceneRugby::tag::ENEMY;}
RugbyMan* SceneRugby::GetPlayerBall() const{return m_ball->GetNpcWithBall();}
