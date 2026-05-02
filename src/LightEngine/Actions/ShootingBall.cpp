#include "ShootingBall.h"
#include "../Scene/SceneRugby.h"
#include "../Engine/Utils.h"
#include "../Entity/Ball.h"
#include "../Entity/RugbyMan.h"
#include "../Engine/Debug.h"

void ShootingBall::Start(RugbyMan* _npc)
{
}

void ShootingBall::Update(RugbyMan* _npc)
{


	sf::Vector2f p2;
	sf::Vector2f p3;
	_npc->SetDirection(0, 0);

	SceneRugby* scene = _npc->GetScene<SceneRugby>();
	if (_npc != scene->m_ball->GetNpcWithBall())
		return;
	if (_npc->GetIfHasPassed())
		return;

	p2 = _npc->GetPosition();
	SceneRugby* pScene = _npc->GetScene<SceneRugby>();

	float dist = NULL;
	RugbyMan* NPCToShoot = scene->m_npcs[0];

	for (RugbyMan* npc : scene->m_npcs) {
		if (npc != _npc && npc->IsTag(scene->GetTag(_npc))) {
			sf::Vector2f p1 = npc->GetPosition();
			if (Utils::GetDistance(p1.x, p1.y, p2.x, p2.y) <= dist || dist == NULL) {
				dist = Utils::GetDistance(p1.x, p1.y, p2.x, p2.y);
				NPCToShoot = npc;
			}
		}
	}

	p3 = NPCToShoot->GetPosition();

	sf::Vector2f direction = sf::Vector2f(p3.x - p2.x, p3.y - p2.y);

	Debug::DrawLine(p2.x, p2.y, p3.x, p3.y, sf::Color::Red);

	sf::Vector2f ballpos = scene->m_ball->GetPosition();



	scene->m_ball->SetNpcWithBall(nullptr);

	scene->m_ball->SetDirection(direction.x, direction.y, 100);

	_npc->SetIfHasPassed(true);
	

	

}

void ShootingBall::End(RugbyMan* _npc)
{
}
