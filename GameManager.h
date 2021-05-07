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

	bool m_IsWhitesTurn = true;

	char* m_InputBuffer;

	Move m_CurrentMove;

    GameStateList m_GameStateList;

	bool m_IsStaleMate = false;

	bool m_IsGameRunning = true;

	bool m_RestartGame = false;

public:
	GameManager();
	~GameManager();
	void Init();
	void Reinit();
	bool StartGame();
	void Update();
	void ReDraw();
	void FlipACoin() const;
	void PrintHelp() const;

	bool ParseMove(Move* moveToParse);
	bool ParseCommand();
	inline void ChangeTurn() { m_IsWhitesTurn = !m_IsWhitesTurn; }

	inline void IsAStalemate(bool value) { m_IsStaleMate = value; }

	inline void GameOver() { m_IsGameRunning = false; }
};

