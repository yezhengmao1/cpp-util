#ifndef INSERTSORT_H_
#define INSERTSORT_H_

#include <Sort.h>

template<class It, class Compare = std::less<value_type_t<It>>>
void InsertSort(It begin, It end, Compare cmp = Compare()) {
    for(auto it = begin; it != end; ++it) {
        auto const insertion = std::upper_bound(begin, it, *it, cmp);
        std::rotate(insertion, it, std::next(it));
    }
}

#endif
