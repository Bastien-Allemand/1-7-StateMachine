#include "HasPass.h"

bool HasPass::OnTest(RugbyMan* owner)
{
	return owner->GetIfHasPassed();
}