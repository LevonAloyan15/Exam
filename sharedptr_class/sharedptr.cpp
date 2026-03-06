#ifndef SOFTACADEMY_SHARED_PTR_HPP
#define SOFTACADEMY_SHARED_PTR_HPP

#include <cstddef>
#include <utility>

namespace softacademy {

template <typename T> class WeakPtr;

namespace detail {
struct ControlBlock {
    ControlBlock(): strong_count(0), weak_count(0) {}
    ~ControlBlock() {}
    std::size_t strong_count;
    std::size_t weak_count;
};
} // namespace detail

template <typename T>
class SharedPtr {
public:
    using element_type = T;

    explicit SharedPtr(T* ptr) : m_ptr(ptr), m_control(new detail::ControlBlock()) {
        m_control->strong_count++;
    }

    SharedPtr(const SharedPtr& other) noexcept : m_ptr(other.m_ptr), m_control(other.m_control) {
        m_control->strong_count++;
    }

    SharedPtr(SharedPtr&& other) noexcept : m_ptr(other.m_ptr), m_control(other.m_control) {
        other.m_ptr = nullptr;
        other.m_control = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& other) noexcept {
        if (this != &other) {
            m_ptr = other.m_ptr;
            m_control = other.m_control;
            m_control->strong_count++;
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            m_ptr = other.m_ptr;
            m_control = other.m_control;
            other.m_ptr = nullptr;
            other.m_control = nullptr;
        }
        return *this;
    }

    ~SharedPtr() {
        m_control->strong_count--;
        if (m_control->strong_count == 0) {
            delete m_ptr;
            if (m_control->weak_count == 0) {
                delete m_control;
            }
        }
    }

    T* get() const noexcept { return m_ptr; }
    T& operator*() const { return *m_ptr; }
    T* operator->() const noexcept { return m_ptr; }

    std::size_t use_count(const SharedPtr& ptr) const noexcept {
        return ptr.m_control->strong_count;
    }

    explicit operator bool() const noexcept { return m_ptr != nullptr; }

    void reset() noexcept {
        m_control->strong_count--;
        if (m_control->strong_count == 0) {
            delete m_ptr;
        }
        m_ptr = nullptr;
        m_control = nullptr;
    }

    void reset(T* ptr) {
        m_control->strong_count--;
        if (m_control->strong_count == 0) {
            delete m_ptr;
        }
        m_ptr = ptr;
    }

    void swap(SharedPtr& other) noexcept {
        std::swap(m_ptr, other.m_ptr);
        std::swap(m_control, other.m_control);
    }
private:
    T* m_ptr;
    detail::ControlBlock* m_control;

    friend class WeakPtr<T>;

} // namespace softacademy

#endif
int main() {

 return 0;
}
};

        m_control = new detail::ControlBlock();
