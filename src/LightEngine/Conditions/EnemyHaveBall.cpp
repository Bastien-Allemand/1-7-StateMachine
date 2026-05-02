#include "EnemyHaveBall.h"
#include "../Scene/SceneRugby.h"

bool EnemyHaveBall::OnTest(RugbyMan* owner)
{
	SceneRugby* scene = owner->GetScene<SceneRugby>();

	RugbyMan* player = scene->GetPlayerBall();

	if (player != nullptr)
	{
		return player->IsTag(scene->GetOppositeTag(owner));
	}
	return false;

}
