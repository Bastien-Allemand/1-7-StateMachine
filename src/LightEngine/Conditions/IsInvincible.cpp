#include "IsInvincible.h"
#include "../Scene/SceneRugby.h"

bool IsInvincible::OnTest(RugbyMan* owner)
{
	return owner->GetIfInvincible();
}
