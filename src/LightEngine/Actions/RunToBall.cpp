#include "RunToBall.h"
#include "../Scene/SceneRugby.h"
#include "../Engine/Utils.h"
#include "../Entity/Ball.h"

void RunToBall::Start(RugbyMan* _npc)
{
}

void RunToBall::Update(RugbyMan* _npc)
{
	sf::Vector2f pos = _npc->GetPosition();

	SceneRugby* pScene = _npc->GetScene<SceneRugby>();


	sf::Vector2f pos1 = pScene->m_ball->GetPosition();

	sf::Vector2f direction = sf::Vector2f((pos1.x - pos.x), (pos1.y - pos.y));
	Utils::Normalize(direction);
	_npc->SetDirection(direction.x, direction.y, _npc->GetSpeed());
}

void RunToBall::End(RugbyMan* _npc)
{
}
