#ifndef SOFTACADEMY_WEAK_PTR_HPP
#define SOFTACADEMY_WEAK_PTR_HPP

#include <cstddef>

namespace softacademy {

template <typename T> class SharedPtr;

namespace detail {
struct ControlBlock {
    std::size_t strong_count;
    std::size_t weak_count;

    ControlBlock() : strong_count(1), weak_count(0) {}
};
}

template <typename T>
class WeakPtr {
public:
    WeakPtr() noexcept {
        m_ptr = nullptr;
        m_control = nullptr;
    }

    WeakPtr(const SharedPtr<T>& sp) noexcept {
        m_ptr = sp.m_ptr;
        m_control = sp.m_control;
        if (m_control != nullptr) {
            m_control->weak_count += 1;
        }
    }

    WeakPtr(const WeakPtr& other) noexcept {
        m_ptr = other.m_ptr;
        m_control = other.m_control;
        if (m_control != nullptr) {
            m_control->weak_count += 1;
        }
    }

    WeakPtr(WeakPtr&& other) noexcept {
        m_ptr = other.m_ptr;
        m_control = other.m_control;
        other.m_ptr = nullptr;
        other.m_control = nullptr;
    }

    WeakPtr& operator=(const WeakPtr& other) noexcept {
        if (this != &other) {
            reset();
            m_ptr = other.m_ptr;
            m_control = other.m_control;
            if (m_control != nullptr) {
                m_control->weak_count += 1;
            }
        }
        return *this;
    }

    WeakPtr& operator=(WeakPtr&& other) noexcept {
        if (this != &other) {
            reset();
            m_ptr = other.m_ptr;
            m_control = other.m_control;
            other.m_ptr = nullptr;
            other.m_control = nullptr;
        }
        return *this;
    }

    WeakPtr& operator=(const SharedPtr<T>& sp) noexcept {
        reset();
        m_ptr = sp.m_ptr;
        m_control = sp.m_control;
        if (m_control != nullptr) {
            m_control->weak_count += 1;
        }
        return *this;
    }

    ~WeakPtr() {
        reset();
    }

    std::size_t use_count() const noexcept {
        if (m_control != nullptr) {
            return m_control->strong_count;
        } else {
            return 0;
        }
    }

    bool expired() const noexcept {
        if (m_control == nullptr) {
            return true;
        }
        if (m_control->strong_count == 0) {
            return true;
        }
        return false;
    }

    // Returns a SharedPtr if object is still alive
    SharedPtr<T> lock() const noexcept {
        if (!expired()) {
            return SharedPtr<T>(*this);
        } else {
            return SharedPtr<T>();
        }
    }

    void reset() noexcept {
        if (m_control != nullptr) {
            if (m_control->weak_count > 0) {
                m_control->weak_count -= 1;
            }
            if (m_control->strong_count == 0) {
                if (m_control->weak_count == 0) {
                    delete m_control;
                }
            }
        }
        m_ptr = nullptr;
        m_control = nullptr;
    }

    void swap(WeakPtr& other) noexcept {
        T* temp_ptr = m_ptr;
        m_ptr = other.m_ptr;
        other.m_ptr = temp_ptr;

        detail::ControlBlock* temp_ctrl = m_control;
        m_control = other.m_control;
        other.m_control = temp_ctrl;
    }

private:
    T* m_ptr;
    detail::ControlBlock* m_control;

    // Allow SharedPtr to access private members
    friend class SharedPtr<T>;
};

} // namespace softacademy

#endif
