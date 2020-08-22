#include "Piece.h"
#include <stdlib.h>
#include <iostream>


const int Piece::pieceHealth[6]{ 10, 20, 20, 20, 40, 40};

Piece::Piece()
	:
	m_moves{},
	m_maxHealth{ 0 },
	m_currentHealth{ 0 },
	m_isNoPiece{ true },
	m_isWhite{ false },
	m_status{Piece::Status::MAX_STATUSES},
	m_hasMoved{ true },
	m_usingSpecial{ false },
	m_statusTurns{ 0 },
	m_dodgeChance{ 0 },
	m_critChance{ 0 },
	m_reducingDamage{ false },
	m_addingDamage{ false },
	m_jerichoCount{ 0 }
{
	m_moves[0] = Move::MAX_MOVES;
	m_moves[1] = Move::MAX_MOVES;
	m_moves[2] = Move::MAX_MOVES;
	m_moves[3] = Move::MAX_MOVES;
}
Piece::Piece(Type type, Move move1, Move move2, Move move3, Move move4, bool isWhite)
	:
	m_moves{},
	m_maxHealth{ Piece::pieceHealth[static_cast<int>(type)] },
	m_currentHealth{ Piece::pieceHealth[static_cast<int>(type)] },
	m_isNoPiece{ false },
	m_isWhite{ isWhite },
	m_status{ Piece::Status::MAX_STATUSES },
	m_type{ type },
	m_hasMoved{ false },
	m_usingSpecial{ false },
	m_statusTurns{ 0 },
	m_dodgeChance{ 10 },
	m_critChance{ 10 },
	m_reducingDamage{ false },
	m_addingDamage{ false },
	m_jerichoCount{ 0 }
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



void Piece::setStatus(Piece::Status status)
{
	m_status = status;
}

int Piece::getMaxHealth()
{
	return m_maxHealth;
}

int Piece::getCurrentHealth()
{
	return m_currentHealth;
}

Piece::Move Piece::getMove(int move)
{
	return m_moves[move-1];
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
	if (m_type == Piece::Type::Rook)
	{
		m_dodgeChance = 0;
	}
}

void Piece::allowMovement()
{
	m_usingSpecial = false;
	if (m_type == Piece::Type::Rook)
	{
		m_dodgeChance = 10;
	}
}

void Piece::dealDamage(int amount)
{
	if (m_usingSpecial && m_type == Piece::Type::Rook)
	{
		--amount;
	}
	if (m_reducingDamage)
	{
		--amount;
		m_reducingDamage = false;
	}
	if (m_status == Piece::Status::Cursed)
	{
		amount += 2;
	}
	if (amount < 0)
	{
		amount = 0;
	}
	m_currentHealth -= amount;
	if (m_currentHealth > m_maxHealth)
	{
		m_currentHealth = m_maxHealth;
	}
}

int Piece::getStatusTurns()
{
	return m_statusTurns;
}

void Piece::decrementStatusTurns()
{
	--m_statusTurns;
	if (m_statusTurns == 0)
	{
		m_status = Piece::Status::MAX_STATUSES;
	}
}

void Piece::setStatusTurns(int turns)
{
	m_statusTurns = turns;
}

void Piece::reset()
{
	if (m_usingSpecial && m_type == Piece::Type::Rook)
	{
		m_dodgeChance = 0;
	}
	else
	{
		m_dodgeChance = 10;
	}
	m_reducingDamage = false;
	m_addingDamage = false;
	m_critChance = 10;
	m_jerichoCount = 0;
}

bool operator== (const Piece& piece1, const Piece& piece2)
{
	return (piece1.m_isNoPiece == piece2.m_isNoPiece);
}

bool operator != (const Piece& piece1, const Piece& piece2)
{
	return (piece1.m_isNoPiece != piece2.m_isNoPiece);
}

Piece::AttackOutcome Piece::useMove(Piece& opponent, Piece::Move move)
{
	bool hit{ true };
	if (getRandomNumber(0, 99) < opponent.m_dodgeChance)
	{
		hit = false;
	}
	bool crit{ false };
	if (getRandomNumber(0, 99) < m_critChance)
	{
		crit = true;
	}
	int extra{ 0 };
	if (m_addingDamage)
	{
		m_addingDamage = false;
		extra = 3;
	}

	switch (move)
	{
	case Piece::Move::Bash:
	{
		if (hit)
		{
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(3, 4));
			}
			else
			{
				opponent.dealDamage(getRandomNumber(1, 2));
			}
		}
		break;
	}
	case Piece::Move::Slice:
	{
		if (hit && opponent.m_type != Piece::Type::Rook)
		{
			opponent.setStatus(Piece::Status::Bleeding);
			if (crit)
			{
				opponent.setStatusTurns(getRandomNumber(2, 3));
			}
			else
			{
				opponent.setStatusTurns(getRandomNumber(1, 2));
			}
		}
		break;
	}
	case Piece::Move::Distract :
	{
		if (hit)
		{
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(1,2));
			}
			else
			{
				opponent.dealDamage(getRandomNumber(0, 1));
			}
			m_dodgeChance += 5;
		}
		break;
	}
	case Piece::Move::FindWeakness :
	{
		if (hit)
		{
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(1, 2));
			}
			else
			{
				opponent.dealDamage(getRandomNumber(0, 1));
			}
			m_critChance += 5;
		}
		break;
	}
	case Piece::Move::PureSkill :
	{
		if (hit)
		{
			if (crit)
			{
				opponent.dealDamage(7);
			}
			else
			{
				opponent.dealDamage(0);
			}
		}
		break;
	}
	case Piece::Move::Cripple :
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_status == Piece::Status::Bleeding)
				{
					opponent.dealDamage(getRandomNumber(5, 6));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(1, 2));
				}
			}
			else
			{
				if (opponent.m_status == Piece::Status::Bleeding)
				{
					opponent.dealDamage(getRandomNumber(3, 4));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(0, 1));
				}
			}
		}
		break;
	}
	case Piece::Move::Demolition :
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_type == Piece::Type::Rook)
				{
					opponent.dealDamage(getRandomNumber(6, 7));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(1, 2));
				}
			}
			else
			{
				if (opponent.m_type == Piece::Type::Rook)
				{
					opponent.dealDamage(getRandomNumber(3, 4));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(0, 1));
				}
			}
		}
		break;
	}
	case Piece::Move::Backstab :
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_type == Piece::Type::Pawn)
				{
					opponent.dealDamage(getRandomNumber(4, 5));
				}
			}
			else
			{
				if (opponent.m_type == Piece::Type::Pawn)
				{
					opponent.dealDamage(getRandomNumber(2, 3));
				}
			}
		}
		break;
	}
	case Piece::Move::LastResort :
	{
		if (hit)
		{
			if (crit)
			{
				if (m_currentHealth == 1)
				{
					opponent.dealDamage(getRandomNumber(6, 8));
				}
			}
			else
			{
				if (m_currentHealth == 1)
				{
					opponent.dealDamage(getRandomNumber(3, 4));
				}
			}
		}
		break;
	}
	case Piece::Move::RecklessSwing :
	{
		dealDamage(1);
		if (hit)
		{
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(4, 6));
			}
			else
			{
				opponent.dealDamage(getRandomNumber(2, 3));
			}
		}
		break;
	}
	case Piece::Move::PrepareDefenses :
	{
		m_reducingDamage = true;
		if (hit)
		{
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(2, 3));
			}
			else
			{
				opponent.dealDamage(getRandomNumber(1, 2));
			}
		}
		break;
	}
	case Piece::Move::BoilingOil :
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_type != Piece::Type::Rook)
				{
					opponent.dealDamage(getRandomNumber(2, 3));
					opponent.setStatus(Piece::Status::Burning);
					opponent.setStatusTurns(getRandomNumber(2, 3));
				}
			}
			else
			{
				if (opponent.m_type != Piece::Type::Rook)
				{
					opponent.dealDamage(getRandomNumber(1, 2));
					opponent.setStatus(Piece::Status::Burning);
					opponent.setStatusTurns(getRandomNumber(1, 2));
				}
			}
		}
		break;
	}
	case Piece::Move::ArrowSalvo :
	{
		if (hit)
		{
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(4, 5));
			}
			else
			{
				opponent.dealDamage(getRandomNumber(2, 3));
			}
		}
		break;
	}
	case Piece::Move::PristineDefense :
	{
		
		if (hit)
		{
			opponent.m_critChance -= 5;
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(2, 4));
			}
			else
			{
				opponent.dealDamage(getRandomNumber(1, 2));
			}
		}
		break;
	}
	case Piece::Move::Caltrops :
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_type == Piece::Type::Knight)
				{
					opponent.dealDamage(getRandomNumber(5, 7));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(1, 2));
				}
			}
			else
			{
				if (opponent.m_type == Piece::Type::Knight)
				{
					opponent.dealDamage(getRandomNumber(3, 5));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(0, 1));
				}
			}
		}
		break;
	}
	case Piece::Move::Pikemen :
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_type != Piece::Type::Rook && opponent.m_type != Piece::Type::Bishop)
				{
					opponent.dealDamage(getRandomNumber(5, 7));
				}
			}
			else
			{
				if (opponent.m_type != Piece::Type::Rook && opponent.m_type != Piece::Type::Bishop)
				{
					opponent.dealDamage(getRandomNumber(3, 5));
				}
			}
		}
		break;
	}
	case Piece::Move::PerfectlyConstructed :
	{
		if (hit)
		{
			if (crit)
			{
				if (m_currentHealth == m_maxHealth)
				{
					opponent.dealDamage(getRandomNumber(7, 9));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(3, 4));
				}
			}
			else
			{
				if (m_currentHealth == m_maxHealth)
				{
					opponent.dealDamage(getRandomNumber(4, 6));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(1, 2));
				}
			}
		}
		break;
	}
	case Piece::Move::NoxiousFumes :
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_status == Piece::Status::Burning)
				{
					opponent.dealDamage(getRandomNumber(6, 8));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(1, 2));
				}
			}
			else
			{
				if (opponent.m_status == Piece::Status::Burning)
				{
					opponent.dealDamage(getRandomNumber(4, 5));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(0, 1));
				}
			}
		}
		break;
	}
	case Piece::Move::ThrowRock :
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_type == Piece::Type::Pawn || opponent.m_type == Piece::Type::Bishop || opponent.m_type == Piece::Type::King)
				{
					opponent.dealDamage(getRandomNumber(4, 6));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(1, 2));
				}
			}
			else
			{
				if (opponent.m_type == Piece::Type::Pawn || opponent.m_type == Piece::Type::Bishop || opponent.m_type == Piece::Type::King)
				{
					opponent.dealDamage(getRandomNumber(2, 4));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(0, 1));
				}
			}
		}
		break;
	}
	case Piece::Move::FalseSurrender :
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_type == Piece::Type::Queen || opponent.m_type == Piece::Type::King)
				{
					opponent.dealDamage(getRandomNumber(5, 9));
				}
			}
			else
			{
				if (opponent.m_type == Piece::Type::Queen || opponent.m_type == Piece::Type::King)
				{
					opponent.dealDamage(getRandomNumber(3, 6));
				}
			}
		}
		break;
	}
	case Piece::Move::Charge :
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_type != Piece::Type::Rook)
				{
					opponent.dealDamage(getRandomNumber(5, 6) + extra);
				}
			}
			else
			{
				if (opponent.m_type != Piece::Type::Rook)
				{
					opponent.dealDamage(getRandomNumber(3, 4) + extra);
				}
			}
		}
		break;
	}
	case Piece::Move::Duel :
	{
		if (hit)
		{
			opponent.m_dodgeChance -= 5;
			m_critChance += 5;
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(2, 4) + extra);
			}
			else
			{
				opponent.dealDamage(getRandomNumber(1, 2) + extra);
			}
		}
		break;
	}
	case Piece::Move::Infiltrate :
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_type == Piece::Type::Rook)
				{
					opponent.dealDamage(getRandomNumber(6, 8) + extra);
				}
				else
				{
					opponent.dealDamage(getRandomNumber(2, 4) + extra);
				}
			}
			else
			{
				if (opponent.m_type == Piece::Type::Rook)
				{
					opponent.dealDamage(getRandomNumber(4, 5) + extra);
				}
				else
				{
					opponent.dealDamage(getRandomNumber(1, 2) + extra);
				}
			}
		}
		break;
	}
	case Piece::Move::SharpenSword :
	{
		m_addingDamage = true;
		return Piece::AttackOutcome::Success;
	}
	case Piece::Move::Slash :
	{
		if (hit)
		{
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(4, 5) + extra);
			}
			else
			{
				opponent.dealDamage(getRandomNumber(2, 3) + extra);
			}
		}
		break;
	}
	case Piece::Move::Amputate :
	{
		if (hit && opponent.m_type != Piece::Type::Rook)
		{
			opponent.setStatus(Piece::Status::Bleeding);
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(1, 2) + extra);
				opponent.setStatusTurns(getRandomNumber(3, 4));
			}
			else
			{
				opponent.dealDamage(getRandomNumber(0, 1) + extra);
				opponent.setStatusTurns(getRandomNumber(2, 3));
			}
		}
		break;
	}
	case Piece::Move::AttackWeakness :
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_status == Piece::Status::Bleeding)
				{
					opponent.dealDamage(getRandomNumber(6, 7) + extra);
				}
				else
				{
					opponent.dealDamage(getRandomNumber(1, 3) + extra);
				}
			}
			else
			{
				if (opponent.m_status == Piece::Status::Bleeding)
				{
					opponent.dealDamage(getRandomNumber(4, 5) + extra);
				}
				else
				{
					opponent.dealDamage(getRandomNumber(0, 1) + extra);
				}
			}
		}
		break;
	}
	case Piece::Move::Horsemanship :
	{
		m_dodgeChance += 10;
		if (hit)
		{
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(3, 4) + extra);
			}
			else
			{
				opponent.dealDamage(getRandomNumber(1, 2) + extra);
			}
		}
		break;
	}
	case Piece::Move::WildSwing :
	{
		if (hit)
		{
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(0, 9) + extra);
			}
			else
			{
				opponent.dealDamage(getRandomNumber(0, 5) + extra);
			}
		}
		break;
	}
	case Piece::Move::StudyOpponent :
	{
		m_critChance += 15;
		return Piece::AttackOutcome::Success;
	}
	case Piece::Move::Heal :
	{
		if (crit)
		{
			dealDamage(-getRandomNumber(4, 5));
			return Piece::AttackOutcome::Super_Effective;
		}
		else
		{
			dealDamage(-getRandomNumber(2, 3));
			return Piece::AttackOutcome::Success;
		}
	}
	case Piece::Move::Purge :
	{
		m_status = Piece::Status::MAX_STATUSES;
		m_statusTurns = 0;
		if (hit)
		{
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(2, 4));
			}
			else
			{
				opponent.dealDamage(getRandomNumber(1, 2));
			}
		}
		break;
	}
	case Piece::Move::Jericho :
	{
		if (opponent.m_type == Piece::Type::Rook)
		{
			++m_jerichoCount;
			if (m_jerichoCount == 3)
			{
				opponent.dealDamage(Piece::pieceHealth[static_cast<int>(Piece::Type::Rook)] + 5);
			}
		}
		return Piece::AttackOutcome::Success;
	}
	case Piece::Move::DarkCurse :
	{
		if (hit)
		{
			opponent.setStatus(Piece::Status::Cursed);
			if (crit)
			{
				opponent.setStatusTurns(getRandomNumber(3, 5));
			}
			else
			{
				
				opponent.setStatusTurns(getRandomNumber(2, 4));
			}
		}
		break;
	}
	case Piece::Move::ProfaneRitual :
	{
		if (hit)
		{
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(3, 4));
				dealDamage(getRandomNumber(-4, -3));
			}
			else
			{
				opponent.dealDamage(getRandomNumber(1, 2));
				dealDamage(getRandomNumber(-2, -1));
			}
		}
		break;
	}
	case Piece::Move::PrayToRNGesus :
	{
		if (hit)
		{
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(-20, 20));
			}
			else
			{
				opponent.dealDamage(getRandomNumber(-10, 10));
			}
		}
		break;
	}
	case Piece::Move::Smite :
	{
		if (hit)
		{
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(4, 5));
			}
			else
			{
				opponent.dealDamage(getRandomNumber(2, 3));
			}
		}
		break;
	}
	case Piece::Move::Excommunicate :
	{
		if (hit && (opponent.m_type == Piece::Type::King || opponent.m_type == Piece::Type::Queen))
		{
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(7, 8));
			}
			else
			{
				opponent.dealDamage(getRandomNumber(4, 5));
			}
		}
		break;
	}
	case Piece::Move::HolyLight :
	{
		m_reducingDamage = true;
		if (crit)
		{
			dealDamage(getRandomNumber(-6, -1));
			return Piece::AttackOutcome::Super_Effective;
		}
		else
		{
			dealDamage(getRandomNumber(-5, 0));
			return Piece::AttackOutcome::Success;
		}
	}
	case Piece::Move::BlindingLight :
	{
		if (hit)
		{
			if (crit)
			{
				m_dodgeChance += 10;
			}
			else
			{
				m_dodgeChance += 5;
			}
			opponent.m_critChance = 0;
			
		}
		break;
	}
	case Piece::Move::Guards:
	{
		if (hit)
		{
			if (crit)
			{
				opponent.dealDamage(getRandomNumber(7, 8));
			}
			else
			{
				opponent.dealDamage(getRandomNumber(4, 5));
			}
		}
		break;
	}
	case Piece::Move::PawnGuards :
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_type == Piece::Type::Pawn)
				{
					opponent.dealDamage(getRandomNumber(8, 9));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(3, 5));
				}
			}
			else
			{
				if (opponent.m_type == Piece::Type::Pawn)
				{
					opponent.dealDamage(getRandomNumber(5, 6));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(2, 3));
				}
			}
		}
		break;
	}
	case Piece::Move::RookGuards:
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_type == Piece::Type::Rook)
				{
					opponent.dealDamage(getRandomNumber(8, 9));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(3, 5));
				}
			}
			else
			{
				if (opponent.m_type == Piece::Type::Rook)
				{
					opponent.dealDamage(getRandomNumber(5, 6));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(2, 3));
				}
			}
		}
		break;
	}
	case Piece::Move::KnightGuards:
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_type == Piece::Type::Knight)
				{
					opponent.dealDamage(getRandomNumber(8, 9));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(3, 5));
				}
			}
			else
			{
				if (opponent.m_type == Piece::Type::Knight)
				{
					opponent.dealDamage(getRandomNumber(5, 6));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(2, 3));
				}
			}
		}
		break;
	}
	case Piece::Move::BishopGuards:
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_type == Piece::Type::Bishop)
				{
					opponent.dealDamage(getRandomNumber(8, 9));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(3, 5));
				}
			}
			else
			{
				if (opponent.m_type == Piece::Type::Bishop)
				{
					opponent.dealDamage(getRandomNumber(5, 6));
				}
				else
				{
					opponent.dealDamage(getRandomNumber(2, 3));
				}
			}
		}
		break;
	}
	case Piece::Move::CutthroatPolitics:
	{
		if (hit)
		{
			if (crit)
			{
				if (opponent.m_type == Piece::Type::Queen || opponent.m_type == Piece::Type::King)
				{
					opponent.dealDamage(getRandomNumber(10, 12));
				}
			}
			else
			{
				if (opponent.m_type == Piece::Type::Queen || opponent.m_type == Piece::Type::King)
				{
					opponent.dealDamage(getRandomNumber(6, 8));
				}
			}
		}
		break;
	}

	case Piece::Move::ObliterateRook :
	{
		dealDamage(Piece::pieceHealth[static_cast<int>(Piece::Type::King)] / 2);
		if (opponent.m_type == Piece::Type::Rook && hit)
		{
			opponent.dealDamage(Piece::pieceHealth[static_cast<int>(Piece::Type::Rook)] + 5);
		}
		break;
	}
	case Piece::Move::ObliterateKnight:
	{
		dealDamage(Piece::pieceHealth[static_cast<int>(Piece::Type::King)] / 2);
		if (opponent.m_type == Piece::Type::Knight && hit)
		{
			opponent.dealDamage(Piece::pieceHealth[static_cast<int>(Piece::Type::Knight)]);
		}
		break;
	}
	case Piece::Move::ObliterateBishop:
	{
		dealDamage(Piece::pieceHealth[static_cast<int>(Piece::Type::King)] / 2);
		if (opponent.m_type == Piece::Type::Bishop && hit)
		{
			opponent.dealDamage(Piece::pieceHealth[static_cast<int>(Piece::Type::Bishop)]);
		}
		break;
	}
	case Piece::Move::ObliterateQueen:
	{
		dealDamage(Piece::pieceHealth[static_cast<int>(Piece::Type::King)] / 2);
		if (opponent.m_type == Piece::Type::Queen && hit)
		{
			opponent.dealDamage(Piece::pieceHealth[static_cast<int>(Piece::Type::Queen)]);
		}
		break;
	}
	case Piece::Move::ObliteratePawn:
	{
		dealDamage(Piece::pieceHealth[static_cast<int>(Piece::Type::King)] / 2);
		if (opponent.m_type == Piece::Type::Pawn && hit)
		{
			opponent.dealDamage(Piece::pieceHealth[static_cast<int>(Piece::Type::Pawn)]);
		}
		break;
	}
	case Piece::Move::ObliterateKing:
	{
		dealDamage(Piece::pieceHealth[static_cast<int>(Piece::Type::King)] / 2);
		if (opponent.m_type == Piece::Type::King && hit)
		{
			opponent.dealDamage(Piece::pieceHealth[static_cast<int>(Piece::Type::King)]);
		}
		break;
	}
	}

	if (!hit)
	{
		return Piece::AttackOutcome::Miss;
	}
	if (crit)
	{
		return Piece::AttackOutcome::Super_Effective;
	}
	return Piece::AttackOutcome::Success;
}

std::string getDescription(Piece::Move move)
{
	switch (move)
	{
	case Piece::Move::Bash:
		return "Deal 1-2 damage";
	case Piece::Move::Slice:
		return "Apply bleeding for 1-2 turns if the enemy is not a rook";
	case Piece::Move::Distract:
		return "Deal 0-1 damage. Raise dodge chance by 5%";
	case Piece::Move::FindWeakness:
		return "Deal 0-1 damage. Raise crit chance by 5%";
	case Piece::Move::PureSkill :
		return "Deal 0 damage. Deal 7 instead if this crits";
	case Piece::Move::Cripple :
		return "Deal 0-1 damage. If the enemy is bleeding, deal 3-4 instead";
	case Piece::Move::Demolition :
		return "Deal 0-1 damage. If the enemy is a rook, deal 3-4 instead";
	case Piece::Move::Backstab :
		return "Deal 0 damage. If the enemy is a pawn, deal 2-3 instead";
	case Piece::Move::LastResort :
		return "If you are at 1 health, deal 3-4 damage";
	case Piece::Move::RecklessSwing :
		return "Take 1 damage. Deal 2-3 damage";


	case Piece::Move::PrepareDefenses :
		return "Deal 1-2 damage. Take 1 less damage next time you are attacked";
	case Piece::Move::BoilingOil :
		return "If the enemy is not a rook, deal 1-2 damage and inflict burning for 1-2 turns";
	case Piece::Move::ArrowSalvo:
		return "Deal 2-3 damage";
	case Piece::Move::PristineDefense:
		return "Deal 1-2 damage and lower the enemy crit chance";
	case Piece::Move::Caltrops :
		return "Deal 0-1 damage. If the enemy is a knight, deal 3-5 instead";
	case Piece::Move::Pikemen :
		return "Deal 3-5 damage if the enemy is not a rook or bishop";
	case Piece::Move::PerfectlyConstructed :
		return "If you are at full health, deal 4-6 damage. Otherwise, deal 1-2";
	case Piece::Move::NoxiousFumes :
		return "Deal 0-1 damage. If the opponent is burning, deal 4-5 instead";
	case Piece::Move::ThrowRock :
		return "Deal 0-1 damage. If the enemy is a pawn, bishop, or king, deal 2-4 instead";
	case Piece::Move::FalseSurrender :
		return "If the enemy is a king or queen, deal 3-6 damage";

	case Piece::Move::Charge:
		return "If the enemy is not a rook, deal 3-4 damage";
	case Piece::Move::Duel:
		return "Deal 1-2 damage, lower enemy dodge chance, raise own crit chance";
	case Piece::Move::Infiltrate:
		return "Deal 1-2 damage. If the enemy is a rook, deal 4-5 instead";
	case Piece::Move::SharpenSword:
		return "Your next attack does an extra 3 damage";
	case Piece::Move::Slash :
		return "Deal 2-3 damage";
	case Piece::Move::Amputate :
		return "Deal 0-1 damage, apply bleeding for 2-3 turns";
	case Piece::Move::AttackWeakness :
		return "Deal 0-1 damage. If the enemy is bleeding, deal 4-5 instead";
	case Piece::Move::Horsemanship :
		return "Deal 1-2 damage. Greatly raise dodge chance";
	case Piece::Move::WildSwing :
		return "Deal 0-5 damage";
	case Piece::Move::StudyOpponent :
		return "Drastically raise crit chance";

	case Piece::Move::Heal:
		return "Restore 2-3 health to self";
	case Piece::Move::Purge:
		return "Deal 1-2 damage and remove status effects from self";
	case Piece::Move::Jericho:
		return "After using it 3 times, destroy an enemy rook";
	case Piece::Move::DarkCurse:
		return "Curse the enemy for 2-4 turns (Cursed enemies take 2 extra damage from moves)";
	case Piece::Move::ProfaneRitual :
		return "Deal 1-2 damage, heal 1-2 health";
	case Piece::Move::PrayToRNGesus :
		return "Heal up to 10 to the opponent, or deal up to 10 damage";
	case Piece::Move::Smite :
		return "Deal 2-3 damage";
	case Piece::Move::Excommunicate :
		return "If the enemy is a king or queen, deal 4-5 damage";
	case Piece::Move::HolyLight :
		return "Heal 0-5 health. Take 1 less damage from the next attack";
	case Piece::Move::BlindingLight :
		return "Lower opponent crit chance to 0. Raise dodge chance";

	case Piece::Move::Guards :
		return "Deal 4-5 damage";
	case Piece::Move::PawnGuards:
		return "Deal 2-3 damage. If the enemy is a pawn, deal 5-6 instead";
	case Piece::Move::RookGuards:
		return "Deal 2-3 damage. If the enemy is a rook, deal 5-6 instead";
	case Piece::Move::KnightGuards:
		return "Deal 2-3 damage. If the enemy is a knight, deal 5-6 instead";
	case Piece::Move::BishopGuards:
		return "Deal 2-3 damage. If the enemy is a bishop, deal 5-6 instead";
	case Piece::Move::CutthroatPolitics :
		return "If the enemy is a king or queen, deal 6-8 damage";

	case Piece::Move::ObliterateRook:
		return "Lose half of your max health. Destroy the enemy if it is a rook";
	case Piece::Move::ObliterateKnight:
		return "Lose half of your max health. Destroy the enemy if it is a knight";
	case Piece::Move::ObliterateBishop:
		return "Lose half of your max health. Destroy the enemy if it is a bishop";
	case Piece::Move::ObliterateQueen:
		return "Lose half of your max health. Destroy the enemy if it is a queen";
	case Piece::Move::ObliteratePawn:
		return "Lose half of your max health. Destroy the enemy if it is a pawn";
	case Piece::Move::ObliterateKing:
		return "Lose half of your max health. Destroy the enemy if it is a king\n(You win even if you die using this)";
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
	case Piece::Move::Distract : 
		return "Distract";
	case Piece::Move::FindWeakness :
		return "Find Weakness";
	case Piece::Move::PureSkill :
		return "Pure Skill";
	case Piece::Move::Cripple :
		return "Cripple";
	case Piece::Move::Demolition :
		return "Demolition";
	case Piece::Move::Backstab :
		return "Backstab";
	case Piece::Move::LastResort :
		return "Last Resort";
	case Piece::Move::RecklessSwing :
		return "Reckless Swing";
	
	case Piece::Move::PrepareDefenses:
		return "Prepare Defenses";
	case Piece::Move::BoilingOil:
		return "Boiling Oil";
	case Piece::Move::ArrowSalvo:
		return "Arrow Salvo";
	case Piece::Move::PristineDefense:
		return "Pristine Defense";
	case Piece::Move::Caltrops :
		return "Caltrops";
	case Piece::Move::Pikemen :
		return "Pikemen";
	case Piece::Move::PerfectlyConstructed :
		return "Perfectly Constructed";
	case Piece::Move::NoxiousFumes :
		return "Noxious Fumes";
	case Piece::Move::ThrowRock :
		return "Throw Rock";
	case Piece::Move::FalseSurrender :
		return "False Surrender";

	case Piece::Move::Charge:
		return "Charge";
	case Piece::Move::Duel:
		return "Duel";
	case Piece::Move::Infiltrate:
		return "Infiltrate";
	case Piece::Move::SharpenSword:
		return "Sharpen Sword";
	case Piece::Move::Slash :
		return "Slash";
	case Piece::Move::Amputate :
		return "Amputate";
	case Piece::Move::AttackWeakness :
		return "Attack Weakness";
	case Piece::Move::Horsemanship :
		return "Horsemanship";
	case Piece::Move::WildSwing :
		return "Wild Swing";
	case Piece::Move::StudyOpponent :
		return "Study Opponent";

	case Piece::Move::Heal:
		return "Heal";
	case Piece::Move::Purge:
		return "Purge";
	case Piece::Move::Jericho:
		return "Jericho";
	case Piece::Move::DarkCurse:
		return "Dark Curse";
	case Piece::Move::ProfaneRitual :
		return "Profane Ritual";
	case Piece::Move::PrayToRNGesus :
		return "Pray To RNGesus";
	case Piece::Move::Smite :
		return "Smite";
	case Piece::Move::Excommunicate :
		return "Excommunicate";
	case Piece::Move::HolyLight :
		return "Holy Light";
	case Piece::Move::BlindingLight :
		return "Blinding Light";

	case Piece::Move::Guards :
		return "Guards";
	case Piece::Move::PawnGuards:
		return "Pawn Guards";
	case Piece::Move::RookGuards:
		return "Rook Guards";
	case Piece::Move::KnightGuards:
		return "Knight Guards";
	case Piece::Move::BishopGuards:
		return "Bishop Guards";
	case Piece::Move::CutthroatPolitics :
		return "Cutthroat Politics";

	case Piece::Move::ObliterateRook:
		return "Obliterate Rook";
	case Piece::Move::ObliterateKnight:
		return "Obliterate Knight";
	case Piece::Move::ObliterateBishop:
		return "Obliterate Bishop";
	case Piece::Move::ObliterateQueen:
		return "Obliterate Queen";
	case Piece::Move::ObliteratePawn:
		return "Obliterate Pawn";
	case Piece::Move::ObliterateKing:
		return "Obliterate King";
	}
	return "";
}

std::string printStatus(Piece::Status status)
{
	switch (status)
	{
	case Piece::Status::Bleeding :
		return "Bleeding";
	case Piece::Status::Cursed :
		return "Cursed";
	case Piece::Status::Burning :
		return "Burning";
	case Piece::Status::MAX_STATUSES :
		return "";
	}
	return "";
}

std::string Piece::getName()
{
	std::string name{};
	if (isWhite())
	{
		name = "White ";
	}
	else
	{
		name = "Black ";
	}
	name += printType(getType());
	return name;
}

std::string printType(Piece::Type type)
{
	switch (type)
	{
	case Piece::Type::Pawn :
		return "Pawn";
	case Piece::Type::Rook :
		return "Rook";
	case Piece::Type::Knight:
		return "Knight";
	case Piece::Type::Bishop:
		return "Bishop";
	case Piece::Type::Queen:
		return "Queen";
	case Piece::Type::King:
		return "King";
	default :
		return "";
	}
}

int getRandomNumber(int min, int max)
{
	static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };
	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}