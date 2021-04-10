#include <chrono>
#include <iostream>
#include "DEBUG.h"

#include "BaseGameMode.h"

BaseGameMode::BaseGameMode()
{
	m_Manager = new GameManager();

	m_IsGameRunning = false;

	if (DEBUG)
		std::cout << typeid(this).name() << " has been created! " << std::endl;
}

BaseGameMode::~BaseGameMode()
{
	delete m_Manager;
}

bool BaseGameMode::StartGame()
{
	m_IsGameRunning = true;

	// Initialize
	m_Manager->Init();

	while (m_IsGameRunning)
	{
		m_Manager->Update();
	}

	return true;
}
