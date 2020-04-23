#pragma once

#include <iostream>

template<class ItemType>
struct NodeType
{
	ItemType mInfo;
	NodeType* mNext;
};

namespace exercise03
{
	template <class ItemType>
	class SortedType
	{
	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const SortedType<T>& other);
	public:
		SortedType();
		~SortedType();

		bool IsFull() const;
		unsigned int  LengthIs() const;
		void MakeEmpty();
		void RetrieveItem(ItemType& item, bool& found);
		void InsertItem(ItemType item); 
		void DeleteItem(ItemType item);
		void ResetList();
		void GetNextItem(ItemType&);
		void MergeLists(const SortedType& other, SortedType& result);

	private:
		NodeType<ItemType>* mListData;
		unsigned int mLength;
		NodeType<ItemType>* mCurrentPos;
	};



	template <class ItemType>
	SortedType<ItemType>::SortedType()
		: mListData(nullptr), mLength(0), mCurrentPos(nullptr)
	{
	}

	template<class ItemType>
	bool SortedType<ItemType>::IsFull() const
	{
		NodeType<ItemType>* location;

		try
		{
			location = new NodeType<ItemType>;
			delete location;
			return false;
		}
		catch(std::bad_alloc exception)
		{
			return true;
		}
	}

	template <class ItemType>
	unsigned int SortedType<ItemType>::LengthIs() const
	{
		return mLength;
	}

	template <class ItemType>
	void SortedType<ItemType>::MakeEmpty()
	{
		NodeType<ItemType>* tempPtr;

		while (mListData != nullptr)
		{
			tempPtr = mListData;
			mListData = mListData->mNext;
			delete tempPtr;
		}

		mLength = 0;
	}

	template <class ItemType>
	void SortedType<ItemType>::RetrieveItem(ItemType& item, bool& found)
	{
		bool moreToSearch;
		NodeType<ItemType>* location;

		location = mListData;
		found = false;
		moreToSearch = (location != nullptr);

		while (moreToSearch && !found)
		{
			if (location->mInfo < item)
			{
				location = location->mNext;
				moreToSearch = (location != nullptr);
			}
			else if (item == location->mInfo)
			{
				found = true;
				item = location->mInfo;
			}
			else
			{
				moreToSearch = false;
			}
		}
	}

	template <class ItemType>
	void SortedType<ItemType>::InsertItem(ItemType item)
	{
		NodeType<ItemType>* newNode;  // pointer to node being inserted
		NodeType<ItemType>* predLoc;  // trailing pointer
		NodeType<ItemType>* location; // traveling pointer
		bool moreToSearch;

		location = mListData;
		predLoc = nullptr;
		moreToSearch = (location != nullptr);

		// Find insertion point.
		while (moreToSearch)
		{
			if (location->mInfo < item)
			{
				predLoc = location;
				location = location->mNext;
				moreToSearch = (location != nullptr);
			}
			else
			{
				moreToSearch = false;
			}
		}

		// Prepare node for insertion
		newNode = new NodeType<ItemType>;
		newNode->mInfo = item;
		// Insert node into list.
		if (predLoc == nullptr)         // Insert as first
		{
			newNode->mNext = mListData;
			mListData = newNode;
		}
		else
		{
			newNode->mNext = location;
			predLoc->mNext = newNode;
		}
		++mLength;
	}

	template <class ItemType>
	void SortedType<ItemType>::DeleteItem(ItemType item)
	{
		NodeType<ItemType>* location = mListData;
		NodeType<ItemType>* tempLocation;

		// Locate node to be deleted.
		if (item == mListData->mInfo)
		{
			tempLocation = location;
			mListData = mListData->mNext;		// Delete first node.
		}
		else
		{
			while (!(item==(location->mNext)->mInfo))
			location = location->mNext;

			// Delete node at location->mNext
			tempLocation = location->mNext;
			location->mNext = (location->mNext)->mNext;
		}
		delete tempLocation;
		--mLength;
	}

	template <class ItemType>
	void SortedType<ItemType>::ResetList()
	{
		mCurrentPos = nullptr;
	}
	
	template <class ItemType>
	void SortedType<ItemType>::GetNextItem(ItemType& item)
	{
		if (mListData == nullptr)
		{
			return;
		}

		if (mCurrentPos == nullptr)
		{
			mCurrentPos = mListData;
		}

		item = mCurrentPos->mInfo; 
		mCurrentPos = mCurrentPos->mNext;
	} 

	template <class ItemType>
	SortedType<ItemType>::~SortedType()
	{
		NodeType<ItemType>* tempPtr;

		while (mListData != nullptr)
		{
			tempPtr = mListData;
			mListData = mListData->mNext;
			delete tempPtr;
		}
	}

	template <class ItemType>
	void SortedType<ItemType>::MergeLists(const SortedType<ItemType>& other, SortedType<ItemType>& result)
	{
		if (mListData == nullptr)
		{
			return;
		}

		NodeType<ItemType>* tempPtr = mListData;
		NodeType<ItemType>* tempOtherPtr = other.mListData;

		while (tempPtr != nullptr && tempOtherPtr != nullptr)
		{
			if (tempPtr->mInfo < tempOtherPtr->mInfo)
			{
				result.InsertItem(tempPtr->mInfo);
				tempPtr = tempPtr->mNext;
			}
			else
			{
				result.InsertItem(tempOtherPtr->mInfo);
				tempOtherPtr = tempOtherPtr->mNext;
			}
		}

		while (tempPtr != nullptr)
		{
			result.InsertItem(tempPtr->mInfo);
			tempPtr = tempPtr->mNext;
		}

		while (tempOtherPtr != nullptr)
		{
			result.InsertItem(tempOtherPtr->mInfo);
			tempOtherPtr = tempOtherPtr->mNext;
		}
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const SortedType<T>& other)
	{
		NodeType<T>* tempPtr = other.mListData;
		size_t index = 0;
		while (tempPtr != nullptr)
		{
			os << "SortedList[" << index << "] = " << tempPtr->mInfo << std::endl;
			tempPtr = tempPtr->mNext;
			++index;
		}

		return os;
	}
}

namespace exercise05
{
	template <class ItemType>
	class SortedType
	{
	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const SortedType<T>& other);
	public:
		SortedType();
		~SortedType();

		bool IsFull() const;
		unsigned int  LengthIs() const;
		void MakeEmpty();
		void RetrieveItem(ItemType& item, bool& found);
		void InsertItem(ItemType item); 
		void DeleteItem(ItemType item);
		void ResetList();
		void GetNextItem(ItemType&);
		void MergeLists(const SortedType& other, SortedType& result);

	private:
		NodeType<ItemType>* mListData;
		unsigned int mLength;
		NodeType<ItemType>* mCurrentPos;
	};



	template <class ItemType>
	SortedType<ItemType>::SortedType()
		: mListData(nullptr), mLength(0), mCurrentPos(nullptr)
	{
	}

	template<class ItemType>
	bool SortedType<ItemType>::IsFull() const
	{
		NodeType<ItemType>* location;

		try
		{
			location = new NodeType<ItemType>;
			delete location;
			return false;
		}
		catch(std::bad_alloc exception)
		{
			return true;
		}
	}

	template <class ItemType>
	unsigned int SortedType<ItemType>::LengthIs() const
	{
		return mLength;
	}

	template <class ItemType>
	void SortedType<ItemType>::MakeEmpty()
	{
		NodeType<ItemType>* tempPtr;

		while (mListData != nullptr)
		{
			tempPtr = mListData;
			mListData = mListData->mNext;
			delete tempPtr;
		}

		mLength = 0;
	}

	template <class ItemType>
	void SortedType<ItemType>::RetrieveItem(ItemType& item, bool& found)
	{
		bool moreToSearch;
		NodeType<ItemType>* location;

		location = mListData;
		found = false;
		moreToSearch = (location != nullptr);

		while (moreToSearch && !found)
		{
			if (location->mInfo < item)
			{
				location = location->mNext;
				moreToSearch = (location != nullptr);
			}
			else if (item == location->mInfo)
			{
				found = true;
				item = location->mInfo;
			}
			else
			{
				moreToSearch = false;
			}
		}
	}

	template <class ItemType>
	void SortedType<ItemType>::InsertItem(ItemType item)
	{
		NodeType<ItemType>* newNode;  // pointer to node being inserted
		NodeType<ItemType>* predLoc;  // trailing pointer
		NodeType<ItemType>* location; // traveling pointer
		bool moreToSearch;

		location = mListData;
		predLoc = nullptr;
		moreToSearch = (location != nullptr);

		// Find insertion point.
		while (moreToSearch)
		{
			if (location->mInfo < item)
			{
				predLoc = location;
				location = location->mNext;
				moreToSearch = (location != nullptr);
			}
			else
			{
				moreToSearch = false;
			}
		}

		// Prepare node for insertion
		newNode = new NodeType<ItemType>;
		newNode->mInfo = item;
		// Insert node into list.
		if (predLoc == nullptr)         // Insert as first
		{
			newNode->mNext = mListData;
			mListData = newNode;
		}
		else
		{
			newNode->mNext = location;
			predLoc->mNext = newNode;
		}
		++mLength;
	}

	template <class ItemType>
	void SortedType<ItemType>::DeleteItem(ItemType item)
	{
		NodeType<ItemType>* prevPtr = nullptr;
		NodeType<ItemType>* curPtr = mListData;
		NodeType<ItemType>* itemToDelete = nullptr;

		while (curPtr != nullptr)
		{
			for (; curPtr != nullptr && curPtr->mInfo != item; prevPtr = curPtr, curPtr = curPtr->mNext)
			{
			}

			if (prevPtr == nullptr)
			{
				mListData = mListData->mNext;
				itemToDelete = curPtr;
				curPtr = curPtr->mNext;
				delete itemToDelete;
				--mLength;
			}
			else if (curPtr != nullptr)
			{
				prevPtr->mNext = curPtr->mNext;
				itemToDelete = curPtr;
				curPtr = curPtr->mNext;
				delete itemToDelete;
				--mLength;
			}
		}
	}

	template <class ItemType>
	void SortedType<ItemType>::ResetList()
	{
		mCurrentPos = nullptr;
	}
	
	template <class ItemType>
	void SortedType<ItemType>::GetNextItem(ItemType& item)
	{
		if (mListData == nullptr)
		{
			return;
		}

		if (mCurrentPos == nullptr)
		{
			mCurrentPos = mListData;
		}

		item = mCurrentPos->mInfo; 
		mCurrentPos = mCurrentPos->mNext;
	} 

	template <class ItemType>
	SortedType<ItemType>::~SortedType()
	{
		NodeType<ItemType>* tempPtr;

		while (mListData != nullptr)
		{
			tempPtr = mListData;
			mListData = mListData->mNext;
			delete tempPtr;
		}
	}

	template <class ItemType>
	void SortedType<ItemType>::MergeLists(const SortedType<ItemType>& other, SortedType<ItemType>& result)
	{
		if (mListData == nullptr)
		{
			return;
		}

		NodeType<ItemType>* tempPtr = mListData;
		NodeType<ItemType>* tempOtherPtr = other.mListData;

		while (tempPtr != nullptr && tempOtherPtr != nullptr)
		{
			if (tempPtr->mInfo < tempOtherPtr->mInfo)
			{
				result.InsertItem(tempPtr->mInfo);
				tempPtr = tempPtr->mNext;
			}
			else
			{
				result.InsertItem(tempOtherPtr->mInfo);
				tempOtherPtr = tempOtherPtr->mNext;
			}
		}

		while (tempPtr != nullptr)
		{
			result.InsertItem(tempPtr->mInfo);
			tempPtr = tempPtr->mNext;
		}

		while (tempOtherPtr != nullptr)
		{
			result.InsertItem(tempOtherPtr->mInfo);
			tempOtherPtr = tempOtherPtr->mNext;
		}
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const SortedType<T>& other)
	{
		NodeType<T>* tempPtr = other.mListData;
		size_t index = 0;
		while (tempPtr != nullptr)
		{
			os << "SortedList[" << index << "] = " << tempPtr->mInfo << std::endl;
			tempPtr = tempPtr->mNext;
			++index;
		}

		return os;
	}
}