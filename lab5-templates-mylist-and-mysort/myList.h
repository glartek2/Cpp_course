// myList.h
#ifndef MYLIST_H
#define MYLIST_H

#include <memory>
#include <stdexcept>
#include <iostream>


#define IMPLEMENTED_constructorOfEmptyList
#define IMPLEMENTED_pushingAndPopingElementsFront
#define IMPLEMENTED_nodesStoredAsUniquePtrs
#define IMPLEMENTED_popFromWhenEmptyList
#define IMPLEMENTED_copyingDisabled
#define IMPLEMENTED_removingElements
#define IMPLEMENTED_iteratorOperations
#define IMPLEMENTED_iteratorWithRangedForLoop
#define IMPLEMENTED_iteratorWithStlAlgorithm
#define IMPLEMENTED_ostreamOperator

template<typename T>
class MyList {
protected:
    struct Node {
        T data_;
        std::unique_ptr<Node> next_;

        Node(const T& data) : data_(data), next_(nullptr) {}
    };

    std::unique_ptr<Node> head_;
    size_t size_;

public:
    typedef T value_type;

    MyList() : head_(nullptr), size_(0) {}

    size_t size() const {
        return size_;
    }

    void push_front(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        newNode->next_ = std::move(head_);
        head_ = std::move(newNode);
        ++size_;
    }

    T pop_front() {
        if (empty())
            throw std::out_of_range("pop_front() called on empty list");

        auto oldHead = std::move(head_);
        head_ = std::move(oldHead->next_);
        --size_;
        return oldHead->data_;
    }

    T& front() const {
        if (empty())
            throw std::out_of_range("front() called on empty list");

        return head_->data_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void remove(const T& element) {
        while (head_ && head_->data_ == element) {
            pop_front();
        }

        if (!head_)
            return;

        auto current = head_.get();
        while (current->next_) {
            if (current->next_->data_ == element) {
                current->next_ = std::move(current->next_->next_);
                --size_;
            } else {
                current = current->next_.get();
            }
        }
    }

    class Iterator {
    private:
        Node* current_;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Node* node) : current_(node) {}

        T& operator*() const {
            return current_->data_;
        }

        Iterator& operator++() {
            if (current_)
                current_ = current_->next_.get();
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator!=(const Iterator& other) const {
            return current_ != other.current_;
        }

        bool operator==(const Iterator& other) const {
            return current_ == other.current_;
        }
    };

    Iterator begin() const {
        return Iterator(head_.get());
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    void assign(Iterator first, Iterator last) {
        clear();
        for (auto it = first; it != last; ++it) {
            push_front(*it);
        }
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    // Disable copying
    MyList(const MyList&) = delete;
    MyList& operator=(const MyList&) = delete;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const MyList<T>& list) {
    for (const auto& element : list) {
        os << element << " ";
    }
    return os;
}

#endif // MYLIST_H
