#include "Scoreing.h"
#include "../Scene/SceneRugby.h"
#include "../Engine/Utils.h"
#include "../Conditions/EnemyInArea.h"

void Scoreing::Start(RugbyMan* _npc)
{
}

void Scoreing::Update(RugbyMan* _npc)
{
	SceneRugby* scene = _npc->GetScene<SceneRugby>();

	if (scene->GetTag(_npc) == scene->ENEMY)
	{
		sf::Vector2f direction = sf::Vector2f(-1, 0);
		_npc->SetDirection(direction.x, direction.y, _npc->GetSpeed());
	}
	else if (scene->GetTag(_npc) == scene->ALLY)
	{
		sf::Vector2f direction = sf::Vector2f(1, 0);
		_npc->SetDirection(direction.x, 0, _npc->GetSpeed());
	}
}

void Scoreing::End(RugbyMan* _npc)
{
}
