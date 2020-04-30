#pragma once

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

// a
const int MAX_CHAR = 80;

struct LineType
{
	char Data[MAX_CHAR];
	struct LineType* Next;
	struct LineType* Previous;
};

class TextEditor
{
friend std::ostream& operator<<(std::ostream& os, const TextEditor& other);
public:
	TextEditor();
	TextEditor(const char* fileName);
	virtual ~TextEditor();

	void GoToTop();
	void GoToBottom();
	void PrintCurrentLine() const;

	void Insert(const char* data);
	bool Delete(const char* data);
	bool Search(const char* data) const;

	LineType* operator[](unsigned int index) const;
	unsigned int GetLength() const;
private:
	LineType* mFirstNode;
	LineType* mLastNode;
	LineType* mCurrentLine;
	unsigned int mSize;
};