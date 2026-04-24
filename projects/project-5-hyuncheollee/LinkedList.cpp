#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include "LinkedList.hpp"

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr_(nullptr), itemCount_(0) {}

template<class ItemType>
LinkedList<ItemType>::~LinkedList() {
    clear();
}

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const {
    return itemCount_ == 0;
}

template<class ItemType>
int LinkedList<ItemType>::getLength() const {
    return itemCount_;
}

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry) {
    if (newPosition < 1 || newPosition > itemCount_ + 1) return false;

    Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

    if (newPosition == 1) {
        newNodePtr->setNext(headPtr_);
        headPtr_ = newNodePtr;
    } else {
        Node<ItemType>* prevPtr = headPtr_;
        for (int i = 1; i < newPosition - 1; i++) {
            prevPtr = prevPtr->getNext();
        }
        newNodePtr->setNext(prevPtr->getNext());
        prevPtr->setNext(newNodePtr);
    }
    itemCount_++;
    return true;
}

template<class ItemType>
bool LinkedList<ItemType>::remove(int position) {
    if (position < 1 || position > itemCount_) return false;

    Node<ItemType>* curPtr = nullptr;
    if (position == 1) {
        curPtr = headPtr_;
        headPtr_ = headPtr_->getNext();
    } else {
        Node<ItemType>* prevPtr = headPtr_;
        for (int i = 1; i < position - 1; i++) {
            prevPtr = prevPtr->getNext();
        }
        curPtr = prevPtr->getNext();
        prevPtr->setNext(curPtr->getNext());
    }
    
    delete curPtr;
    itemCount_--;
    return true;
}

template<class ItemType>
void LinkedList<ItemType>::clear() {
    while (!isEmpty()) {
        remove(1);
    }
}

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const {
    if (position < 1 || position > itemCount_) throw "Index out of bounds";
    
    Node<ItemType>* ptr = headPtr_;
    for (int i = 1; i < position; i++) {
        ptr = ptr->getNext();
    }
    return ptr->getItem();
}
#endif