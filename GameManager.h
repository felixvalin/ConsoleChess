#pragma once

#include <array>

#include "Player.h"
#include "Board.h"
#include "GameState.h"
#include "GameStateList.h"

struct Move;

class GameManager
{
private: 

	Board m_Board;

	Player m_WhitePlayer;
	Player m_BlackPlayer;
	Player* m_CurrentPlayer;

	bool m_IsWhitesTurn;

	char* m_InputBuffer;

	Move m_CurrentMove;

	GameStateList m_GameStateList;

	bool m_IsGameRunning = false;

public:
	GameManager();
	~GameManager();
	void Init();
	bool StartGame();
	void Update();
	void ReDraw();

	bool ParseMove(Move* moveToParse);
	bool ParseCommand();
	inline void ChangeTurn() { m_IsWhitesTurn = !m_IsWhitesTurn; }

	inline void GameOver() { m_IsGameRunning = false; }
};

