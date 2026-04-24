/**
 * @file Node.hpp
 * @brief Standard Node class for Linked List.
 */
#ifndef NODE_HPP
#define NODE_HPP

template<class ItemType>
class Node {
public:
    Node() : next_(nullptr) {}
    Node(const ItemType& anItem) : item_(anItem), next_(nullptr) {}
    Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) 
        : item_(anItem), next_(nextNodePtr) {}

    void setItem(const ItemType& anItem) { item_ = anItem; }
    void setNext(Node<ItemType>* nextNodePtr) { next_ = nextNodePtr; }

    ItemType getItem() const { return item_; }
    Node<ItemType>* getNext() const { return next_; }

private:
    ItemType item_;
    Node<ItemType>* next_;
};
#endif