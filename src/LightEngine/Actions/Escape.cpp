#include "Escape.h"
#include "../Scene/SceneRugby.h"
#include "../Engine/Utils.h"

void Escape::Start(RugbyMan* _npc)
{
}

void Escape::Update(RugbyMan* _npc)
{
	SceneRugby* scene = _npc->GetScene<SceneRugby>();
	
	for (RugbyMan* npc : scene->m_npcs)
	{
		if ((_npc->IsTag(scene->GetOppositeTag(npc))))
		{

			sf::Vector2f p1 = npc->GetPosition();
			sf::Vector2f p2 = _npc->GetPosition();

			if (Utils::GetDistance(p1.x, p1.y, p2.x, p2.y) <= 100 && _npc->IsTag(scene->GetOppositeTag(npc)))
			{
				//contournement
				sf::Vector2f direction = p2 - p1;
				Utils::Normalize(direction);
				float speed = _npc->GetSpeed();
				float movey = 0;
				if (p1.y > p2.y)
				{
					movey = -1;
				}
				else
				{
					movey = 1;
				}
				if(_npc->IsTag(scene->GetTag(_npc))== scene->ALLY )
				{
					_npc->SetDirection(1, direction.y + movey, speed);
				}
				else {
					_npc->SetDirection(-1, direction.y + movey, speed);

				}
			}
		}
	}
}

void Escape::End(RugbyMan* _npc)
{
}
