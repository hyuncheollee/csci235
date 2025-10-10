#pragma once

#include <cstddef>
#include <sstream>

template <class T>
struct Node {
    T value_;
    Node* next_;

    /**
     * @brief Constructs a Node with a value and a pointer to the next node.
     * @tparam T The type of the value stored in the node.
     * @param val A const reference to the value of type T to store in the node.
     * @param next Pointer to the next node in the list (Node<T>*).
     */
    Node(const T& val, Node* next = nullptr);
};

/**
 * @brief A singly linked list implementation.
 * @tparam T The type of elements stored in the list.
 */
template <class T>
class LinkedList {
private:
    Node<T>* head_ { nullptr };
    Node<T>* tail_ { nullptr };
    size_t size_ { 0 };

public:
    /**
     * @brief Default constructor: creates an empty list.
     */
    LinkedList() = default;

    /**
     * @brief Copy constructor (eg. how do we construct a copy of the list)
     */
    LinkedList(const LinkedList<T>& list);

    /**
     * @brief Copy assignment operator. Assigns another LinkedList's content to this one.
     * @param other The LinkedList to assign from.
     * @return A reference to this LinkedList.
     */
    LinkedList<T>& operator=(const LinkedList<T>& other);

    /**
     * @brief Stringifies the underlying LinkedList
     * @return A string of the form "{'<node_content_1>', ...}" representing the LinkedList's contents
     */
    std::string toString() const;

    // YOUR CODE BELOW =======
};

// DO NOT REMOVE, THIS IS NECESSARY SINCE NODE & LINKEDLIST ARE TEMPLATED
#include "LinkedList.cpp"