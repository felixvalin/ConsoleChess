#include "DEBUG.h"
#include "Pawn.h"
#include "Player.h"

#include <iostream>

Pawn::Pawn(Player* player)
	: Piece::Piece(player)
{
	SetPieceID('p');
	m_IsFirstMove = true;

	player->IsWhitePlayer() ? m_ForwardDirection = -1 : m_ForwardDirection = 1;

	m_Diagonals[0] = Point(-1, m_ForwardDirection);
	m_Diagonals[1] = Point(1, m_ForwardDirection);

	m_PromotionRow = IsWhitePiece() ? 0 : 7;

	if (DEBUG)
		std::cout << typeid(this).name() << " has been created! " << std::endl;
}

Pawn::~Pawn()
{
}

void Pawn::CheckPossibleMoves()
{
	ResetPossibleMoves();
	unsigned int maxDistance;
	m_PossibleMovesIndex = 0;

	Point currentPosition = m_Board->GetPiecePosition(this);

	if (m_IsFirstMove)
	{
		maxDistance = 2;
	}
	else
	{
		maxDistance = 1;
	}

	// Forward movement
	BoardCell* forwardCell = m_Board->GetBoardCell(currentPosition + Point(0, m_ForwardDirection));

	if (!forwardCell->IsOccupied())
	{
		m_PossibleMoves[m_PossibleMovesIndex] = forwardCell->GetPosition();
		m_PossibleMovesIndex++;
	}

	if (m_IsFirstMove)
	{
		BoardCell* secondForwardCell = m_Board->GetBoardCell(currentPosition + Point(0, 2 * m_ForwardDirection));

		if (!secondForwardCell->IsOccupied())
		{
			m_PossibleMoves[m_PossibleMovesIndex] = secondForwardCell->GetPosition();
			m_PossibleMovesIndex++;
		}
	}

	// Kill moves (Diagonals)
	BoardCell* firstDiagCell = !Board::IsOutOfBoard(currentPosition + m_Diagonals[0]) ? m_Board->GetBoardCell(currentPosition + m_Diagonals[0]) : nullptr;
	BoardCell* secondDiagCell = !Board::IsOutOfBoard(currentPosition + m_Diagonals[1]) ? m_Board->GetBoardCell(currentPosition + m_Diagonals[1]) : nullptr;

	if (firstDiagCell)
	{
		m_PossibleMoves[m_PossibleMovesIndex] = firstDiagCell->GetPosition();
		m_PossibleMovesIndex++;
	}

	if (secondDiagCell)
	{
		m_PossibleMoves[m_PossibleMovesIndex] = secondDiagCell->GetPosition();
		m_PossibleMovesIndex++;
	}

	// En passant
	if ((IsWhitePiece() && currentPosition.y == 3) || (!IsWhitePiece() && currentPosition.y == 4))
	{
		BoardCell* firstEnPassantCell = m_Board->GetBoardCell(currentPosition + Point(1, 0));
		BoardCell* secondEnPassantCell = m_Board->GetBoardCell(currentPosition + Point(-1, 0));

		if (Pawn* pawn = dynamic_cast<Pawn*>(firstEnPassantCell->GetOccupant()))
		{
			if (pawn->IsLastPieceMoved())
			{
				m_PossibleMoves[m_PossibleMovesIndex] = firstEnPassantCell->GetPosition() + Point(0, m_ForwardDirection);
				m_PossibleMovesIndex++;
			}
		}

		if (Pawn* pawn = dynamic_cast<Pawn*>(secondEnPassantCell->GetOccupant()))
		{
			if (pawn->IsLastPieceMoved())
			{
				m_PossibleMoves[m_PossibleMovesIndex] = secondEnPassantCell->GetPosition() + Point(0, m_ForwardDirection);
				m_PossibleMovesIndex++;
			}
		}
	}
}

bool Pawn::IsLegalMove(Point point)
{
	if (!Piece::IsLegalMove(point))
	{
		return false;
	}

	if (point.x != m_Board->GetPiecePosition(this).x)
	{
		BoardCell* cell = m_Board->GetBoardCell(point);
		return cell->IsOccupied() && (cell->GetOccupant()->IsWhitePiece() != IsWhitePiece());
	}

	return true;
}

void Pawn::Move(BoardCell* moveFrom, BoardCell* moveTo)
{
	bool isEnPassant = IsEnPassantMove(moveFrom, moveTo);
	if (isEnPassant)
	{
		// Get the board cell that contains the piece to kill, then remove it from the board.
		BoardCell* cellToRemove = m_Board->GetBoardCell(Point(moveTo->GetPosition().x, moveFrom->GetPosition().y));
		cellToRemove->RemovePiece();
	}

	moveTo->AddPiece(this);
	moveFrom->RemovePiece();
	//m_Position = moveTo->GetPosition();
}

bool Pawn::IsEnPassantMove(BoardCell* moveFrom, BoardCell* moveTo) const
{
	// If we're moving diagonally and there's no opposing piece, we're moving En Passant
	return moveFrom->GetPosition().x != moveTo->GetPosition().x && !moveTo->IsOccupied();
}

void Pawn::SetAttackedCells()
{
    Point currentPosition = m_Board->GetPiecePosition(this);

	for (int i = 0; i < 2; i++)
	{
		if (!Board::IsOutOfBoard(currentPosition + m_Diagonals[i]))
		{
			m_Board->GetBoardCell(currentPosition + m_Diagonals[i])->AddAttacker(this);
		}
	}
}

PieceType Pawn::AskForPromotion()
{
	char promotionInput;
	PieceType pieceType = PieceType::Piece_NULL;
	Piece* promotedPiece = nullptr;

	while (pieceType == PieceType::Piece_NULL)
	{
		std::cout << "Pawn Promotion [Q/R/B/N]: ";
		std::cin >> promotionInput;
		promotionInput = toupper(promotionInput);

		switch (promotionInput)
		{
		case 'Q':
			pieceType = PieceType::Piece_Queen;
			break;
		case 'R':
			pieceType = PieceType::Piece_Rook;
			break;
		case 'B':
			pieceType = PieceType::Piece_Bishop;
			break;
		case 'N':
			pieceType = PieceType::Piece_Knight;
			break;
		default:
			std::cout << "Unknown piece type! Try again." << std::endl;
		}
	}
	
	return pieceType;
}

bool Pawn::CanPromote() const
{
	return m_Board->GetPiecePosition(this).y == m_PromotionRow;
}
