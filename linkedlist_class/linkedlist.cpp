#ifndef SOFTACADEMY_LIST_HPP
#define SOFTACADEMY_LIST_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>

namespace softacademy {

template <typename T>
class LinkedList {
public:
    using value_type = T;
    using size_type  = std::size_t;

    // Node structure
    struct Node {
        T value;
        Node* prev;
        Node* next;

        Node(const T& v, Node* p = nullptr, Node* n = nullptr)
            : value(v), prev(p), next(n) {}

        Node(T&& v, Node* p = nullptr, Node* n = nullptr)
            : value(std::move(v)), prev(p), next(n) {}
    };

    // Constructor
    LinkedList() noexcept {
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    // Copy constructor
    LinkedList(const LinkedList& other) {
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
        Node* current = other.head_;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }

    // Move constructor
    LinkedList(LinkedList&& other) noexcept {
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    // Copy assignment
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            Node* current = other.head_;
            while (current != nullptr) {
                push_back(current->value);
                current = current->next;
            }
        }
        return *this;
    }

    // Move assignment
    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // Destructor
    ~LinkedList() {
        clear();
    }

    // Size
    size_type size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }

    // Access front/back
    T& front() {
        if (!head_) throw std::out_of_range("List is empty");
        return head_->value;
    }

    const T& front() const {
        if (!head_) throw std::out_of_range("List is empty");
        return head_->value;
    }

    T& back() {
        if (!tail_) throw std::out_of_range("List is empty");
        return tail_->value;
    }

    const T& back() const {
        if (!tail_) throw std::out_of_range("List is empty");
        return tail_->value;
    }

    // Clear list
    void clear() noexcept {
        Node* current = head_;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    // Push front
    void push_front(const T& value) {
        Node* new_node = new Node(value, nullptr, head_);
        if (head_ != nullptr) head_->prev = new_node;
        head_ = new_node;
        if (tail_ == nullptr) tail_ = new_node;
        size_++;
    }

    void push_front(T&& value) {
        Node* new_node = new Node(std::move(value), nullptr, head_);
        if (head_ != nullptr) head_->prev = new_node;
        head_ = new_node;
        if (tail_ == nullptr) tail_ = new_node;
        size_++;
    }

    // Push back
    void push_back(const T& value) {
        Node* new_node = new Node(value, tail_, nullptr);
        if (tail_ != nullptr) tail_->next = new_node;
        tail_ = new_node;
        if (head_ == nullptr) head_ = new_node;
        size_++;
    }

    void push_back(T&& value) {
        Node* new_node = new Node(std::move(value), tail_, nullptr);
        if (tail_ != nullptr) tail_->next = new_node;
        tail_ = new_node;
        if (head_ == nullptr) head_ = new_node;
        size_++;
    }

    // Emplace front
    template <typename... Args>
    void emplace_front(Args&&... args) {
        Node* new_node = new Node(T(std::forward<Args>(args)...), nullptr, head_);
        if (head_ != nullptr) head_->prev = new_node;
        head_ = new_node;
        if (tail_ == nullptr) tail_ = new_node;
        size_++;
    }

    // Emplace back
    template <typename... Args>
    void emplace_back(Args&&... args) {
        Node* new_node = new Node(T(std::forward<Args>(args)...), tail_, nullptr);
        if (tail_ != nullptr) tail_->next = new_node;
        tail_ = new_node;
        if (head_ == nullptr) head_ = new_node;
        size_++;
    }

    // Pop front
    void pop_front() {
        if (head_ == nullptr) return;
        Node* temp = head_;
        head_ = head_->next;
        if (head_ != nullptr) head_->prev = nullptr;
        else tail_ = nullptr;
        delete temp;
        size_--;
    }

    // Pop back
    void pop_back() {
        if (tail_ == nullptr) return;
        Node* temp = tail_;
        tail_ = tail_->prev;
        if (tail_ != nullptr) tail_->next = nullptr;
        else head_ = nullptr;
        delete temp;
        size_--;
    }

    // Swap two lists
    void swap(LinkedList& other) noexcept {
        Node* temp_head = head_;
        head_ = other.head_;
        other.head_ = temp_head;

        Node* temp_tail = tail_;
        tail_ = other.tail_;
        other.tail_ = temp_tail;

        size_type temp_size = size_;
        size_ = other.size_;
        other.size_ = temp_size;
    }

private:
    Node* head_;
    Node* tail_;
    size_type size_;
};

} // namespace softacademy

#endif
