#include <cstring>
#include <iostream>

#include "Board.h"

Board* Board::mInstance = nullptr;
Piece*** Board::mBoard = nullptr;
Piece* Board::mFallingPiece = nullptr;

Board::~Board()
{
	if (mBoard != nullptr)
	{
		for (unsigned char column = 0; column < BOARD_HEIGTH; ++column)
		{
			for (unsigned char row = 0; row < BOARD_WIDTH; ++row)
			{
				if (mBoard[row] != nullptr)
				{
					delete mBoard[column][row];
				}
			}
			delete[] mBoard[column];
		}

		delete[] mBoard;
	}

	delete mInstance;
}

Board* Board::GetInstance()
{
	std::cerr << "GETINSTANCE: Called" << std::endl;
	if (mInstance == nullptr)
	{
		std::cerr << "GETINSTANCE: Instance not initialized." << std::endl;
		mInstance = new Board();
		std::cerr << "GETINSTANCE: Instance Initialized, initializing board" << std::endl;
		mBoard = new Piece**[BOARD_HEIGTH];
		for (unsigned char column = 0; column < BOARD_HEIGTH; ++column)
		{
			std::cerr << "GETINSTANCE: Initializing column " << static_cast<unsigned short>(column) << std::endl;
			mBoard[column] = new Piece*[BOARD_WIDTH];
			std::cerr << "GETINSTANCE: Column " << static_cast<unsigned short>(column) << " initialized, initializing each cell to nullptr" << std::endl;
			memset(mBoard[column], 0, sizeof(char) * BOARD_WIDTH);
			std::cerr << "GETINSTANCE: Initializing blocks to nullptr" << std::endl;
			for (unsigned char row = 0; row < BOARD_WIDTH; ++row)
			{
				std::cout << "[" << static_cast<unsigned short>(column) << ", " << static_cast<unsigned short>(row) << "] " << mBoard[column][row] << std::endl;
			}
		}
	}

	return mInstance;
}

bool Board::AddPiece(Piece*&& piece, unsigned char x, unsigned char y)
{
	if (piece == nullptr)
	{
		return false;
	}

	if (x >= 6 || y >= 16)
	{
		return false;
	}

	for (unsigned char column = 0; column < 5; ++column)
	{
		for (unsigned char row = 0; row < 5; ++row)
		{
			if (piece->GetBlock(row, column) != 0)
			{
				mBoard[column][y + row] = piece;
			}
		}
	}

	mFallingPiece = piece;

	piece = nullptr;
	return true;
}

bool Board::IsGameOver() const
{
	for (unsigned char row = 0; row < BOARD_WIDTH; ++row)
	{
		if (mBoard[0][row] != nullptr)
		{
			return true;
		}
	}

	return false;
}

void Board::DeleteLine(unsigned char line)
{
	for (unsigned char column = line - 1; column >= 0; --column)
	{
		for (unsigned char row = 0; row < BOARD_WIDTH; ++row)
		{
			if (column == line - 1)
			{
				delete mBoard[column][row];
			}

			mBoard[column][row] = (column != 0) ? mBoard[column - 1][row] : nullptr;
		}
	}
}

void Board::DeletePossibleLines()
{
	unsigned char blockCount;
	for (unsigned char column = BOARD_HEIGTH - 1; column >= 0; --column)
	{
		blockCount = 0;
		for (unsigned char row = 0; row < BOARD_WIDTH; ++row)
		{
			if (mBoard[column][row] != nullptr)
			{
				++blockCount;
			}
		}

		if (blockCount == BOARD_WIDTH)
		{
			DeleteLine(column);
			++column;
		}
	}
}

bool Board::IsFreeBlock(unsigned char x, unsigned char y) const
{
	return (mBoard[y][x] != nullptr);
}

// bool IsPossibleMovement()
// {
// 	// Collision with wall


// 	// Collision with bock
// }

bool Board::IsPossibleMovement(ePieceType pieceType, eRotationType rotationType, unsigned char x, unsigned char y)
{
	for (unsigned char column = 0; column < 5; ++column)
	{
		for (unsigned char row = 0; row < 5; ++row)
		{
			if (x + row < 0 || x + row > BOARD_WIDTH - 1 || y + column > BOARD_HEIGTH - 1)
			{
				if (mBoard[y + column][x + row] != nullptr)
				{
					return false;
				}
			}

			if (y + column >= 0)
			{
				if (mBoard[y + column][x + row] != nullptr && !IsFreeBlock(x + row, y + column))
				{
					return false;
				}
			}
		}
	}

	return true;
}
