#ifndef ALLOCATOR_TRAITS_H_
#define ALLOCATOR_TRAITS_H_

#include "PointerTraits.h"
#include "TypeTraits.h"

namespace STL {

template<typename Alloc>
struct allocator_traits {
    using allocator_type     = Alloc;
    using value_type         = typename Alloc::value_type;
    using pointer            = value_type*;
    using const_pointer      = typename pointer_traits<pointer>::template rebind<const value_type>;
    using void_pointer       = typename pointer_traits<pointer>::template rebind<void>;
    using const_void_pointer = typename pointer_traits<pointer>::template rebind<const void>;
    using difference_type    = typename pointer_traits<pointer>::difference_type;
    using size_type          = typename make_unsigned<difference_type>::type;
    using propagate_on_container_copy_assignment = false_type;
    using propagate_on_container_move_assignment = typename Alloc::propagate_on_container_copy_assignment;
    using propagate_on_container_swap            = false_type;
    using is_always_equal                        = typename Alloc::is_always_equal;
};

} // STL

#endif // ALLCATOR_TRAITS_H_
