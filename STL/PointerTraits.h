#ifndef POINTER_TRAITS_H_
#define POINTER_TRAITS_H_

namespace STL {

    // TODO
template<typename Ptr>
struct pointer_traits {
};

template<typename T>
struct pointer_traits<T*> {
    using pointer = T*;
    using element_type = T;
    using difference_type = std::ptrdiff_t;
    
    template<typename U>
    using rebind = U*;

    static constexpr pointer pointer_to(element_type &r) noexcept {
        return std::addressof(r);
    };
};

} // STL

#endif // POINTER_TRAITS_H_
