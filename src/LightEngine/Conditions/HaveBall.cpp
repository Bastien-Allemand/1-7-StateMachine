#include "HaveBall.h"
#include "../Scene/SceneRugby.h"

bool HaveBall::OnTest(RugbyMan* owner)
{
	SceneRugby* scene = owner->GetScene<SceneRugby>();

	return owner == scene->GetPlayerBall();
}
