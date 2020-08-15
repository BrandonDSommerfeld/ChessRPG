#include "Piece.h"
#include <stdlib.h>
#include <iostream>


const int Piece::pieceHealth[6]{ 1,2,3,4,5,6 };

Piece::Piece()
	:
	m_moves{},
	m_maxHealth{ 0 },
	m_currentHealth{ 0 },
	m_isNoPiece{ true },
	m_isWhite{ false },
	m_status{Piece::Status::MAX_STATUSES},
	m_hasMoved{ true },
	m_usingSpecial{ false }
{
	m_moves[0] = Move::MAX_MOVES;
	m_moves[1] = Move::MAX_MOVES;
	m_moves[2] = Move::MAX_MOVES;
	m_moves[3] = Move::MAX_MOVES;
}
Piece::Piece(Type type, Move move1, Move move2, Move move3, Move move4, int health, bool isWhite)
	:
	m_moves{},
	m_maxHealth{ health },
	m_currentHealth{ health },
	m_isNoPiece{ false },
	m_isWhite{ isWhite },
	m_status{ Piece::Status::MAX_STATUSES },
	m_type{ type },
	m_hasMoved{ false },
	m_usingSpecial{ false }
{
	m_moves[0] = move1;
	m_moves[1] = move2;
	m_moves[2] = move3;
	m_moves[3] = move4;
}

bool Piece::neighbor(int crow, int ccol, int nrow, int ncol)
{
	return false;
}

Piece::AttackOutcome Piece::useMove(Piece& opponent, Piece::Move move)
{
	return Piece::AttackOutcome::MAX_OUTCOMES;
}
int Piece::getMaxHealth()
{
	return m_maxHealth;
}

int Piece::getCurrentHealth()
{
	return m_currentHealth;
}

Piece::Move Piece::getMove1()
{
	return m_moves[0];
}

Piece::Move Piece::getMove2()
{
	return m_moves[1];
}

Piece::Move Piece::getMove3()
{
	return m_moves[2];
}

Piece::Move Piece::getMove4()
{
	return m_moves[3];
}

Piece::Status Piece::getStatus()
{
	return m_status;
}

Piece::Type Piece::getType()
{
	return m_type;
}

bool Piece::isWhite()
{
	return m_isWhite;
}

bool Piece::hasMoved()
{
	return m_hasMoved;
}

bool Piece::isUsingSpecial()
{
	return m_usingSpecial;
}

bool Piece::isDead()
{
	return (m_currentHealth <= 0);
}


void Piece::moved()
{
	m_hasMoved = true;
}

void Piece::useSpecial()
{
	m_usingSpecial = true;
}

void Piece::allowMovement()
{
	m_usingSpecial = false;
}

void Piece::dealDamage(int amount)
{
	m_currentHealth -= amount;
	if (m_currentHealth > m_maxHealth)
	{
		m_currentHealth = m_maxHealth;
	}
}





bool operator== (const Piece& piece1, const Piece& piece2)
{
	return (piece1.m_isNoPiece == piece2.m_isNoPiece);
}

bool operator != (const Piece& piece1, const Piece& piece2)
{
	return (piece1.m_isNoPiece != piece2.m_isNoPiece);
}

std::string getDescription(Piece::Move move)
{
	switch (move)
	{
	case Piece::Move::Bash :
		return "Deal 2 damage";
	case Piece::Move::Slice:
		return "Deal 1 damage and apply bleeding";
	case Piece::Move::Extra:
		return "Empty";
	case Piece::Move::Move:
		return "";

	default :
		return "";
	}
	return "";
}

std::string printMove(Piece::Move move)
{
	switch (move)
	{
	case Piece::Move::Bash :
		return "Bash";
	case Piece::Move::Slice:
		return "Slice";
	case Piece::Move::Extra : 
		return "Extra";
	case Piece::Move::Move :
		return "Move";
	default :
		return "";
	}
	return "";
}

std::string printStatus(Piece::Status status)
{
	switch (status)
	{
	case Piece::Status::Bleeding :
		return "Bleeding";
	case Piece::Status::Poisoned :
		return "Poisoned";
	default :
		return "";
	}
}

int getRandomNumber(int min, int max)
{
	static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };  // static used for efficiency, so we only calculate this value once
	// evenly distribute the random number across our range
	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}