#ifndef MALLOC_ALLOCATOR_H_
#define MALLOC_ALLOCATOR_H_

namespace STL {

template<typename T>
class MallocAllocator {
public:
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T*             pointer;
    typedef const T*       const_pointer;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef T              value_type;
    
    template<typename T1>
    struct rebind {
        typedef MallocAllocator<T1> other;
    };

    size_type max_size() const noexcept {
        return size_t(-1) / sizeof(T);
    }

    MallocAllocator() noexcept { }
    MallocAllocator(const MallocAllocator&) noexcept { }
    template<typename T1>
    MallocAllocator(const MallocAllocator<T1>&) noexcept { }

    ~MallocAllocator() noexcept { }
    
    pointer address(reference x) const noexcept {
        return std::addressof(x);
    }

    const_pointer address(const_reference x) const noexcept {
        return std::addressof(x);
    }
    
    pointer allocate(size_type n, const void* = 0) {
        if(n > this->max_size()) {
            exit(1);
        }
        pointer ret = 0;
        if(!ret) {
            ret = static_cast<T*>(std::malloc(n * sizeof(T)));
        }
        if(!ret) {
            exit(1);
        }
        return ret;
    }

    void deallocate(pointer p, size_type) {
        std::free(static_cast<void*>(p));
    }

    void construct(pointer p, const T& val) {
        ::new((void*)p) value_type(val);
    }

    void destroy(pointer p) {
        p->~T();
    }
};

}

#endif
