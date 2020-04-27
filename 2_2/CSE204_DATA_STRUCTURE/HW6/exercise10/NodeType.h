#pragma once

template<class ItemType>
struct NodeType
{
    ItemType mInfo;
    NodeType* mNext;
};