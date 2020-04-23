#pragma once

#include <iostream>

namespace exercise03
{
	template<class ItemType>
	struct NodeType
	{
		ItemType mInfo;
		NodeType* mNext;
	};

	template <class ItemType>
	class UnsortedType
	{
	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const UnsortedType<T>& other);
	public:
		UnsortedType();	
		~UnsortedType();

		bool IsFull() const;
		unsigned int  LengthIs() const;
		void MakeEmpty();
		void RetrieveItem(ItemType& item, bool& found);
		void InsertItem(ItemType item); 
		void DeleteItem(ItemType item);
		void ResetList();
		void GetNextItem(ItemType& item);
		void MergeLists(const UnsortedType& other, UnsortedType& result);

	private:
		NodeType<ItemType>* mListData;
		unsigned int mLength;
		NodeType<ItemType>* mCurrentPos;
	};



	template <class ItemType>
	UnsortedType<ItemType>::UnsortedType()
		: mListData(nullptr), mLength(0), mCurrentPos(nullptr)
	{
	}

	template <class ItemType>
	UnsortedType<ItemType>::~UnsortedType()
	{
		MakeEmpty();
	}

	template<class ItemType>
	bool UnsortedType<ItemType>::IsFull() const
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
	unsigned int UnsortedType<ItemType>::LengthIs() const
	{
		return mLength;
	}

	template <class ItemType>
	void UnsortedType<ItemType>::MakeEmpty()
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
	void UnsortedType<ItemType>::RetrieveItem(ItemType& item, bool& found)
	{
		bool moreToSearch;
		NodeType<ItemType>* location;

		location = mListData;
		found = false;
		moreToSearch = (location != nullptr);

		while (moreToSearch && !found)
		{
			if (item == location->mInfo)
			{
				found = true;
				item = location->mInfo;
			}
			else
			{
				location = location->mNext;
				moreToSearch = (location != nullptr);
			}
		}
	}
	template <class ItemType>
	void UnsortedType<ItemType>::InsertItem(ItemType item)
	{
		NodeType<ItemType>* location;

		location = new NodeType<ItemType>;
		location->mInfo = item;
		location->mNext = mListData;
		mListData = location;
		mLength++;
	}

	template <class ItemType>
	void UnsortedType<ItemType>::DeleteItem(ItemType item)
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
		mLength--;
	}

	template <class ItemType>
	void UnsortedType<ItemType>::ResetList()
	// Post: Current position has been initialized.
	{
		mCurrentPos = nullptr;
	}
	
	template <class ItemType>
	void UnsortedType<ItemType>::GetNextItem(ItemType& item)
	// Post:  Current position has been updated; item is current item.
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
	void UnsortedType<ItemType>::MergeLists(const UnsortedType<ItemType>& other, UnsortedType<ItemType>& result)
	{
		if (mListData == nullptr)
		{
			return;
		}

		NodeType<ItemType>* tempPtr = mListData;
		UnsortedType<ItemType> tempList;

		while (tempPtr != nullptr)
		{
			tempList.InsertItem(tempPtr->mInfo);
			tempPtr = tempPtr->mNext;
		}

		tempPtr = other.mListData;
		while (tempPtr != nullptr)
		{
			tempList.InsertItem(tempPtr->mInfo);
			tempPtr = tempPtr->mNext;
		}

		tempPtr = tempList.mListData;
		while (tempPtr != nullptr)
		{
			result.InsertItem(tempPtr->mInfo);
			tempPtr = tempPtr->mNext;
		}
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const UnsortedType<T>& other)
	{
		NodeType<T>* tempPtr = other.mListData;
		size_t index = 0;
		while (tempPtr != nullptr)
		{
			os << "UnsortedList[" << index << "] = " << tempPtr->mInfo << std::endl;
			tempPtr = tempPtr->mNext;
			++index;
		}

		return os;
	}
}

namespace exercise04
{
	template<class ItemType>
	struct NodeType
	{
		ItemType mInfo;
		NodeType* mNext;
	};

	template <class ItemType>
	class UnsortedType
	{
	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const UnsortedType<T>& other);
	public:
		UnsortedType();	
		~UnsortedType();

		bool IsFull() const;
		unsigned int  LengthIs() const;
		void MakeEmpty();
		void RetrieveItem(ItemType& item, bool& found);
		void InsertItem(ItemType item); 
		void DeleteItem(ItemType item);
		void ResetList();
		void GetNextItem(ItemType& item);
		void MergeLists(const UnsortedType& other, UnsortedType& result);

	private:
		NodeType<ItemType>* mListData;
		unsigned int mLength;
		NodeType<ItemType>* mCurrentPos;
	};



	template <class ItemType>
	UnsortedType<ItemType>::UnsortedType()
		: mListData(nullptr), mLength(0), mCurrentPos(nullptr)
	{
	}

	template <class ItemType>
	UnsortedType<ItemType>::~UnsortedType()
	{
		MakeEmpty();
	}

	template<class ItemType>
	bool UnsortedType<ItemType>::IsFull() const
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
	unsigned int UnsortedType<ItemType>::LengthIs() const
	{
		return mLength;
	}

	template <class ItemType>
	void UnsortedType<ItemType>::MakeEmpty()
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
	void UnsortedType<ItemType>::RetrieveItem(ItemType& item, bool& found)
	{
		bool moreToSearch;
		NodeType<ItemType>* location;

		location = mListData;
		found = false;
		moreToSearch = (location != nullptr);

		while (moreToSearch && !found)
		{
			if (item == location->mInfo)
			{
				found = true;
				item = location->mInfo;
			}
			else
			{
				location = location->mNext;
				moreToSearch = (location != nullptr);
			}
		}
	}
	template <class ItemType>
	void UnsortedType<ItemType>::InsertItem(ItemType item)
	{
		NodeType<ItemType>* location;

		location = new NodeType<ItemType>;
		location->mInfo = item;
		location->mNext = mListData;
		mListData = location;
		mLength++;
	}

	template <class ItemType>
	void UnsortedType<ItemType>::DeleteItem(ItemType item)
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
	void UnsortedType<ItemType>::ResetList()
	// Post: Current position has been initialized.
	{
		mCurrentPos = nullptr;
	}
	
	template <class ItemType>
	void UnsortedType<ItemType>::GetNextItem(ItemType& item)
	// Post:  Current position has been updated; item is current item.
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
	void UnsortedType<ItemType>::MergeLists(const UnsortedType<ItemType>& other, UnsortedType<ItemType>& result)
	{
		if (mListData == nullptr)
		{
			return;
		}

		NodeType<ItemType>* tempPtr = mListData;
		UnsortedType<ItemType> tempList;

		while (tempPtr != nullptr)
		{
			tempList.InsertItem(tempPtr->mInfo);
			tempPtr = tempPtr->mNext;
		}

		tempPtr = other.mListData;
		while (tempPtr != nullptr)
		{
			tempList.InsertItem(tempPtr->mInfo);
			tempPtr = tempPtr->mNext;
		}

		tempPtr = tempList.mListData;
		while (tempPtr != nullptr)
		{
			result.InsertItem(tempPtr->mInfo);
			tempPtr = tempPtr->mNext;
		}
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const UnsortedType<T>& other)
	{
		NodeType<T>* tempPtr = other.mListData;
		size_t index = 0;
		while (tempPtr != nullptr)
		{
			os << "UnsortedList[" << index << "] = " << tempPtr->mInfo << std::endl;
			tempPtr = tempPtr->mNext;
			++index;
		}

		return os;
	}
}