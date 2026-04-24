/**
 * @file LinkedList.hpp
 * @brief Standard Linked List Template.
 */
#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "Node.hpp"
#include <vector>

template<class ItemType>
class LinkedList {
public:
    LinkedList();
    virtual ~LinkedList();

    bool isEmpty() const;
    int getLength() const;
    bool insert(int newPosition, const ItemType& newEntry);
    bool remove(int position);
    void clear();
    ItemType getEntry(int position) const;

protected:
    Node<ItemType>* headPtr_;
    int itemCount_;
};

#include "LinkedList.cpp" // Include implementation for templates
#endif