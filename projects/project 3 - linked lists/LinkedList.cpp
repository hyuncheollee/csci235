/*
Hyuncheol Lee
2025/10/17

this file deals with singly linked lists
*/

#include "LinkedList.hpp"

/**
 * @brief Constructs a Node with a given value.
 */
template <class T>
Node<T>::Node(const T& val, Node* next)
    : value_(val)
    , next_(next)
{
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs)
    : size_ { 0 }
{
    // Perform the deep copy from the other list
    for (Node<T>* current = rhs.head_; current != nullptr; current = current->next_) {
        push_back(current->value_);
    }
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
    // 1. Check for self-assignment
    if (this == &other) {
        return *this;
    }

    // 2. Clear the current list's contents to prevent memory leaks
    clear();

    // 3. Perform the deep copy from the other list
    for (Node<T>* current = other.head_; current != nullptr; current = current->next_) {
        push_back(current->value_);
    }

    // 4. Return a reference to the current object to allow for chained assignments
    return *this;
}

/**
 * @brief Stringifies the underlying LinkedList
 * @return A string of the form "{'<node_content_1>', ...}" representing the LinkedList's contents
 */
template <class T>
std::string LinkedList<T>::toString() const
{
    std::stringstream ss;
    ss << "size: " << size() << " - ";
    ss << "{ ";

    Node<T>* p = head_;
    for (size_t i = 0; i < size(); i++) {
        ss << p->value_;

        if (i + 1 != size()) {
            ss << ", ";
        }
        p = p->next_;
    }

    ss << " }";
    return ss.str();
}

// YOUR CODE BELOW. DO NOT MODIFY ABOVE.

/**
 * @brief Returns the number of elements in the list.
 * @return The number of elements (size_t).
 */
template <class T>
size_t LinkedList<T>::size() const {
    return size_;
}

/**
 * @brief Checks if the list is empty (ie. contains no elements).
 * @return true if the list is empty, false otherwise.
 */
template <class T>
bool LinkedList<T>::empty() const {
    // checks if list is empty
    if (size_ == 0) {
        return true;
    }
    return false;
}

/**
 * @brief Access the node pointing to the head of the linked list
 * @return A pointer to the head node (or nullptr if the list is empty)
 */
template <class T>
Node<T>* LinkedList<T>::head() const {
    // checks if list is empty
    if (empty()) {
        return nullptr;
    }
    return head_;
}

/**
 * @brief Access the first element.
 * @return The first element's value (of type T, NOT the node).
 * @throws std::runtime_error if the list is empty.
 */
template <class T>
T LinkedList<T>::front() const {
    // checks if list is empty
    if (empty()) {
        throw std::runtime_error("the list is empty");
    }
    
    return head_ -> value_;
}

/**
 * @brief Access the last element.
 * @return The last element's value (of type T, , NOT the node).
 * @throws std::runtime_error if the list is empty.
 */
template <class T>
T LinkedList<T>::back() const {
    // checks if list is empty
    if (empty()) {
        throw std::runtime_error("the list is empty");
    }

    return tail_ -> value_;
}

/**
 * @brief Access an element at a specific index.
 * @param index The zero-based index of the element (size_t).
 * @return The element's value at the given index (of type T).
 *
 * @throws std::out_of_range if the index is invalid (eg. too large).
 */
template <class T>
T LinkedList<T>::at(size_t index) const {
    // checks if index is larger than number of nodes
    if (index >= size_) {
        throw std::out_of_range("index is out of range");
    }

    // start from the head
    Node<T>* current = head_;
    
    // indexing through to desired index
    for (size_t i = 0; i < index; i++) { 
        current = current -> next_;
    }

    // found that node
    return current -> value_;
}

/**
 * @brief Adds an element to the end of the list.
 * @param value A const reference to the value (of type T)
 * to add to the end of the list
 */
template <class T>
void LinkedList<T>::push_back(const T& value) {
    // creating node
    Node<T>* new_node = new Node<T>(value);

    // if empty, assign new node to both head and tail
    if (empty()) {
        head_ = new_node;
        tail_ = new_node;
    }

    // if not, assign new node to just tail
    else {
        tail_ -> next_ = new_node;      
        tail_ = new_node;               // old tail pointer is updated to new tail
    }
    
    // add one more to size of list
    size_++;
}

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
template <class T>
void LinkedList<T>::insert(size_t index, const T& value) {
    // check if index is within range
    if (index > size_) {
        throw std::out_of_range("index is larger than size of list");
    }

    // create new node
    Node<T>* new_node = new Node<T>(value);

    // if we want to insert in the front
    if (index == 0) {
        new_node -> next_ = head_;      // new node -> old head
        head_ = new_node;               // head now -> new node

        // if list was empty, new node should be assigned to tail as well
        if (empty()) {
            tail_ = new_node;
        }
    }

    // if we want to insert at the tail
    else if (index == size_) {
        tail_ -> next_ = new_node;          // old tail -> new node
        tail_ = new_node;                   // update tail -> new node
    }

    // if we're inserting anywhere else
    else {
        // start from beginning of list
        Node<T>* prev = head_;

        // iterate through the list
        for (size_t i = 0; i < index - 1; i++) {
            prev = prev -> next_;
        }

        // insert new node
        new_node -> next_ = prev -> next_;
        prev -> next_ = new_node;
    }

    // dont forget to increase list size
    size_++;
}

/**
 * @brief Erases an element at a specific index.
 * @param index The zero-based index of the element to erase (as asize_t).
 *
 * @throws std::out_of_range if index is greater than or equal to the size
 */
template <class T>
void LinkedList<T>::erase(size_t index) {
    // check if index is out of range
    if (index >= size_) {
        throw std::out_of_range("index is out of range");
    }

    // preparing to delete node
    Node<T>* to_delete = nullptr;

    // if we're removing the head
    if (index == 0) {
        to_delete = head_;          // save current head for deleting
        head_ = head_ -> next_;     // assign head to next node

        // if we're deleting the only node we need to make tail nullptr as well
        if (head_ == nullptr) {
            tail_ = nullptr;
        }
    }

    // removing anything but the head
    else {
        // start from beginning of list
        Node<T>* prev = head_;
        
        // index to the node[-1] we want to delete
        for (size_t i = 0; i < index - 1; ++i) {
            prev = prev -> next_;
        }

        // the node to delete is the one after prev
        to_delete = prev -> next_;

        // bypass node to delete
        prev -> next_ = to_delete -> next_;
        
        // if we delete tail, update tail_ -> prev
        if (to_delete == tail_) {
            tail_ = prev;
        }
    }

    // housekeeping
    delete to_delete;       // free memory of deleted node
    size_--;                // decrement size of list

}

/**
 * @brief Removes all elements from the list.
 */
template <class T>
void LinkedList<T>::clear() {
    // start at the head
    Node<T>* current = head_;

    // iterate through list
    while (current != nullptr) {
        Node<T>* next_node = current->next_;  // keep track of next node
        delete current;                       // free memory of current node
        current = next_node;                  // move to next node
    }

    // housekeeping
    head_ = nullptr;        // reset head of list
    tail_ = nullptr;        // reset tail of list
    size_ = 0;              // size of list is now 0
}

/**
 * @brief Destructor: cleans up all nodes to prevent memory leaks.
 */
template <class T>
LinkedList<T>::~LinkedList() {
    // calls the clear function
    clear();
}
