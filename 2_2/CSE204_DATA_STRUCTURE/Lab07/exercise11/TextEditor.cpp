#include "TextEditor.h"

extern const int MAX_CHAR;

// b
TextEditor::TextEditor()
	: mFirstNode(nullptr)
	, mLastNode(nullptr)
	, mCurrentLine(mFirstNode)
	, mSize(0)
{
}

TextEditor::TextEditor(const char* fileName)
	: mFirstNode(nullptr)
	, mLastNode(nullptr)
	, mSize(0)
{
	LineType* curPtr;
	LineType* prevPtr = nullptr;
	std::ifstream fin;
	fin.open(fileName);

	bool bNotEOF = true;
	char character;
	std::string trash;
	while (bNotEOF)
	{
		curPtr = new LineType;
		++mSize;
		curPtr->Previous = prevPtr;
		if (prevPtr != nullptr)
		{
			prevPtr->Next = curPtr;
		}
		else
		{
			mFirstNode = curPtr;
		}

		for (size_t ch = 0; ch < MAX_CHAR; ++ch)
		{
			fin.get(character);

			if (!fin.fail())
			{
				if (character == '\0' || character == '\n')
				{
					break;
				}

				curPtr->Data[ch] = character;
				continue;
			}

			if (fin.eof())
			{
				bNotEOF = false;
				break;
			}

			fin.clear();
			fin >> trash;
		}

		prevPtr = curPtr;
	}

	curPtr->Next = nullptr;
	mLastNode = curPtr;

	mCurrentLine = mFirstNode;

	fin.close();
}

TextEditor::~TextEditor()
{
	LineType* tempPtr = mFirstNode;

	while (tempPtr != nullptr)
	{
		LineType* lineToDelete = tempPtr;
		delete lineToDelete;

		tempPtr = tempPtr->Next;
	}

	mFirstNode = nullptr;
	mLastNode = nullptr;
	mCurrentLine = nullptr;
}

void TextEditor::GoToTop()
{
	
	if (mSize == 0)
	{
		mCurrentLine = mLastNode;
		return;
	}

	/* c
	while (mCurrentLine->Previous != nullptr)
	{
		mCurrentLine = mCurrentLine->Previous;
	}
	*/

	// d
	mCurrentLine = mFirstNode;
}

void TextEditor::GoToBottom()
{
	if (mSize == 0)
	{
		mCurrentLine = mFirstNode;
		return;
	}

	/* c
	while (mCurrentLine->Next != nullptr)
	{
		mCurrentLine = mCurrentLine->Next;
	}
	*/

	// d
	mCurrentLine = mLastNode;
}

// e
void TextEditor::Insert(const char* line)
{
	// 빈 노드
	if (mSize == 0)
	{
		LineType* newNode = new LineType;
		size_t ch = 0;
		for (; ch < MAX_CHAR && line[ch] != '\0'; ++ch)
		{
			newNode->Data[ch] = line[ch];
		}
		newNode->Data[ch] = '\0';
		newNode->Next = nullptr;
		newNode->Previous = nullptr;

		mFirstNode = newNode;
		mLastNode = newNode;
		++mSize;
		return;
	}

	// 맨 앞
	if (mCurrentLine == mFirstNode)
	{
		LineType* newNode = new LineType;
		size_t ch = 0;
		for (; ch < MAX_CHAR && line[ch] != '\0'; ++ch)
		{
			newNode->Data[ch] = line[ch];
		}
		newNode->Data[ch] = '\0';
		newNode->Previous = mFirstNode;
		newNode->Next = mFirstNode->Next;
		mFirstNode->Next->Previous = newNode;
		mFirstNode->Next = newNode;

		if (mFirstNode == mLastNode)
		{
			mLastNode = newNode;
		}

		++mSize;
		return;
	}

	unsigned int count = 1;
	for (LineType* node = mFirstNode; node != nullptr && count <= mSize; node = node->Next, ++count)
	{
		// 맨 뒤
		if (count == mSize)
		{
			LineType* newNode = new LineType;
			size_t ch = 0;
			for (; ch < MAX_CHAR && line[ch] != '\0'; ++ch)
			{
				newNode->Data[ch] = line[ch];
			}
			newNode->Data[ch] = '\0';
			newNode->Previous = node;
			newNode->Next = nullptr;
			node->Next = newNode;
			++mSize;
			return;
		}

		if (node == mCurrentLine)
		{
			// 중간
			LineType* newNode = new LineType;
			size_t ch = 0;
			for (; ch < MAX_CHAR && line[ch] != '\0'; ++ch)
			{
				newNode->Data[ch] = line[ch];
			}
			newNode->Data[ch] = '\0';
			newNode->Previous = node;
			newNode->Next = node->Next;
			node->Next->Previous = newNode;
			node->Next = newNode;
			++mSize;
			return;
		}
	}
}

bool TextEditor::Delete(const char* data)
{
	// 비어있을 때
	if (mSize == 0)
	{
		return false;
	}

	LineType* cur;
	LineType* prev;
	for (cur = mFirstNode, prev = nullptr; cur != nullptr && strcmp(cur->Data, data) != 0; prev = cur, cur = cur->Next)
	{
	}
	
	if (cur == nullptr)
	{
		return false;
	}
	if (prev == nullptr)
	{
		mFirstNode = mFirstNode->Next;
	}
	else
	{
		prev->Next = cur->Next;

		if (cur->Next != nullptr)
		{
			cur->Next->Previous = prev;
			cur->Next = nullptr;
		}
		
		cur->Previous = nullptr;
	}
	cur = nullptr;
	--mSize;

	return true;
}

bool TextEditor::Search(const char* data) const
{
	for (LineType* node = mFirstNode; node != nullptr; node = node->Next)
	{
		if ( strcmp(node->Data, data) )
		{
			return true;
		}
	}

	return false;
}

LineType* TextEditor::operator[](unsigned int index) const
{
	if (index >= mSize)
	{
		return nullptr;
	}

	unsigned int count = 0;
	for (LineType* node = mFirstNode; node != nullptr && count < mSize; node = node->Next, ++count)
	{
		if (count == index)
		{
			return node;
		}
	}

	return nullptr;
}

unsigned int TextEditor::GetLength() const
{
	return mSize;
}

void TextEditor::PrintCurrentLine() const
{
	if (mCurrentLine != nullptr)
	{
		std::cout << mCurrentLine->Data << std::endl;
	}
}

std::ostream& operator<<(std::ostream& os, const TextEditor& other)
{
	LineType* tempPtr = other.mFirstNode;
	size_t index = 0;
	while (tempPtr != nullptr)
	{
		os << "Line[" << index << "] = " << tempPtr->Data << std::endl;
		tempPtr = tempPtr->Next;
		++index;
	}

	return os;
}