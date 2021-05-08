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

	char* m_InputBuffer;

	Move m_CurrentMove;

    GameStateList m_GameStateList;

	union
	{
		struct 
		{
            uint8_t IsStaleMate:1;
            uint8_t IsWhitesTurn:1;
            uint8_t IsGameRunning:1;
			uint8_t RestartGame:1;
		} FlagsFlags;
		uint8_t m_Flags;
	};

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
	inline void ChangeTurn() { FlagsFlags.IsWhitesTurn = !FlagsFlags.IsWhitesTurn; }

	inline void IsAStalemate(bool value) { FlagsFlags.IsStaleMate = value; }

	inline void GameOver() { FlagsFlags.IsGameRunning = false; }
};

