#pragma once

#include <memory>

#include "Board.h"
#include "Piece.h"

class Game
{
public:
private:
	unsigned short mScreenHeight;
	unsigned short mNextPosX;
	unsigned short mNextPosY;
	ePieceType mNextPieceType;
	eRotationType mNextRotationType;

	std::unique_ptr<Board> mBoard;
};