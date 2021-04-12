#include "DEBUG.h"
#include <assert.h>
#include <iostream>

#include "Player.h"
#include "Piece.h"
#include "PieceState.h"
#include "GameState.h"
#include "GameManager.h"

Player::Player()
	: m_IsWhitePlayer(false), m_Board(nullptr), m_NbOfPieces(0), m_Opponent(nullptr), m_King(nullptr), m_Manager(nullptr)
{
	for (int index = 0; index < max_nb_pieces; index++)
	{
		m_Pieces[index] = nullptr;
	}

	if (DEBUG)
		std::cout << typeid(this).name() << " has been created! " << std::endl;
}

Player::~Player()
{
}


void Player::Init(Board* board, Player* opponent, GameManager* manager, bool isWhitePlayer)
{
	isWhitePlayer ? m_PlayerID = "White" : m_PlayerID = "Black";

	m_Board = board;
	m_IsWhitePlayer = isWhitePlayer;
	m_Opponent = opponent;
	m_Manager = manager;

	SetupBoard();
}

void Player::SetupBoard()
{
	int pawnRow = m_IsWhitePlayer ? 6 : 1;
	int piecesRow = m_IsWhitePlayer ? 7 : 0;

	// Pawns
	//for (unsigned int i = 0; i < Board::GetBoardWidth(); i++)
	//{
	//	AddPiece(PieceType::Piece_Pawn, Point(i, pawnRow));
	//}

	// Pieces
	//AddPiece(PieceType::Piece_Rook, Point(0, piecesRow));
	//AddPiece(PieceType::Piece_Rook, Point(7, piecesRow));

	//AddPiece(PieceType::Piece_Knight, Point(1, piecesRow));
	//AddPiece(PieceType::Piece_Knight, Point(6, piecesRow));

	//AddPiece(PieceType::Piece_Bishop, Point(2, piecesRow));
	//AddPiece(PieceType::Piece_Bishop, Point(5, piecesRow));

	//AddPiece(PieceType::Piece_Queen, Point(3, piecesRow));
	//AddPiece(PieceType::Piece_King, Point(4, piecesRow));

	//Pawn promotion testing
	//if (IsWhitePlayer())
	//{
	//	AddPiece(PieceType::Piece_Pawn, Point(3, 1));
	//}

	//if (!IsWhitePlayer())
	//{
	//	AddPiece(PieceType::Piece_Pawn, Point(3, 6));
	//}

	// Checkmate in 1
	if (IsWhitePlayer())
	{
		AddPiece(PieceType::Piece_Rook, Point(0, 7));
		AddPiece(PieceType::Piece_Rook, Point(2, 7));
	}

	if (!IsWhitePlayer())
	{
		AddPiece(PieceType::Piece_King, Point(0, 0));
	}
}

void Player::PreTurnSetup()
{
	SetAllAttackedCells();

	if (IsKingChecked())
	{
		IsKingCheckMated();
	}
}

void Player::SetAllAttackedCells()
{
	Piece** pieces = m_Opponent->GetPieces();

	if (*pieces)
	{
		m_Board->ResetAttackedCells();

		for (int i = 0; i < m_Opponent->GetNbOfPieces(); i++)
		{
			pieces[i]->SetAttackedCells();
		}
	}
}

bool Player::MovePiece(Piece* piece, Point position)
{
	assert(piece);
	if (piece->IsLegalMove(position))
	{
		// Save state since we simulate the move for king checks
		GameState preMoveState(m_IsWhitePlayer, *this, *(GetOpponent()));

		BoardCell* moveFrom = m_Board->GetBoardCell(Board::GetIndexFromPosition(piece->GetPosition()));
		BoardCell* moveTo = m_Board->GetBoardCell(Board::GetIndexFromPosition(position));
		piece->Move(moveFrom, moveTo);

		// Allows to check if king is checked
		SetAllAttackedCells();

		if (IsKingChecked())
		{
			std::cout << "Illegal Move Error: The king is in check after this move." << std::endl;
			m_Board->SetState(preMoveState);

			return false;
		}

		// Check for pawn promotion
		if (Pawn* pawn = dynamic_cast<Pawn*>(piece))
		{
			if (pawn->CanPromote())
			{
				PromotePawn(pawn);
			}
		}

		m_Board->SetLastPieceMoved(piece);

		return true;
	}
	else
	{
		std::cout << "Illegal Move Error: This move is not considered legal, try something else." << std::endl;
		return false;
	}
}

void Player::AddPiece(PieceType type, Point position, int index /*= -1*/)
{
	bool shouldIncNbOfPieces = false;

	// -1 is default, meaning we are setting up the first pieces. 
	if (index == -1)
	{
		index = m_NbOfPieces;
		shouldIncNbOfPieces = true;
	}
	// Otherwise we're replacing an existing piece
	else
	{
		delete m_Pieces[index];
	}

	switch (type)
	{
		case PieceType::Piece_Pawn:
			m_Pieces[index] = new Pawn(position, this);
			break;
		case PieceType::Piece_Bishop:
			m_Pieces[index] = new Bishop(position, this);
			break;
		case PieceType::Piece_Rook:
			m_Pieces[index] = new Rook(position, this);
			break;
		case PieceType::Piece_Knight:
			m_Pieces[index] = new Knight(position, this);
			break;
		case PieceType::Piece_Queen:
			m_Pieces[index] = new Queen(position, this);
			break;
		case PieceType::Piece_King:
			King* newKing = new King(position, this);
			m_Pieces[index] = newKing;
			m_King = newKing;
	}
	
	m_Pieces[index]->Init(m_Board);

	if (shouldIncNbOfPieces)
	{
		m_NbOfPieces++;
	}
}

bool Player::MakeMove(Move* moveToMake)
{
	BoardCell* fromCell = m_Board->GetBoardCell(Board::GetIndexFromPosition(moveToMake->fromPoint));
	BoardCell* toCell = m_Board->GetBoardCell(Board::GetIndexFromPosition(moveToMake->toPoint));
	
	// Check if we're trying to move a piece
	if (!fromCell->IsOccupied())
	{
		std::cout << "Piece Selection Error: FROM position has no piece." << std::endl;
		return false;
	}
	else
	{
		// Check if moving the right piece
		if (fromCell->GetOccupant()->IsWhitePiece() != m_IsWhitePlayer)
		{
			if (m_IsWhitePlayer)
			{
				std::cout << "Piece Color Error: White is trying to move a Black piece." << std::endl;
				return false;
			}
			else
			{
				std::cout << "Piece Color Error: Black is trying to move a White piece." << std::endl;
				return false;
			}
		}
	}

	return MovePiece(fromCell->GetOccupant(), moveToMake->toPoint);
}

bool Player::IsKingChecked() const
{
	if (m_King && m_King->IsChecked())
	{
		std::cout << m_PlayerID << "'s King is in Check." << std::endl;
		return true;
	}
	
	return false;
}

bool Player::IsKingCheckMated()
{
	GameState originalState(m_IsWhitePlayer, *this, *m_Opponent);

	for (int index = 0; index < max_nb_pieces; index++)
	{
		Piece* piece = m_Pieces[index];

		if (piece)
        {
            const Point* pieceMoves = piece->GetPossibleMoves();

            for (int moveIndex = 0; moveIndex < piece->GetNbOfMoves(); moveIndex++)
            {
                BoardCell* moveTo = m_Board->GetBoardCell(piece->GetPosition() + pieceMoves[moveIndex]);
                piece->Move(moveTo);
                SetAllAttackedCells();

                if (!IsKingChecked())
                {
                    m_Board->SetState(originalState);
                    return false;
                }

                m_Board->SetState(originalState);
            }
        }
	}

	std::cout << "Checkmate!" << std::endl;
	m_Manager->GameOver();

	return true;
}

void Player::PromotePawn(Pawn* pawn)
{
	PieceType type = pawn->AskForPromotion();

	if (type == PieceType::Piece_NULL)
	{
		std::cout << "Piece type == Piece_NULL" << std::endl;
		return;
	}

	for (int index = 0; index < max_nb_pieces; index++)
	{
		if (m_Pieces[index] == pawn)
		{
			AddPiece(type, pawn->GetPosition(), index);
		}
	}
}

void Player::SetPieces(PieceState* states)
{
	for (int i = 0; i < max_nb_pieces; i++)
	{
		states[i].GetPiece()->Move(states[i]);
	}
}