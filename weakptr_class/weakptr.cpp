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
    // Default constructor
    WeakPtr() noexcept {
        ptr_ = nullptr;
        control_ = nullptr;
    }

    // Construct from SharedPtr
    WeakPtr(const SharedPtr<T>& sp) noexcept {
        ptr_ = sp.ptr_;
        control_ = sp.control_;
        if (control_) {
            control_->weak_count += 1;
        }
    }

    // Copy constructor
    WeakPtr(const WeakPtr& other) noexcept {
        ptr_ = other.ptr_;
        control_ = other.control_;
        if (control_) {
            control_->weak_count += 1;
        }
    }

    // Move constructor
    WeakPtr(WeakPtr&& other) noexcept {
        ptr_ = other.ptr_;
        control_ = other.control_;
        other.ptr_ = nullptr;
        other.control_ = nullptr;
    }

    // Copy assignment
    WeakPtr& operator=(const WeakPtr& other) noexcept {
        if (this != &other) {
            reset();
            ptr_ = other.ptr_;
            control_ = other.control_;
            if (control_) {
                control_->weak_count += 1;
            }
        }
        return *this;
    }

    // Move assignment
    WeakPtr& operator=(WeakPtr&& other) noexcept {
        if (this != &other) {
            reset();
            ptr_ = other.ptr_;
            control_ = other.control_;
            other.ptr_ = nullptr;
            other.control_ = nullptr;
        }
        return *this;
    }

    // Assign from SharedPtr
    WeakPtr& operator=(const SharedPtr<T>& sp) noexcept {
        reset();
        ptr_ = sp.ptr_;
        control_ = sp.control_;
        if (control_) {
            control_->weak_count += 1;
        }
        return *this;
    }

    // Destructor
    ~WeakPtr() {
        reset();
    }

    // Returns number of strong references
    std::size_t use_count() const noexcept {
        if (control_) return control_->strong_count;
        return 0;
    }

    // Checks if the object is expired
    bool expired() const noexcept {
        return !control_ || control_->strong_count == 0;
    }

    // Returns a SharedPtr if object is still alive
    SharedPtr<T> lock() const noexcept {
        if (!expired()) {
            return SharedPtr<T>(*this);
        } else {
            return SharedPtr<T>();
        }
    }

    // Reset this weak pointer
    void reset() noexcept {
        if (control_) {
            if (control_->weak_count > 0) {
                control_->weak_count -= 1;
            }
            if (control_->strong_count == 0 && control_->weak_count == 0) {
                delete control_;
            }
        }
        ptr_ = nullptr;
        control_ = nullptr;
    }

    // Swap two WeakPtrs
    void swap(WeakPtr& other) noexcept {
        T* temp_ptr = ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = temp_ptr;
        detail::ControlBlock* temp_ctrl = control_;
        control_ = other.control_;
        other.control_ = temp_ctrl;
    }

private:
    T* ptr_;
    detail::ControlBlock* control_;

    // Allow SharedPtr to access private members
    friend class SharedPtr<T>;
};

} // namespace softacademy

#endif
