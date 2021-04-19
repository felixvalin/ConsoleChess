	#pragma once
#include "GameState.h"

struct GameStateListItem
{
	GameStateListItem* previous;
	GameStateListItem* next;
	GameState state;

	GameStateListItem(GameState _state)
		: previous(nullptr),
		next(nullptr),
		state(_state)
	{
	}

	GameStateListItem() = delete;
};

class GameStateList
{
private:
	GameStateListItem* m_Cursor;
	GameStateListItem* m_Head;

public:
	GameStateList();
	~GameStateList();

	void Reinit();

	void AddGameState(const GameState& state);
	void DeleteGameState();

	void CursorToNext();
	void CursorToPrevious();
	void CursorToHead();

	inline bool IsCursorAtHead() { return m_Cursor == m_Head; }

	GameState& GetCursorState() const;
	GameState& GetHeadState() const;
};