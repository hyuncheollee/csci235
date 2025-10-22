/*
Hyuncheol Lee
2025/10/17

this file deals with singly linked lists
*/

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

    /**
     * @brief Returns the number of elements in the list.
     * @return The number of elements (size_t).
     */
    size_t size() const;

    /**
     * @brief Checks if the list is empty (ie. contains no elements).
     * @return true if the list is empty, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Access the node pointing to the head of the linked list
     * @return A pointer to the head node (or nullptr if the list is empty)
     */
    Node<T>* head() const;

    /**
     * @brief Access the first element.
     * @return The first element's value (of type T, NOT the node).
     * @throws std::runtime_error if the list is empty.
     */
    T front() const;

    /**
     * @brief Access the last element.
     * @return The last element's value (of type T, , NOT the node).
     * @throws std::runtime_error if the list is empty.
     */
    T back() const;

    /**
     * @brief Access an element at a specific index.
     * @param index The zero-based index of the element (size_t).
     * @return The element's value at the given index (of type T).
     *
     * @throws std::out_of_range if the index is invalid (eg. too large).
     */
    T at(size_t index) const;

    /**
     * @brief Adds an element to the end of the list.
     * @param value A const reference to the value (of type T)
     * to add to the end of the list
     */
    void push_back(const T& value);

    /**
     * @brief Inserts an element at a specific index.
     * @param index The zero-based index to insert at (as a size_t).
     * @param value A const reference to the value (of type T) to insert.
     *
     * @throws std::out_of_range if the index is strictly greater than the size
     * @note That is, if we insert at index 1 when we have a list of length 1,
     *    that's fine! We just insert at the end. Inserting at index 2 would raise
     *    an error though.
     */
    void insert(size_t index, const T& value);

    /**
     * @brief Erases an element at a specific index.
     * @param index The zero-based index of the element to erase (as asize_t).
     *
     * @throws std::out_of_range if index is greater than or equal to the size
     */
    void erase(size_t index);

    /**
     * @brief Removes all elements from the list.
     */
    void clear();

    /**
     * @brief Destructor: cleans up all nodes to prevent memory leaks.
     */
    ~LinkedList();
};

// DO NOT REMOVE, THIS IS NECESSARY SINCE NODE & LINKEDLIST ARE TEMPLATED
#include "LinkedList.cpp"