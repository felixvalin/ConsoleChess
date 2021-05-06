#include "DEBUG.h"
#include <iostream>

#include "Piece.h"
#include "PieceState.h"
#include "Player.h"
#include "HasMoved.h"

Piece::Piece()
	: m_PieceID('d'),
	m_Board(nullptr),
	m_Directions(nullptr),
	m_NbOfDirections(0),
	m_Player(nullptr),
	m_PossibleMovesIndex(0)
{
}

Piece::Piece(Player* player)
    : m_PieceID('d'),
    m_Board(nullptr),
    m_Directions(nullptr),
    m_NbOfDirections(0),
    m_Player(player),
    m_PossibleMovesIndex(0)
{
	m_PieceID = toupper(m_PieceID);

    if (DEBUG)
        std::cout << typeid(this).name() << " has been created! " << std::endl;
}

Piece::~Piece()
{
	delete[] m_Directions;
}

void Piece::Init(Board* board, Point position)
{
	m_Board = board;
	board->AddPiece(this, position);
}

void Piece::ResetPossibleMoves()
{
	for (int i = 0; i < max_possible_moves; i++)
	{
		m_PossibleMoves[i] = Point();
	}

	m_PossibleMovesIndex = 0;
}

void Piece::SetPieceID(char id)
{
	m_PieceID = toupper(id);// : m_PieceID = id;
}

bool Piece::IsWhitePiece() const
{
	return m_Player->IsWhitePlayer();
}

void Piece::CheckPossibleMoves()
{
	if (m_IsDead)
	{
		if (m_PossibleMovesIndex != 0)
		{
			ResetPossibleMoves();
		}

		return;
	}

	ResetPossibleMoves();
	m_PossibleMovesIndex = 0;

	for (int i = 0; i < m_NbOfDirections; i++)
	{
		bool canMoveFurther = true;
		Point currentPosition = m_Board->GetPiecePosition(this);

		while (canMoveFurther && m_PossibleMovesIndex <= max_possible_moves)
		{
			// Increment position with direction vector
			currentPosition = currentPosition + m_Directions[i];

			// Check if position is out of the board
			if (Board::IsOutOfBoard(currentPosition))
			{
				break;
			}

			// Get the cell
			BoardCell* currentCell = m_Board->GetBoardCell(Board::GetIndexFromPosition(currentPosition));

			// Check occupancy
			if (currentCell->IsOccupied())
			{
				canMoveFurther = false;
			}

			// Add to possible moves
			m_PossibleMoves[m_PossibleMovesIndex] = currentCell->GetPosition();
			m_PossibleMovesIndex++;

			// if we're moving the king or the knight, we can only move once in every direction
			if (toupper(m_PieceID) == 'K' || toupper(m_PieceID) == 'N')
			{
				canMoveFurther = false;
			}
		}
	}
}

bool Piece::IsLegalMove(Point point)
{
	CheckPossibleMoves();

	for (Point* i = m_PossibleMoves; (i - m_PossibleMoves) < max_possible_moves; i++)
	{
		if (i)
		{
			BoardCell* possibleMoveCell = m_Board->GetBoardCell(point);

			if (possibleMoveCell->IsOccupied() && possibleMoveCell->GetOccupant()->IsWhitePiece() == IsWhitePiece())
			{
				return false;
			}

			if (i->x == point.x && i->y == point.y)
				return true;
		}
		else
		{
			break;
		}
	}

	return false;
}

void Piece::Move(BoardCell* moveTo)
{
	Move(m_Board->GetBoardCell(this), moveTo);
}

void Piece::Move(BoardCell* moveFrom, BoardCell* moveTo)
{
	if (moveFrom == moveTo)
	{
		std::cout << "Wrong Move Error: moveFrom == moveTo" << std::endl;
		return;
	}

    moveFrom->RemovePiece(false);
    moveTo->AddPiece(this);
}

bool Piece::IsLastPieceMoved() const
{
	return m_Board->GetLastPieceMoved() == this;
}

void Piece::Move(const PieceState& state)
{
	Move(m_Board->GetBoardCell(this), m_Board->GetBoardCell(state.GetPosition()));
}

void Piece::SetAttackedCells()
{
	CheckPossibleMoves();
	for (int i = 0; i < m_PossibleMovesIndex; i++)
	{
		BoardCell* cell = m_Board->GetBoardCell(m_PossibleMoves[i]);
		cell->AddAttacker(this);
	}
}