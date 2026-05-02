
#include <SFML/Graphics.hpp>
//
#include "Engine/GameManager.h"
#include "Scene/SceneRugby.h"
//
#include <cstdlib>
#include <crtdbg.h>
#include <time.h>
#include <iostream>

int main() 
{
	srand(time(NULL));

    GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1800, 700, "Gameplay", 100,sf::Color::Black);

	pInstance->LaunchScene<SceneRugby>();



	return 0;
}