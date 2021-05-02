#include "DEBUG.h"
#include <iostream>
#include <array>

#include "Board.h"
#include "GameState.h"

Board::Board()
{
	for (int i = 0; i < s_BoardSize; i++)
	{
		m_Cells[i] = BoardCell(i, this);
	}

	if (DEBUG)
		std::cout << typeid(this).name() << " has been created! " << std::endl;
}

Board::~Board()
{
}

Point Board::GetPositionFromIndex(int cellIndex)
{
	return Point(cellIndex % s_BoardWidth, cellIndex / s_BoardWidth);
}

int Board::GetIndexFromPosition(Point position)
{
	return position.y * GetBoardWidth() + position.x;
}

bool Board::IsOutOfBoard(Point position)
{
	return position.x >= s_BoardWidth || position.x < 0 || position.y >= s_BoardWidth || position.y < 0;
}

void Board::PrintHorizontalLine()
{
	std::cout << "   ";
	for (int i = 0; i < s_BoardWidth; i++)
	{
		std::cout << " ---";
	}
	std::cout << std::endl;
}

void Board::Draw(bool shouldClearBuffer/*= true*/)
{
	//Clear the screen
	if (shouldClearBuffer)
		system("CLS");

	int currentCell = 0;
	int row = 1;

	for (int i = 0; i < s_BoardSize; i++)
	{
		// End of chessboard, print a horizontal line
		if (i % s_BoardWidth == 0)
		{
			PrintHorizontalLine();

			// And print row coords
			std::cout << " " << s_BoardWidth - (i / s_BoardWidth) << " ";
		}

		// Draw the cell
		m_Cells[i].Draw();
	}

	PrintHorizontalLine();

	// Print column coords
	std::cout << "   ";
	for (char col = 'a'; col <= 'h'; col++)
	{
		std::cout << "  " << col << " ";
	}
	std::cout << std::endl;
}

void Board::AddPiece(Piece* piece, Point position)
{
	m_Cells[GetIndexFromPosition(position)].AddPiece(piece);
}

Piece* Board::GetPieceAt(Point position) const
{
	return m_Cells[GetIndexFromPosition(position)].GetOccupant();
}

Point Board::GetPiecePosition(const Piece* piece) const
{
    for (int i = 0; i < s_BoardSize; i++)
    {
		if (m_Cells[i].GetOccupant() == piece)
		{
			return GetPositionFromIndex(i);
		}
    }

	return Point();
}

void Board::SetState(const GameState& state)
{
	//PROBLEMS HERE WHEN REVIVING PIECES....

	// Clear the board
	for (int i = 0; i < s_BoardSize; i++)
	{
        m_Cells[i].RemovePiece(false);
    }

	for (int i = 0; i < s_BoardSize; i++)
	{

		// Problem here: The piece that has its move simulated (in Player::IsKingChecked()) isn't placed back to its original position.
		if (Piece* piece = state.GetPieceOn(m_Cells[i].GetPosition()))
		{
			//piece->Move(&m_Cells[i]);
			//GetBoardCell(piece->GetPosition())->RemovePiece(false);
			//piece->Revive();
			//piece->Move(GetBoardCell(state.GetPieceState(piece)->GetPosition()));
			//piece->SetPosition(state.GetPieceState(piece)->GetPosition());
			m_Cells[i].AddPiece(piece);
			//piece->SetPosition(m_Cells[i].GetPosition());
		}
		/*else
		{
			GetBoardCell(i)->RemovePiece();
		}*/
	}
}

void Board::ResetAttackedCells()
{
	for (int i = 0; i < s_BoardSize; i++)
	{
		m_Cells[i].ResetAttackers();
	}
}