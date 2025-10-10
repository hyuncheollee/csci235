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