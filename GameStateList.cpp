#include "DEBUG.h"
#include <cassert>
#include <iostream>

#include "GameStateList.h"

GameStateList::GameStateList()
	: m_Head(nullptr),
	m_Cursor(nullptr)
{
	if (DEBUG)
		std::cout << typeid(this).name() << " has been created! " << std::endl;
}

GameStateList::~GameStateList()
{
	if (m_Head)
	{
		GameStateListItem* tempCursor = m_Head;

		while (tempCursor->previous != nullptr)
		{
			tempCursor = tempCursor->previous;
			delete tempCursor->next;
		}
	}

	m_Head = nullptr;
	m_Cursor = nullptr;
}

void GameStateList::AddGameState(const GameState& state)
{
	// Adds a new item to the list, also updates the cursor to the head of the list.
	if (m_Head)
	{
		GameStateListItem* newGameState = new GameStateListItem(state);
		m_Head->next = newGameState;
		newGameState->previous = m_Head;
		m_Head = newGameState;
	}
	else // It means this is the first state we're adding
	{
		m_Head = new GameStateListItem(state);
	}

	m_Cursor = m_Head;
}

void GameStateList::CursorToNext()
{
	if (m_Cursor->next)
	{
		m_Cursor = m_Cursor->next;
	}
	else
	{
		// This gets cleared before the player gets to read it...
		std::cout << "There is no Next item in this GameStateList." << std::endl;
	}
}

void GameStateList::CursorToPrevious()
{
	if (m_Cursor->previous)
	{
		m_Cursor = m_Cursor->previous;
	}
	else
	{
		// This gets cleared before the player gets to read it...
		std::cout << "There is no Previous item in this GameStateList." << std::endl;
	}
}

void GameStateList::CursorToHead()
{
	if (m_Head)
	{
		m_Cursor = m_Head;
	}
	else
	{
		std::cout << "The list is empty: m_Head == nullptr" << std::endl;
	}
}

GameState& GameStateList::GetCursorState() const
{
	assert(m_Cursor && "The cursor pointer is null.");

	return m_Cursor->state;
}

GameState& GameStateList::GetHeadState() const
{
	assert(m_Head && "The cursor pointer is null.");

	return m_Head->state;
}

void GameStateList::DeleteGameState()
{
	if (m_Head)
	{
		m_Head = m_Head->previous;
		delete m_Head->next;
	}
}