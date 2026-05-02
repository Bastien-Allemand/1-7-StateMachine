#include "EnemyInArea.h"
#include "../Scene/SceneRugby.h"
#include "../Engine/Utils.h"

bool EnemyInArea::OnTest(RugbyMan* owner)
{
	SceneRugby* scene = owner->GetScene<SceneRugby>();

	bool rep = false;

	for (RugbyMan* npc : scene->m_npcs)
	{
		if ((owner->IsTag(scene->GetOppositeTag(npc))))
		{

			sf::Vector2f p1 = npc->GetPosition();
			sf::Vector2f p2 = owner->GetPosition();

			if (Utils::GetDistance(p1.x, p1.y, p2.x, p2.y) <= 200)
			{

				if (npc->IsTag(SceneRugby::ALLY)){
					if (p2.x >= p1.x) { rep = true; }
					else { rep = false; }
				}

				if (npc->IsTag(SceneRugby::ENEMY)){
					if (p2.x <= p1.x) { rep = true;	}
					else { rep = false; }
				}
			}
		}
	}
	return rep;
}
