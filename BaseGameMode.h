#pragma once

#include <chrono>
#include "GameManager.h"
#include "Player.h"

class BaseGameMode
{
private:
	GameManager* m_Manager;

	bool m_IsGameRunning;

public:

	BaseGameMode();
	~BaseGameMode();

	bool StartGame();
};

