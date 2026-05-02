#include "Attack.h"
#include "../Scene/SceneRugby.h"
#include "../Engine/Utils.h"
#include "../Entity/Ball.h"

void Attack::Start(RugbyMan* _npc)
{

}

void Attack::Update(RugbyMan* _npc)
{
	SceneRugby* scene = _npc->GetScene<SceneRugby>();
	for (int i = 0; i < scene->m_npcs.size(); i++)
	{
		if (scene->m_npcs[i] == scene->m_ball->GetNpcWithBall())
		{
			sf::Vector2f p1 = scene->m_npcs[i]->GetPosition();
			sf::Vector2f p2 = _npc->GetPosition();
			sf::Vector2f direction = sf::Vector2f(p1.x - p2.x, p1.y - p2.y);
			Utils::Normalize(direction);
			_npc->SetDirection(direction.x, direction.y, _npc->GetSpeed());
			break;
		}
	}
}

void Attack::End(RugbyMan* _npc)
{
}
