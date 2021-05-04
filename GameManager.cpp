#include "DEBUG.h"
#include <iostream>
#include <ctype.h>

#include "GameManager.h"

GameManager::GameManager()
	: m_CurrentPlayer(nullptr),
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
	m_GameStateList.AddGameState(GameState(m_IsWhitesTurn, &m_Board));
}

void GameManager::Reinit()
{
	m_Board = Board();

	m_WhitePlayer.Reinit();
	m_WhitePlayer.Reinit();

	m_GameStateList.Reinit();

	m_IsGameRunning = true;
	m_IsWhitesTurn = true;

    // Save initial state
    m_GameStateList.AddGameState(GameState(m_IsWhitesTurn, &m_Board));
}

bool GameManager::StartGame()
{
	while (m_IsGameRunning)
	{
		Update();
	}

	return m_RestartGame;
}

void GameManager::Update()
{
	m_IsWhitesTurn ? m_CurrentPlayer = &m_WhitePlayer : m_CurrentPlayer = &m_BlackPlayer;
	// This must be where the eaten pieces are brought back on the board... 
	//m_CurrentPlayer->PreTurnSetup();

	m_Board.Draw(CLEARBUFFER);

    //if (!m_CurrentPlayer->GetOpponent()->IsKingCheckMated())
	if (true)
    {
        do {
            if (!m_IsGameRunning)
            {
                break;
            }

            std::cout << std::endl;
            std::cout << m_CurrentPlayer->GetPlayerID() << "'s move: ";
            std::cin >> m_InputBuffer;
            std::cout << std::endl;
        } while (!ParseMove(&m_CurrentMove));
    }
    else
    {
        do {
            if (!m_IsGameRunning)
            {
                break;
            }

            std::cout << m_CurrentPlayer->GetPlayerID() << " wins!" << std::endl;
            std::cout << std::endl;
            std::cout << "Game Over! You can review the game using the following commands:" << std::endl;
            std::cout << "/p : Go to previous move." << std::endl;
            std::cout << "/n : Go to next move." << std::endl;
            std::cout << "/l : Go to last move." << std::endl;
            std::cout << std::endl;
            std::cout << "/r : New game." << std::endl;
            std::cout << "/q : Quit game." << std::endl;
            std::cout << "Input: ";
            std::cin >> m_InputBuffer;
        } while (!ParseCommand());
    }

	// Save GameState
	m_GameStateList.AddGameState(GameState(m_IsWhitesTurn, &m_Board));

	//if (!m_CurrentPlayer->GetOpponent()->IsKingCheckMated())
	{
		ChangeTurn();
	}
}

void GameManager::ReDraw()
{
	// Set Cursor state as current state
	//m_GameStateList.GetCursorState().UpdatePieces(m_Board);
	m_Board.SetState(m_GameStateList.GetCursorState());
	// Draw new state
	m_Board.Draw(CLEARBUFFER);

	//if (!m_GameStateList.IsCursorAtHead())
	//{
		//std::cout << std::endl;
		//std::cout << "/l : return to latest state." << std::endl;
	//}

	// Reset to head state
	//m_GameStateList.GetHeadState().UpdatePieces(m_Board);
    m_Board.SetState(m_GameStateList.GetHeadState());

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
		m_RestartGame = false;
		break;
	}
    case 'r': // reset
    {
        m_RestartGame = true;
		m_IsGameRunning = false;
        break;
    }
	return true;

	default:
		std::cout << "Command '" << m_InputBuffer[1] << "' is unknown." << std::endl;
	}

	return false;
}