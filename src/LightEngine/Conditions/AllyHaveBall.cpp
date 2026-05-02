#include "AllyHaveBall.h"
#include "../Scene/SceneRugby.h"

bool AllyHaveBall::OnTest(RugbyMan* owner)
{
	SceneRugby* scene = owner->GetScene<SceneRugby>();
	RugbyMan* player = scene->GetPlayerBall();

	if (player != nullptr)
		return player->IsTag(scene->GetTag(owner));

	return false;
}
