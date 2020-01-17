#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

#include "TypeTraits.h"

namespace STL {

template<typename T>
class allocator {
public:
    using value_type = T;
    using size_type = std::size_t;
    using diffrence_type = std::ptrdiff_t;
    using propagate_on_container_move_assignment = true_type;
    using is_always_equal = true_type;

    constexpr allocator() noexcept = default;
    constexpr allocator(const allocator& other) noexcept = default;
    ~allocator() = default;

    template<typename U>
    constexpr allocator(const allocator<U>& other) noexcept {
    };

    [[nodiscard]] constexpr T* allocate(std::size_t n) {
        if(n > std::size_t(-1) / sizeof(T)) {
            throw std::bad_alloc();
        }
        return static_cast<T*>(::operator new(n * sizeof(T), std::align_val_t(alignof(T))));
    };
    
    constexpr void deallocate(T *p, std::size_t n) {
        ::operator delete(p, n * sizeof(T), std::align_val_t(alignof(T)));
        return;
    };
};

template<typename T, typename U>
constexpr bool operator==(const allocator<T>& lhs, const allocator<U>& rhs) noexcept {
    return true;
};
    
} // STL

#endif // ALLOCATOR_H_
