#pragma once
#include "../Engine/Scene.h"
#include <vector>

class RugbyMan;
class Ball;

class SceneRugby : public Scene
{
	std::pair<int, int> m_score;

	bool m_resetmatch = false;
public:
	enum tag
	{
		ALLY,
		ENEMY,
		BALL,

		count
	};

	std::vector<RugbyMan*> m_npcs;

	Ball* m_ball;
private:


	RugbyMan* m_player_selected;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void TrySetSelectedEntity(RugbyMan* pEntity, int x, int y);
	void OnUpdate() override;
	void DebugShoot();
	void Debugfield();
	void DebugMessagebox();
	void ResetPosition();
	void GiveBall(RugbyMan* _npc);
	RugbyMan* GetPlayerWithBall();
	tag GetOppositeTag(RugbyMan* pEntity) const;
	SceneRugby::tag GetTag(RugbyMan* pEntity) const;
	RugbyMan* GetPlayerBall() const;
};

