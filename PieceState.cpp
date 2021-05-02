#include "DEBUG.h"
#include <iostream>

#include "PieceState.h"

PieceState::PieceState()
	: m_Piece(nullptr),
	m_IsDead(false)
{
}

void PieceState::Init(Piece* piece)
{
	m_Piece = piece;
	//m_Position = piece->GetPosition();
	m_IsDead = piece->IsDead();

	if (DEBUG)
		std::cout << typeid(this).name() << " has been created! " << std::endl;
}