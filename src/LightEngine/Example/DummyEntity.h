#pragma once
#include "../Engine/Entity.h"

class DummyEntity : public Entity
{
public:
	void OnCollision(Entity* other) override;
};

