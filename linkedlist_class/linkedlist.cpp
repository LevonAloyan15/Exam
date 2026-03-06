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

    struct Node {
        T value;
        Node* prev;
        Node* next;

        Node(const T& v, Node* p = nullptr, Node* n = nullptr)
            : value(v), prev(p), next(n) {}

        Node(T&& v, Node* p = nullptr, Node* n = nullptr)
            : value(std::move(v)), prev(p), next(n) {}
    };

    LinkedList() noexcept {
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
    }

    LinkedList(const LinkedList& other) {
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
        Node* current = other.m_head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }

    LinkedList(LinkedList&& other) noexcept {
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_size = other.m_size;
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            Node* current = other.m_head;
            while (current != nullptr) {
                push_back(current->value);
                current = current->next;
            }
        }
        return *this;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            m_head = other.m_head;
            m_tail = other.m_tail;
            m_size = other.m_size;
            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    ~LinkedList() {
        clear();
    }

    size_type size() const noexcept {
        return m_size;
    }

    bool empty() const noexcept {
        return m_size == 0;
    }


    T& front() {
        if (!m_head) {
            throw std::out_of_range("List is empty");
        }
        return m_head->value;
    }

    const T& front() const {
        if (!m_head) {
            throw std::out_of_range("List is empty");
        }
        return m_head->value;
    }

    T& back() {
        if (!m_tail) {
            throw std::out_of_range("List is empty");
        }
        return m_tail->value;
    }

    const T& back() const {
        if (!m_tail) {
            throw std::out_of_range("List is empty");
        }
        return m_tail->value;
    }

    void clear() noexcept {
        Node* current = m_head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
    }


    void push_front(const T& value) {
        Node* new_node = new Node(value, nullptr, m_head);
        if (m_head != nullptr) {
            m_head->prev = new_node;
        }
        m_head = new_node;
        if (m_tail == nullptr) {
            m_tail = new_node;
        }
        m_size++;
    }

    void push_front(T&& value) {
        Node* new_node = new Node(std::move(value), nullptr, m_head);
        if (m_head != nullptr) {
            m_head->prev = new_node;
        }
        m_head = new_node;
        if (m_tail == nullptr) {
            m_tail = new_node;
        }
        m_size++;
    }

    void push_back(const T& value) {
        Node* new_node = new Node(value, m_tail, nullptr);
        if (m_tail != nullptr) {
            m_tail->next = new_node;
        }
        m_tail = new_node;
        if (m_head == nullptr) {
            m_head = new_node;
        }
        m_size++;
    }

    void push_back(T&& value) {
        Node* new_node = new Node(std::move(value), m_tail, nullptr);
        if (m_tail != nullptr) {
            m_tail->next = new_node;
        }
        m_tail = new_node;
        if (m_head == nullptr) {
            m_head = new_node;
        }
        m_size++;
    }

    


    void pop_front() {
        if (m_head == nullptr) {
            return;
        }
        Node* temp = m_head;
        m_head = m_head->next;
        if (m_head != nullptr) {
            m_head->prev = nullptr;
        } else {
            m_tail = nullptr;
        }
        delete temp;
        m_size--;
    }

    void pop_back() {
        if (m_tail == nullptr) {
            return;
        }
        Node* temp = m_tail;
        m_tail = m_tail->prev;
        if (m_tail != nullptr) {
            m_tail->next = nullptr;
        } else {
            m_head = nullptr;
        }
        delete temp;
        m_size--;
    }

    void swap(LinkedList& other) noexcept {
        Node* temp_head = m_head;
        m_head = other.m_head;
        other.m_head = temp_head;

        Node* temp_tail = m_tail;
        m_tail = other.m_tail;
        other.m_tail = temp_tail;

        size_type temp_size = m_size;
        m_size = other.m_size;
        other.m_size = temp_size;
    }

private:
    Node* m_head;
    Node* m_tail;
    size_type m_size;
};

} // namespace softacademy

#endif
