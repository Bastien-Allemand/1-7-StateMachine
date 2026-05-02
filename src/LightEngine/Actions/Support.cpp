#include "Support.h"
#include "../Scene/SceneRugby.h"
#include "../Engine/Utils.h"
#include "../Entity/Ball.h"


void Support::Start(RugbyMan* _npc)
{
}

void Support::Update(RugbyMan* _npc)
{
	SceneRugby* scene = _npc->GetScene<SceneRugby>();
	for (int i = 0; i < scene->m_npcs.size(); i++)
	{
		if (scene->m_npcs[i] == scene->m_ball->GetNpcWithBall() && ((_npc->GetPosition().x < scene->m_npcs[i]->GetPosition().x - 70 && _npc->IsTag(scene->ALLY))))
		{
			sf::Vector2f p1 = scene->m_npcs[i]->GetPosition();
			sf::Vector2f p2 = _npc->GetPosition();
			sf::Vector2f direction = sf::Vector2f(p1.x - p2.x, p1.y - p2.y);
			Utils::Normalize(direction);
			_npc->SetDirection(direction.x, 0, _npc->GetSpeed());
			break;
		}
		else if (scene->m_npcs[i] == scene->m_ball->GetNpcWithBall() && ((_npc->GetPosition().x > scene->m_npcs[i]->GetPosition().x + 70 && _npc->IsTag(scene->ENEMY))))
		{
			sf::Vector2f p1 = scene->m_npcs[i]->GetPosition();
			sf::Vector2f p2 = _npc->GetPosition();
			sf::Vector2f direction = sf::Vector2f(p1.x - p2.x, p1.y - p2.y);
			Utils::Normalize(direction);
			_npc->SetDirection(direction.x, 0, _npc->GetSpeed());
			break;
		}
		else if (scene->m_npcs[i] == scene->m_ball->GetNpcWithBall())
		{
			sf::Vector2f p1 = scene->m_npcs[i]->GetPosition();
			sf::Vector2f p2 = _npc->GetPosition();
			sf::Vector2f direction = sf::Vector2f(p1.x - p2.x, p1.y - p2.y);
			Utils::Normalize(direction);
			_npc->SetDirection(direction.x, 0, _npc->GetSpeed());
			break;
		}
	}
}

void Support::End(RugbyMan* _npc)
{
}
