#ifndef SOFTACADEMY_VECTOR_HPP
#define SOFTACADEMY_VECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace softacademy {

template <typename T>
class Vector {
public:
    using value_type = T;
    using size_type  = std::size_t;

    Vector() noexcept {
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    explicit Vector(size_type count) {
        if (count == 0) {
            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;
        } else {
            m_data = new T[count];
            for (size_type i = 0; i < count; ++i) {
                m_data[i] = T();
            }
            m_size = count;
            m_capacity = count;
        }
    }

    Vector(const Vector& other) {
        if (other.m_size == 0) {
            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;
        } else {
            m_data = new T[other.m_size];
            for (size_type i = 0; i < other.m_size; ++i) {
                m_data[i] = other.m_data[i];
            }
            m_size = other.m_size;
            m_capacity = other.m_size;
        }
    }

    Vector(Vector&& other) noexcept {
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] m_data;

            if (other.m_size == 0) {
                m_data = nullptr;
                m_size = 0;
                m_capacity = 0;
            } else {
                m_data = new T[other.m_size];
                for (size_type i = 0; i < other.m_size; ++i) {
                    m_data[i] = other.m_data[i];
                }
                m_size = other.m_size;
                m_capacity = other.m_size;
            }
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] m_data;

            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    ~Vector() {
        delete[] m_data;
    }

    size_type size() const noexcept {
        return m_size;
    }

    size_type capacity() const noexcept {
        return m_capacity;
    }

    bool empty() const noexcept {
        return m_size == 0;
    }

    T& operator[](size_type index) {
        return m_data[index];
    }

    const T& operator[](size_type index) const {
        return m_data[index];
    }

    T& at(size_type index) {
        if (index >= m_size) {
            throw std::out_of_range("Vector::at");
        }
        return m_data[index];
    }

    const T& at(size_type index) const {
        if (index >= m_size) {
            throw std::out_of_range("Vector::at");
        }
        return m_data[index];
    }

    T& front() {
        return m_data[0];
    }

    const T& front() const {
        return m_data[0];
    }

    T& back() {
        return m_data[m_size - 1];
    }

    const T& back() const {
        return m_data[m_size - 1];
    }

    T* data() noexcept {
        return m_data;
    }

    const T* data() const noexcept {
        return m_data;
    }

    void push_back(const T& value) {
        if (m_size >= m_capacity) {
            size_type new_capacity = m_capacity + 5;
            T* new_data = new T[new_capacity];
            for (size_type i = 0; i < m_size; ++i) {
                new_data[i] = std::move(m_data[i]);
            }
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }
        m_data[m_size] = value;
        m_size += 1;
    }

    void push_back(T&& value) {
        if (m_size >= m_capacity) {
            size_type new_capacity = m_capacity + 5;
            T* new_data = new T[new_capacity];
            for (size_type i = 0; i < m_size; ++i) {
                new_data[i] = std::move(m_data[i]);
            }
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }
        m_data[m_size] = std::move(value);
        m_size += 1;
    }

    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (m_size >= m_capacity) {
            size_type new_capacity = m_capacity + 5;
            T* new_data = new T[new_capacity];
            for (size_type i = 0; i < m_size; ++i) {
                new_data[i] = std::move(m_data[i]);
            }
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }
        m_data[m_size] = T(std::forward<Args>(args)...);
        m_size += 1;
    }

    void pop_back() {
        if (m_size > 0) {
            m_size -= 1;
        }
    }

    void resize(size_type new_size, const T& value = T()) {
        if (new_size > m_capacity) {
            T* new_data = new T[new_size];
            for (size_type i = 0; i < m_size; ++i) {
                new_data[i] = std::move(m_data[i]);
            }
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_size;
        }
        for (size_type i = m_size; i < new_size; ++i) {
            m_data[i] = value;
        }
        m_size = new_size;
    }

    
    void clear() noexcept {
        m_size = 0;
    }

    void swap(Vector& other) noexcept {
        T* temp_data = m_data;
        m_data = other.m_data;
        other.m_data = temp_data;

        size_type temp_size = m_size;
        m_size = other.m_size;
        other.m_size = temp_size;

        size_type temp_capacity = m_capacity;
        m_capacity = other.m_capacity;
        other.m_capacity = temp_capacity;
    }

public:
    T* m_data;
    size_type m_size;
    size_type m_capacity;
};

} // namespace softacademy

#endif
