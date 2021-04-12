#include "DEBUG.h"
#include <iostream>
#include <ctype.h>

#include "GameManager.h"

GameManager::GameManager()
	: m_CurrentPlayer(nullptr),
	m_IsWhitesTurn(true),
	m_InputBuffer(new char[5])
{
	if (DEBUG)
		std::cout << typeid(this).name() << " has been created! " << std::endl;
}

GameManager::~GameManager()
{
	delete[] m_InputBuffer;
	m_InputBuffer = nullptr;

	if (DEBUG)
		std::cout << typeid(this).name() << " has been destroyed! " << std::endl;
}

void GameManager::Init()
{
	m_WhitePlayer.Init(&m_Board, &m_BlackPlayer, this, true);
	m_BlackPlayer.Init(&m_Board, &m_WhitePlayer, this, false);

	// Save initial state
	m_GameStateList.AddGameState(GameState(m_IsWhitesTurn, m_WhitePlayer, m_BlackPlayer));
}

bool GameManager::StartGame()
{
	m_IsGameRunning = true;

	while (m_IsGameRunning)
	{
		Update();
	}

	return true;
}

void GameManager::Update()
{
	m_IsWhitesTurn ? m_CurrentPlayer = &m_WhitePlayer : m_CurrentPlayer = &m_BlackPlayer;
	m_CurrentPlayer->PreTurnSetup();

	m_Board.Draw(CLEARBUFFER);

	do {
		if (m_IsGameRunning)
		{
			std::cout << std::endl;
			std::cout << m_CurrentPlayer->GetPlayerID() << "'s move: ";
			std::cin >> m_InputBuffer;
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Enter any text to terminate.";
			char input;
			std::cin >> input;
			break;
		}
	} while (!ParseMove(&m_CurrentMove));

	// Save GameState
	m_GameStateList.AddGameState(GameState(m_IsWhitesTurn, m_WhitePlayer, m_BlackPlayer));

	ChangeTurn();
}

void GameManager::ReDraw()
{
	// Set Cursor state as current state
	m_GameStateList.GetCursorState().UpdatePieces(m_Board);
	// Draw new state
	m_Board.Draw(CLEARBUFFER);

	if (!m_GameStateList.IsCursorAtHead())
	{
		std::cout << std::endl;
		std::cout << "/l : return to latest state." << std::endl;
	}

	// Reset to head state
	m_GameStateList.GetHeadState().UpdatePieces(m_Board);
}

bool GameManager::ParseMove(Move* moveToParse)
{
	if (!isalpha(m_InputBuffer[0]) || !isdigit(m_InputBuffer[1]) || !isalpha(m_InputBuffer[2]) || !isdigit(m_InputBuffer[3]))
	{
		if (m_InputBuffer[0] == '/')
		{
			return ParseCommand();
		}

		std::cout << "Move Format Error: moves must have the following format (without square brackets) -> [FROM letter coord][FROM digit coord][TO letter coord][TO digit coord] " << std::endl;
		return false;
	}
	else
	{
		Point fromCoord;
		Point toCoord;

		fromCoord.x = Board::GetRowIndexFromAlphaCoord(m_InputBuffer[0]);
		fromCoord.y = Board::GetColIndexFromNumCoord(m_InputBuffer[1]);

		toCoord.x = Board::GetRowIndexFromAlphaCoord(m_InputBuffer[2]);
		toCoord.y = Board::GetColIndexFromNumCoord(m_InputBuffer[3]);

		if (Board::IsOutOfBoard(fromCoord))
		{
			std::cout << "Out Of Board Error: FROM board cell is out of the board." << std::endl;
			return false;
		}
		if (Board::IsOutOfBoard(toCoord))
		{
			std::cout << "Out Of Board Error: TO board cell is out of the board." << std::endl;
			return false;
		}

		moveToParse->fromPoint = fromCoord;
		moveToParse->toPoint = toCoord;

		return m_CurrentPlayer->MakeMove(&m_CurrentMove);
	}
}

bool GameManager::ParseCommand()
{
	switch (m_InputBuffer[1])
	{
	case 'n': // next state
	{
		m_GameStateList.CursorToNext();
		ReDraw();
		std::cout << "Cursor has been moved to the next game state in the list." << std::endl;
		break;
	}
	case 'p': // previous state
	{
		m_GameStateList.CursorToPrevious();
		ReDraw();
		std::cout << "Cursor has been moved to the previous game state in the list." << std::endl;
		break;
	}
	case 'l': // latest state
	{
		m_GameStateList.CursorToHead();
		ReDraw();
		break;
	}
	case 'q': // quit
	{
		m_IsGameRunning = false;
		break;
	}
	return true;

	default:
		std::cout << "Command '" << m_InputBuffer[1] << "' is unknown." << std::endl;
	}

	return false;
}